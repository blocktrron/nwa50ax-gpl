import os
import logging
import yaml
import glob
import shutil
import subprocess
import shlex
import argparse
import re
import sys
import time
import filecmp
from shutil import copyfile
from pathlib import Path
from util import run_command_with_logging

OPENWRT_STAGING_HOST_BIN = "staging_dir/host/bin"
OPENWRT_FEEDS_UNINSTALL_COMMAND = "./scripts/feeds uninstall -a"
OPENWRT_FEEDS_CLEAN_COMMAND = "./scripts/feeds clean"
OPENWRT_FEEDS_UPDATE_COMMAND = "./scripts/feeds update -a"
OPENWRT_FEEDS_INSTALL_COMMAND = "./scripts/feeds install -a -f"
OPENWRT_DEFAULT_CONFIG_COMMAND = "make defconfig"
OPENWRT_DEFAULT_MAKE_COMMAND = "make"
OPENWRT_DEFAULT_CLEAN_COMMAND = "make clean"
OPENWRT_DISTCLEAN_COMMAND = "make distclean"
OPENWRT_BUILD_ERROR_MESSAGE = "build failed. Please re-run make with -j1 V=s to see what's going on"

def copytree(src, dst, symlinks=False, ignore=None):
    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isdir(s):
            shutil.copytree(s, d, symlinks, ignore)
        else:
            shutil.copy2(s, d)

