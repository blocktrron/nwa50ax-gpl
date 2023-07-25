#!/usr/bin/env python3
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
import socket
import datetime
import time
import json

from pathlib import Path
from openwrt_builder import OpenWRTPlatformBuilder
from util import bcolors, init_logger, run_command_with_logging
from glob import glob

fusion_root_dir = os.getcwd()
fusion_openwrt_dir = '{0}/openwrt'.format(fusion_root_dir)
fusion_images_dir = "{0}/images".format(fusion_root_dir)
fusion_gen_img_dir = "{0}/boards/gen-image".format(fusion_root_dir)
#pattern = re.compile(r'\$\{([a-zA-Z]+)\}')
pattern = re.compile(r'\$\{([^}^{]+)\}')
build_ctx = {}

def varexpan_constructor(loader,node):
    value = node.value
    expandvalue = ''
    lastidx = 0

    while(True):
        match = pattern.search(value, lastidx)
        if match is None:
            expandvalue += value[lastidx:]
            break

        if (match.start() != 0):
            expandvalue += value[lastidx:match.start()]

        env_var = match.group()[2:-1]
        expandvalue += build_ctx[env_var]
        lastidx = match.end()

    logging.getLogger().debug("Value {0} expands to {1}".format(value, expandvalue))
    return expandvalue

def load_project(filename):
    #define the regex pattern that the parser will use to 'implicitely' tag your node
    yaml.add_implicit_resolver("!varexpan", pattern)
    yaml.add_constructor('!varexpan', varexpan_constructor)

    with open(filename, 'r') as f:
        return yaml.load(f, Loader=yaml.Loader)

def dump_projects():
    projects = list(glob("{0}/**/project.yaml".format(fusion_images_dir)))
    print("\nTarget boards available to build:")
    for _i, project_path_str in enumerate(projects):
        project_path = Path(project_path_str)
        print("{0} - {1}".format(project_path.parent.name, project_path.parent))
    return

def create_platform_builder(project):
    return OpenWRTPlatformBuilder()

def save_build_ctx_to_file():
    with open('{0}/.build_ctx.json'.format(fusion_root_dir), 'w') as outfile:
        json.dump(build_ctx, outfile, indent=4)

def build_projects(args, projects):
    for _i, project_path_str in enumerate(projects):
        p = load_project(project_path_str)
        project_path = Path(project_path_str)

        build_ctx['project_def'] = p
        images_def = {}
        for _i, image in enumerate(p['images']):
            images_def[image['name']] = image

        if 'releases' in p:
            images_releases = p['releases']
        else:
            images_releases = None

        platform_builder = create_platform_builder(p)
        build_ctx['project'] = project_path.parent.name
        build_ctx['project_path'] = str(project_path.parent)

        if 'zld_config' in p:
            zld_config = p['zld_config']
        else:
            zld_config = None

        if args.clean or args.distclean:
            pipeline = platform_builder.create_clean_pipeline()
            if args.distclean:
                pipeline.execute(build_ctx, 1)
            else:
                pipeline.execute(build_ctx, 0)
            # run clean script if it is set
            if zld_config != None and zld_config.get('clean_script','') != '':
                os.chdir(build_ctx['project_path'])
                run_command_with_logging(zld_config['clean_script'])
            break

        logging.getLogger().info("Found a project {0} from {1} and start building".
            format(project_path.parent.name, fusion_images_dir))

        for _i, build in enumerate(p['builds']):
            if args.build != None:
                if args.build != build['name']:
                    continue
            else:
                if 'default' in build:
                    if build['default'] is False:
                        continue

            # do the following check only when zld_config exists
            if zld_config != None:
                os.chdir(build_ctx['project_path'])
                os.environ['GALAXY_DEFCONFIG'] = "{0}/{1}".format(build_ctx['project_path'],build['defconfig'])
                if not (args.make_image or args.rebuild_zysh):
                    if zld_config.get('setup_script','') != '':
                        run_command_with_logging(zld_config['setup_script'])
                    if zld_config.get('prepare_script','') != '':
                        run_command_with_logging(zld_config['prepare_script'])
            if args.setup:
                logging.getLogger().info("Start to setup for {0}".format(build_ctx['project']))
                pipeline = platform_builder.create_setup_pipeline(build)
            elif args.prepare:
                logging.getLogger().info("Start to prepare for {0}".format(build_ctx['project']))
                pipeline = platform_builder.create_prepare_pipeline(build)
            elif args.make_image:
                logging.getLogger().info("Start to make image for {0}".format(build_ctx['project']))
                pipeline = platform_builder.create_make_image_pipeline(build)
            elif args.rebuild_zysh:
                logging.getLogger().info("Start to rebuild zysh for {0}".format(build_ctx['project']))
                pipeline = platform_builder.create_rebuild_zysh_pipeline(build)
            else:
                logging.getLogger().info("Start to build for {0}".format(build_ctx['project']))
                pipeline = platform_builder.create_build_pipeline(build)
            if 'models' in p:
                build_ctx['project_models'] = p['models']
            build_ctx['project_image_list'] = p['images']
            build_ctx['project_parameters'] = p['parameters']
            build_ctx['project_build'] = build
            pipeline.execute(build_ctx)
            if args.setup or args.prepare or args.rebuild_zysh:
                break

            for _i, image in enumerate(build['images']):
                pack_image_pipeline = platform_builder.create_pack_image_pipeline(images_def[image])
                pack_image_pipeline.execute(build_ctx)

            if args.releasedir != None and images_releases != None:
                for _i, release in enumerate(images_releases):
                    release_image_pipeline = platform_builder.create_release_image_pipeline(release)
                    release_image_pipeline.execute(build_ctx)