class OpenWRTBuildPipeline:
    def __init__(self, build):
        self.build_tasks = [self.build_task_init, self.build_task_feeds_init, self.build_task_run, self.build_task_images_pack]
        self.build = build
        return

    def copy_config(self, source_file, dest_file):
        try:
            if filecmp.cmp(source_file, dest_file):
                return
            logging.info("Copy config from {0} to {1} ".format(source_file, dest_file))
        except FileNotFoundError:
            logging.debug("Config file {0} is not existed so copying a new one".format(dest_file))

        shutil.copyfile(source_file, dest_file)
        return

    def build_task_init(self, build_ctx):
        project_path = Path(build_ctx['project_path'])
        build = build_ctx['project_build']

        # logging.info("Start to build for {0}".format(build['name']))

        if 'feeds' in build:
            feeds_conf = Path("{0}/{1}".format(str(project_path), build['feeds']))
            feeds_conf_dest = Path("{0}/feeds.conf".format(str(build_ctx['openwrt_dir'])))
            self.copy_config(str(feeds_conf), str(feeds_conf_dest))
            logging.info("OpenWRT feeds config: {0}".format(feeds_conf))

        if 'defconfig' in build:
            defconfig = Path("{0}/{1}".format(str(project_path), build['defconfig']))
            defconfig_dest = Path("{0}/.config".format(str(build_ctx['openwrt_dir'])))
            self.copy_config(str(defconfig), str(defconfig_dest))
            logging.info("OpenWRT defconfig: {0}".format(defconfig))

            for line in open(str(defconfig_dest), 'r'):
                if line.startswith('CONFIG_TARGET_BOARD'):
                    build_ctx['openwrt_target'] = line.strip().split('=')[1].strip('"')
                if line.startswith('CONFIG_TARGET_SUBTARGET'):
                    build_ctx['openwrt_subtarget'] = line.strip().split('=')[1].strip('"')
                    break

        if 'kconfig' in build:
            kconfig = Path("{0}/{1}".format(str(project_path), build['kconfig']))
            kconfig_dest_file = build['kconfig'].replace("config/", "")
            kconfig_dest_file = kconfig_dest_file.replace(build_ctx['project'] + '.', "")
            kconfig_dest = Path("{0}/target/linux/{1}/{2}".format(str(build_ctx['openwrt_dir']),
                                                                  str(build_ctx['openwrt_target']),
                                                                  str(kconfig_dest_file)))

            kconfig_exists = False
            logging.debug(kconfig_dest)
            if os.path.exists(str(kconfig_dest)):
                kconfig_exists = True
            if not kconfig_exists:
                kconfig_dest = Path("{0}/target/linux/{1}/{2}/{3}".format(str(build_ctx['openwrt_dir']),
                                                                    str(build_ctx['openwrt_target']),
                                                                    str(build_ctx['openwrt_subtarget']),
                                                                    str(kconfig_dest_file)))
            logging.debug(kconfig_dest)

            self.copy_config(str(kconfig), str(kconfig_dest))
            logging.info("OpenWRT kernel config: {0}".format(kconfig))

        if 'ubnizecfg' in build:
            ubinizecfg = Path("{0}/{1}".format(str(project_path), build['ubnizecfg']))
            ubinizecfg_dest_file = build['ubnizecfg'].replace("config/", "")
            ubinizecfg_dest = Path("{0}/target/linux/{1}/image/{2}".format(str(build_ctx['openwrt_dir']),
                                                             str(build_ctx['openwrt_target']),
                                                             str(ubinizecfg_dest_file)))

            self.copy_config(str(ubinizecfg), str(ubinizecfg_dest))

        if 'prepare' in build:
            if build['prepare'] == 'ipq':
                run_command_with_logging("{0}/qsdk-others/scripts/src-prep.sh".format(str(project_path)))

        logging.info("OpenWRT target: {0}".format(build_ctx['openwrt_target']))

        # Update zyxel partition to device tree
        if 'zyxel_dts' in build:
            kernel_dts_path = Path("{0}/target/linux/{1}/dts/{2}".format(str(build_ctx['openwrt_dir']),
                                                                  str(build_ctx['openwrt_target']),
                                                                  str(build['zyxel_dts'])))

            ret = run_command_with_logging("{0}/script/gen-partition-dts.sh".format(project_path))
            logging.info("Gen kernel partition dts with {0}".format(ret))

            with open('partition_tmp.dts') as f:
                first_line = f.readline()
            dts_name = first_line.strip()

            ret = run_command_with_logging('sed -i -e "/\t{0}/ r {1}" -e "/\t{0}/,/^\t}};/d" {2}'.format(dts_name, "partition_tmp.dts", "zyxel.dts"))
            logging.info("Update kernel dts with {0}".format(ret))

            self.copy_config("zyxel.dts", str(kernel_dts_path))

        # If overlay is assigned, check whether symbolic link is correct
        if 'overlay' in build:
            overlay_symlink = Path("{0}/overlay/{1}".format(str(build_ctx['openwrt_dir']), str(build_ctx['openwrt_target'])))

            if overlay_symlink.is_symlink():
                linkpath = str(overlay_symlink.resolve())
                dirname = os.path.dirname(linkpath)
                basename = os.path.basename(linkpath)

                if basename != build['overlay']:
                    os.unlink(str(overlay_symlink))
                    os.symlink(build['overlay'], "{0}/{1}".format(dirname, build_ctx['openwrt_target']))

        # Prepare gen-image dir
        gen_img_dir = build_ctx['gen_img_dir']
        if os.path.isdir('{0}/image'.format(gen_img_dir)):
            shutil.rmtree('{0}/image'.format(gen_img_dir))
        os.mkdir('{0}/image'.format(gen_img_dir))
        if not os.path.isdir('{0}/config'.format(gen_img_dir)):
            os.mkdir('{0}/config'.format(gen_img_dir))
        copytree("{0}/include".format(project_path), "{0}/include".format(gen_img_dir))
        copytree("{0}/config".format(project_path), "{0}/config".format(gen_img_dir))

        # Inject version before run
        for _i, image in enumerate(build_ctx['project_image_list']):
            if image['name'] == 'firmware':
                firmware = image

        with open('{0}/fwinfo'.format(build_ctx['openwrt_dir']), 'w') as f:
            f.write('{0},{1}'.format(firmware['version'],
            time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())))

        # Export FIRMWARE_VER
        if image['type'] == 'default':
            if build_ctx['version'] != '':
                os.environ["FIRMWARE_VER"] = build_ctx['version']
            else:
                os.environ["FIRMWARE_VER"] = image['version']

        # Export BUILD_TIME
        os.environ["BUILD_TIME"] = time.strftime("%Y-%m-%d %T", time.localtime())

        if build_ctx['release'] and os.path.isfile(Path("{0}/.time".format(str(project_path)))):
            fp = open('{0}/.time'.format(str(project_path)), 'r')
            line = fp.read()
            os.environ["BUILD_TIME"] = str(line)
            fp.close()
        else:
            fp = open('{0}/.time'.format(str(project_path)), 'w')
            fp.write('{0}'.format(os.getenv("BUILD_TIME")))
            fp.close()

        # Create zyxel-image.mk symlink to openwrt include dir
        if os.path.isfile(Path("{0}/include/zyxel-image.mk".format(str(project_path)))):
            os.remove(Path("{0}/include/zyxel-image.mk".format(str(build_ctx['openwrt_dir']))))
            os.symlink(Path("{0}/include/zyxel-image.mk".format(str(project_path))),
                Path("{0}/include/zyxel-image.mk".format(str(build_ctx['openwrt_dir']))))

        return 0

    def build_task_feeds_init(self, build_ctx):
        os.chdir(build_ctx['openwrt_dir'])

        run_command_with_logging(OPENWRT_FEEDS_UNINSTALL_COMMAND)
        run_command_with_logging(OPENWRT_FEEDS_CLEAN_COMMAND)

        ret = run_command_with_logging(OPENWRT_FEEDS_UPDATE_COMMAND)
        logging.info("Feeds update with ret {0}".format(ret))

        ret = run_command_with_logging(OPENWRT_FEEDS_INSTALL_COMMAND)
        logging.info("Feeds install with ret {0}".format(ret))
        return 0

    def build_task_run(self, build_ctx):
        project_path = build_ctx['project_path']
        build = build_ctx['project_build']
        parameters = build_ctx['project_parameters'][0]

        os.chdir(build_ctx['openwrt_dir'])
        os.environ["NO_COLOR"] = "1"
        defconfig = Path("{0}/{1}".format(str(project_path), build['defconfig']))
        defconfig_dest = Path("{0}/.config".format(str(build_ctx['openwrt_dir'])))
        shutil.copyfile(str(defconfig), str(defconfig_dest))

        run_command_with_logging(OPENWRT_DEFAULT_CONFIG_COMMAND)

        # The root/non-root option have to update the password files.
        if build_ctx['root']:
            run_command_with_logging("sed -i '/^root/c\\root::0:0:root&admin&120&120&480&480&1&0:/root:/bin/bash' \
                {0}/overlay/{1}/base-files/files/etc/zyxel/sys/passwd.basic".format(str(build_ctx['openwrt_dir']),str(build_ctx['openwrt_target'])))
            run_command_with_logging("sed -i '/^root/c\\root::12396:0:99999:7:::' \
                {0}/overlay/{1}/base-files/files/etc/zyxel/sys/shadow.basic".format(str(build_ctx['openwrt_dir']),str(build_ctx['openwrt_target'])))
        else:
            run_command_with_logging("sed -i '/^root/c\\root:x:0:0:root&admin&120&120&480&480&1&0:/root:/bin/bash' \
                {0}/overlay/{1}/base-files/files/etc/zyxel/sys/passwd.basic".format(str(build_ctx['openwrt_dir']),str(build_ctx['openwrt_target'])))
            run_command_with_logging("sed -i '/^root/c\\root:***:12396:0:99999:7:::' \
                {0}/overlay/{1}/base-files/files/etc/zyxel/sys/shadow.basic".format(str(build_ctx['openwrt_dir']),str(build_ctx['openwrt_target'])))

        # Clean the base-files to update the password files on rootfs.
        run_command_with_logging("make package/base-files/clean")
        # Clean zld-files to make sure ZYSH_PATH is cleaned
        run_command_with_logging("make package/zld-files/clean")

        if 'jobs' in parameters:
            build_cmd = "{0} -j{1}".format(OPENWRT_DEFAULT_MAKE_COMMAND, parameters['jobs'])
        else:
            build_cmd = "{0} -j{1}".format(OPENWRT_DEFAULT_MAKE_COMMAND, build_ctx['jobs'])
        if build_ctx['verbose']:
            build_cmd += " V=s --output-sync=target"

        logging.info("OpenWRT build command: {0}".format(build_cmd))
        ret = run_command_with_logging(build_cmd)
        if ret:
            if not build_ctx['verbose']:
                logging.info("OpenWRT build is failed! Re-build with make -j1 V=s")
                if build_ctx['retry_clean']:
                    run_command_with_logging("make clean")
                run_command_with_logging("make -j1 V=s")
                '''
                    It's likely "make -j1 V=s" will compile OK however we'd like to return
                    error to break the build
                '''
            sys.exit(-1)
        else:
            return 0

    def build_task_images_pack_generic(self, build_ctx):
        logging.debug("Prepare gen-image dir")
        openwrt_bin_path = Path("{0}/bin/targets/{1}/{2}".format(str(build_ctx['openwrt_dir']),
                                                                str(build_ctx['openwrt_target']),
                                                                str(build_ctx['openwrt_subtarget'])))

        parameters = build_ctx['project_parameters'][0]
        project_path = build_ctx['project_path']
        gen_img_dir = build_ctx['gen_img_dir']
        sysupgrade_bin = "{0}/image/sysupgrade.bin".format(gen_img_dir)
        nebula_yang_list_files = list(openwrt_bin_path.glob("**/nebula_yang_list.csv"))

        logging.debug("Copy prebuilt binary to image dir")
        copytree("{0}/image".format(project_path), "{0}/image".format(gen_img_dir))

        logging.debug("Copy boot.bin to uboot naming")
        if 'uboot' in parameters:
            uboot_filename = parameters['uboot']
            shutil.copyfile("{0}/image/boot.bin".format(gen_img_dir),
                "{0}/image/{1}".format(gen_img_dir, uboot_filename))

        logging.debug("Copy system-default.conf to image dir")
        shutil.copyfile("{0}/conf/system-default.conf.cprep".format(project_path),
                "{0}/image/system-default.conf".format(gen_img_dir))

        logging.debug("Copy zld-spec.h to image dir")
        shutil.copyfile("{}/boards/{}/include/zld-spec.h".format(str(build_ctx['root_dir']),build_ctx['project']),
                "{0}/image/zld-spec.h".format(gen_img_dir))

        if not (len(nebula_yang_list_files) > 0):
            logging.debug("Cannot find nebula_yang_list.csv in {}!!".format(str(openwrt_bin_path)))
        else:
            logging.info("Found {}!!".format(nebula_yang_list_files[0]))
            shutil.copyfile(nebula_yang_list_files[0], "{}/image/nebula_yang_list.csv".format(gen_img_dir))

        logging.debug("Create logs.img")
        ret = run_command_with_logging("{0}/script/gen-ubi.img.sh logs".format(gen_img_dir))
        if ret:
            logging.info("Error occured in gen-ubi.img.sh logs! Please check the result in build.log!!")
            return False

        logging.debug("Create myzyxel.img")
        ret = run_command_with_logging("{0}/script/gen-ubi.img.sh myzyxel".format(gen_img_dir))
        if ret:
            logging.info("Error occured in gen-ubi.img.sh myzyxel! Please check the result in build.log!!")
            return False

        logging.debug("Create mrd.bin")
        ret = run_command_with_logging("make -C {0} -f mrd.mk all".format(gen_img_dir))
        if ret:
            logging.info("Error occured in create mrd! Please check the result in build.log!!")
            return False

        logging.debug("Create wtpinfo")
        ret = run_command_with_logging("{0}/script/gen-wtpinfo.sh".format(gen_img_dir))
        if ret:
            logging.info("Error occured in create wtpinfo! Please check the result in build.log!!")
            return False

        logging.debug("Move sysupgeade bin to image dir")
        if 'sysupgrade' in parameters:
            sysupgrade_filename = parameters['sysupgrade']
        else:
            print("Sysupgrade filename isn't configurated")
            return False

        files = list(openwrt_bin_path.glob("**/{0}".format(str(sysupgrade_filename))))
        if not files:
            logging.debug("No {0} is found from ".format(str(sysupgrade_filename)) + str(openwrt_bin_path))
            return False
        for _i, file in enumerate(files):
            shutil.move(str(file), sysupgrade_bin)

        return 0

    def build_task_images_pack_mtk(self, build_ctx):
        return 0

    def build_task_images_pack_qsdk(self, build_ctx):
        project_path = build_ctx['project_path']

        os.chdir(build_ctx['root_dir'])

        openwrt_bin_path = Path('{0}/bin/{1}'.format(build_ctx['openwrt_dir'], build_ctx['openwrt_target']))
        logging.debug(openwrt_bin_path)
        images_bin_path = Path('{0}/common/build/ipq_x64'.format(project_path))
        files = list(openwrt_bin_path.glob("**/openwrt*"))

        dtbs_path = Path('{0}/bin/{1}/dtbs'.format(build_ctx['openwrt_dir'], build_ctx['openwrt_target']))
        logging.debug(dtbs_path)
        files_dtbs = list(dtbs_path.glob("**/*"))

        ubinize_exists = False
        ubinize_bin_path = Path('{0}/staging_dir/host/bin/ubinize'.format(build_ctx['openwrt_dir']))
        logging.debug(ubinize_bin_path)
        if os.path.exists(str(ubinize_bin_path)):
            ubinize_exists = True

        for _i, file in enumerate(files):
            dest_file = "{0}/{1}".format(images_bin_path, file.name)
            logging.debug("Copy openwrt bin file {0} to {1}".format(str(file), dest_file))
            shutil.copyfile(str(file), dest_file)

        for _i, file in enumerate(files_dtbs):
            dest_file = "{0}/{1}".format(images_bin_path, file.name)
            logging.debug("Copy dtbs file {0} to {1}".format(str(file), dest_file))
            shutil.copyfile(str(file), dest_file)

        if (ubinize_exists):
            dest_file = "{0}/{1}".format(images_bin_path, os.path.basename(str(ubinize_bin_path)))
            logging.debug("Copy ubinize bin file {0} to {1}".format(str(ubinize_bin_path), dest_file))
            shutil.copy2(str(ubinize_bin_path), dest_file)

        return 0

    def build_task_images_pack_ipq(self, build_ctx):
        return 0

    def build_task_images_pack(self, build_ctx):
        logging.debug("Enter _task_images_pack")

        images_pack_dispatch = {'ZYXEL_REF': self.build_task_images_pack_generic,
                                'MTK11AX_REF': self.build_task_images_pack_mtk,
                                'WAX650S_REF': self.build_task_images_pack_qsdk,
                                'IPQ_REF': self.build_task_images_pack_ipq}

        images_pack_dispatch[build_ctx['project_models'][0]](build_ctx)

        return 0

    def execute(self, build_ctx):
        build_ok = True
        for _i, task in enumerate(self.build_tasks):
            ret = task(build_ctx)
            if ret is not 0:
                build_ok = False
                break

        if build_ok:
            logging.info("Build is successful")
        else:
            logging.error("Build is failed! Please check the build.log for the details")
            sys.exit(-1)
        return build_ok

class OpenWRTPackZYXELFirmwarePipeline:
    def __init__(self, image):
        self.image = image
        return

    def execute(self, build_ctx):
        logging.info("Enter OpenWRTPackZYXELFirmwarePipeline")
        gen_img_dir = build_ctx['gen_img_dir']

        ret = run_command_with_logging("{0}/script/gen-fit-img.sh".format(gen_img_dir))
        if ret:
            logging.info("Error occured in gen-fit-img.sh! Please check the result in build.log!!")
            return False

class OpenWRTPackMTKFirmwarePipeline:
    def __init__(self, image):
        self.image = image
        return

    def execute(self, build_ctx):
        logging.info("Enter OpenWRTPackMTKFirmwarePipeline")
        project_path = build_ctx['project_path']
        # firmware = self.image
        parameters = build_ctx['project_parameters'][0]

        if 'sysupgrade' in parameters:
            sysupgrade_filename = parameters['sysupgrade']
        else:
            print("Sysupgrade filename isn't configurated")
            return False

        output_path = "{0}/bin/".format(project_path)
        if not os.path.exists(output_path):
            os.makedirs(output_path)

        openwrt_bin_path = Path("{0}/bin/targets/{1}/{2}".format(str(build_ctx['openwrt_dir']),
                                                                str(build_ctx['openwrt_target']),
                                                                str(build_ctx['openwrt_subtarget'])))
        files = list(openwrt_bin_path.glob("**/{0}".format(str(sysupgrade_filename))))
        if not files:
            logging.debug("No {0}is found from ".format(str(sysupgrade_filename)) + str(openwrt_bin_path))
            return False
        for _i, file in enumerate(files):
            dest_file = "{0}/{1}".format(output_path, file.name)
            logging.debug("Move openwrt bin file {0} to {1}".format(str(file), dest_file))
            shutil.move(str(file), dest_file)

        return