def main():
    global fusion_root_dir
    global fusion_openwrt_dir
    global fusion_images_dir
    global fusion_gen_img_dir

    curr_root_dir = os.path.dirname(os.path.abspath(sys.argv[0]))
    if curr_root_dir != fusion_root_dir:
        fusion_root_dir = curr_root_dir
        fusion_openwrt_dir = '{0}/openwrt'.format(fusion_root_dir)
        fusion_images_dir = "{0}/images".format(fusion_root_dir)
        fusion_gen_img_dir = "{0}/boards/gen-image".format(fusion_root_dir)

    init_logger('build.log')

    parser = argparse.ArgumentParser(description='Galaxy build frontend system')
    parser.add_argument('--list-targets', dest='dump_target', action='store_true', default=False,
                        help='list all target boards.')
    parser.add_argument('--target', dest='target', action='store',
                        help='specify the target board to build for. The target board is defined under images directory.')
    parser.add_argument('--release', dest='release', action='store_true', default=False,
                        help='To specify the release build.')
    parser.add_argument('--build', dest='build', action='store',
                        help='To specify the build from the project settings')
    parser.add_argument('--buildno', dest='buildno', action='store', type=int, default=1,
                        help='To specify the build number')
    parser.add_argument('--release-dir', dest='releasedir', action='store', default='./bin',
                        help='To specicy the release directory')
    parser.add_argument('--jobs', dest='jobs', action='store', type=int, default=int(os.cpu_count()+1),
                        help='Specifies  the  number  of  jobs  (commands)  to run simultaneously.')
    parser.add_argument('--verbose', dest='verbose', action='store_true', default=False,
                        help='Enable the verbose mode.')
    parser.add_argument('--clean-before-retry', dest='retry_clean', action='store_true', default=False,
                        help='If build failed, run \'make clean\' before retry with \'make -j1\'')
    parser.add_argument('--zld-enable-root', dest='root', action='store_true', default=False,
                        help='Enable root login without password for this build')
    parser.add_argument('--zld-version', dest='version', action='store', default='',
                        help='Set ZLD version to specified value')
    group = parser.add_mutually_exclusive_group()
    group.add_argument('--setup', dest='setup', action='store_true', default=False,
                        help='Only do environment setup and exit')
    group.add_argument('--prepare', dest='prepare', action='store_true', default=False,
                        help='Only do build prepare and exit')
    group.add_argument('--image', dest='make_image', action='store_true', default=False,
                        help='Only do gen-image and exit')
    group.add_argument('--rebuild-zysh', dest='rebuild_zysh', action='store_true', default=False,
                        help='Only rebuild ZYSH and exit')
    group.add_argument('--clean', dest='clean', action='store_true', default=False,
                        help='Clean the intermediate files of a build (but keep host tools and toolchain)')
    group.add_argument('--distclean', dest='distclean', action='store_true', default=False,
                    help='Clean the intermediate files of a build')

    args = parser.parse_args()

    logging.getLogger().info("{0}Galaxy build frontend system is running from {1}{2}".format(bcolors.HEADER, fusion_root_dir, bcolors.ENDC))

    if args.target is None:
        projects = list(glob("{0}/**/project.yaml".format(fusion_images_dir), recursive=True))
    else:
        projects = list(glob("{0}/{1}/**/project.yaml".format(fusion_images_dir, args.target), recursive=True))

    if (args.dump_target or len(projects) == 0):
        dump_projects()
        return

    build_ctx['root'] = args.root
    build_ctx['root_dir'] = fusion_root_dir
    build_ctx['openwrt_dir'] = fusion_openwrt_dir
    build_ctx['images_dir'] = fusion_images_dir
    build_ctx['gen_img_dir'] = fusion_gen_img_dir
    build_ctx['jobs'] = args.jobs
    build_ctx['retry_clean'] = args.retry_clean
    build_ctx['verbose'] = args.verbose
    build_ctx['buildno'] = "{:0>3d}".format(args.buildno)
    build_ctx['hostname'] = socket.gethostname()
    build_ctx['buildtime'] = datetime.datetime.fromtimestamp(time.time()).strftime('%Y-%m-%d.%H%M%S')
    build_ctx['version'] = args.version
    build_ctx['release'] = args.release

    if os.path.isabs(args.releasedir):
        build_ctx['releasedir'] = args.releasedir
    else:
        build_ctx['releasedir'] = '{0}/{1}'.format(fusion_root_dir, args.releasedir)

    build_projects(args, projects)
    save_build_ctx_to_file()

if __name__ == '__main__':
    main()