class OpenWRTPackQSDKFirmwarePipeline:
    def __init__(self, image):
        self.image = image
        return

    def execute(self, build_ctx):
        os.chdir('{0}/common/build'.format(build_ctx['project_path']))
        return run_command_with_logging("python update_common_info.py")

class OpenWRTPackIPQFirmwarePipeline:
    def __init__(self, image):
        self.image = image
        return

    def execute(self, build_ctx):
        return run_command_with_logging("{0}/qsdk-others/scripts/gen-image.sh".format(build_ctx['project_path']))

class OpenWRTCleanPipeline:
    def execute(self, build_ctx, distclean):
        os.chdir(build_ctx['openwrt_dir'])
        if distclean:
            return run_command_with_logging(OPENWRT_DISTCLEAN_COMMAND)
        else:
            return run_command_with_logging(OPENWRT_DEFAULT_CLEAN_COMMAND)

class OpenWRTZYXELReleasePipeline:
    def __init__(self, release):
        self.release = release
        return

    def execute(self, build_ctx):
        logging.debug("Enter OpenWRTZYXELReleasePipeline execute")
        zyxel_bin_path = Path("{0}/../gen-image/image".format(str(build_ctx['project_path'])))
        logging.debug("Enter OpenWRTZYXELReleasePipeline execute " + str(zyxel_bin_path))
        files = list(zyxel_bin_path.glob("**/{0}".format(self.release['from_file'])))

        if (len(files) != 1):
            logging.debug("File {0} is not found".format(self.release['from_file']))
            return False

        logging.debug("Release File {0}".format(self.release['from_file']))

        base_path = Path(build_ctx['releasedir'])
        to_file_path = base_path / self.release['to_file']
        md5_file_path = "{0}.md5".format(to_file_path)

        os.makedirs(str(base_path), exist_ok=True)
        copyfile(str(files[0]), str(to_file_path))
        md5 = subprocess.check_output(['md5sum', self.release['to_file']], cwd=str(base_path))
        with open(str(md5_file_path), 'wb') as outfile:
            outfile.write(md5)
        return True

class OpenWRTReleasePipeline:
    def __init__(self, release):
        self.release = release
        return

    def execute(self, build_ctx):
        logging.debug("Enter OpenWRTReleasePipeline execute")
        project_path = Path(build_ctx['project_path'])
        logging.debug("Enter OpenWRTReleasePipeline execute " + str(project_path))
        files = list(project_path.glob("**/{0}".format(self.release['from_file'])))

        if (len(files) != 1):
            logging.debug("File {0} is not found".format(self.release['from_file']))
            return False

        base_path = Path(build_ctx['releasedir'])
        to_file_path = base_path / self.release['to_file']
        md5_file_path = to_file_path.with_suffix('.md5')

        os.makedirs(str(base_path), exist_ok=True)
        copyfile(str(files[0]), str(to_file_path))
        md5 = subprocess.check_output(['md5sum', self.release['to_file']], cwd=str(base_path))
        with open(str(md5_file_path), 'wb') as outfile:
            outfile.write(md5)
        return True

class ArchiveReleasePipeline:
    def __init__(self, release):
        self.release = release
        return

    def execute(self, build_ctx):
        logging.debug("Enter ArchiveReleasePipeline execute")
        subprocess.check_output(['tar', 'zcvf', self.release['to_file']] + self.release['from_file'], cwd=build_ctx['releasedir'])
        return True

class OpenWRTSetupPipeline(OpenWRTBuildPipeline):
    def __init__(self, build):
        self.build_tasks = [self.build_task_init, self.build_task_feeds_init, self.build_task_setup]
        self.build = build
        return

    def build_task_setup(self, build_ctx):
        project_path = build_ctx['project_path']
        build = build_ctx['project_build']

        os.chdir(build_ctx['openwrt_dir'])
        os.environ["NO_COLOR"] = "1"
        defconfig = Path("{0}/{1}".format(str(project_path), build['defconfig']))
        defconfig_dest = Path("{0}/.config".format(str(build_ctx['openwrt_dir'])))
        shutil.copyfile(str(defconfig), str(defconfig_dest))

        return run_command_with_logging(OPENWRT_DEFAULT_CONFIG_COMMAND)

class OpenWRTPreparePipeline(OpenWRTSetupPipeline):
    def __init__(self, build):
        self.build_tasks = [self.build_task_init, self.build_task_feeds_init, self.build_task_setup, self.buil_task_prepare]
        self.build = build
        return

    def buil_task_prepare(self, build_ctx):
        os.chdir(build_ctx['openwrt_dir'])
        os.environ["NO_COLOR"] = "1"
        parameters = build_ctx['project_parameters'][0]

        build_cmd = 'make prepare'
        if 'jobs' in parameters:
            build_cmd += " -j{0}".format(parameters['jobs'])
        else:
            build_cmd += " -j{0}".format(build_ctx['jobs'])
        if build_ctx['verbose']:
            build_cmd += " V=s --output-sync=target"
        logging.info("OpenWRT build command: {0}".format(build_cmd))
        return run_command_with_logging(build_cmd)

class OpenWRTMakeImagePipeline(OpenWRTBuildPipeline):
    def __init__(self, build):
        self.build_tasks = [self.build_task_init, self.build_task_make_image, self.build_task_images_pack]
        self.build = build
        return

    def build_task_make_image(self, build_ctx):
        parameters = build_ctx['project_parameters'][0]
        os.chdir(build_ctx['openwrt_dir'])
        os.environ["NO_COLOR"] = "1"

        build_cmd = 'make'
        if 'jobs' in parameters:
            build_cmd += " -j{0}".format(parameters['jobs'])
        else:
            build_cmd += " -j{0}".format(build_ctx['jobs'])
        if build_ctx['verbose']:
            build_cmd += " V=s --output-sync=target"

        run_command_with_logging('{} package/install'.format(build_cmd))
        run_command_with_logging('{} target/install'.format(build_cmd))

        return 0

class OpenwrtRebuildZySH(OpenWRTMakeImagePipeline):
    def __init__(self, build):
        self.build_tasks = [self.build_task_init, self.build_task_rebuild_zysh]
        self.build = build
        return

    def build_task_rebuild_zysh(self, build_ctx):
        parameters = build_ctx['project_parameters'][0]
        os.chdir(build_ctx['openwrt_dir'])
        os.environ["NO_COLOR"] = "1"

        for pkg in [ 'zysh', 'zld-files', 'zyklog' ]:
            run_command_with_logging('make package/{}/clean'.format(pkg))

        build_cmd = 'make'
        if 'jobs' in parameters:
            build_cmd += " -j{0}".format(parameters['jobs'])
        else:
            build_cmd += " -j{0}".format(build_ctx['jobs'])
        if build_ctx['verbose']:
            build_cmd += " V=s --output-sync=target"

        run_command_with_logging('{} package/zysh/compile'.format(build_cmd))

        return 0

class OpenWRTPlatformBuilder:
    def __init__(self):
        return

    def create_build_pipeline(self, build):
        return OpenWRTBuildPipeline(build)

    def create_pack_image_pipeline(self, image):
        if not 'type' in image:
            logging.error("Invalid image definition for " + image['name'])
            return None

        if image['type'] == 'squashfs-mtk':
            return OpenWRTPackMTKFirmwarePipeline(image)
        elif image['type'] == 'qsdk':
            return OpenWRTPackQSDKFirmwarePipeline(image)
        elif image['type'] == 'ipq':
            return OpenWRTPackIPQFirmwarePipeline(image)
        else:
            return OpenWRTPackZYXELFirmwarePipeline(image)

    def create_release_image_pipeline(self, release):
        if release['image'] == 'archive':
            return ArchiveReleasePipeline(release)
        elif release['image'] == 'openwrt':
            return OpenWRTReleasePipeline(release)
        else:
            return OpenWRTZYXELReleasePipeline(release)

    def create_clean_pipeline(self):
        return OpenWRTCleanPipeline()

    def create_setup_pipeline(self, build):
        return OpenWRTSetupPipeline(build)

    def create_prepare_pipeline(self, build):
        return OpenWRTPreparePipeline(build)

    def create_make_image_pipeline(self, build):
        return OpenWRTMakeImagePipeline(build)

    def create_rebuild_zysh_pipeline(self, build):
        return OpenwrtRebuildZySH(build)
