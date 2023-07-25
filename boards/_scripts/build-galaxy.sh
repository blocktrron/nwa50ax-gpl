#!/bin/bash

#
# define build product
#
GALAXY_BUILD_PRODUCT=${GALAXY_BUILD_PRODUCT:=$(basename $PWD)}

#
# define build dirs
#
GALAXY_BUILD_TOP=${GALAXY_BUILD_TOP:=$(cd ../.. ; pwd)}
GALAXY_BUILD_DIR=${GALAXY_BUILD_DIR:=$PWD}
GALAXY_BUILD_SCRIPT=${GALAXY_BUILD_SCRIPT:="$(dirname $PWD)/_scripts"}

#
# define ZLD related paths
#
GALAXY_ZLD_REPO_PATH=${GALAXY_ZLD_REPO_PATH:="${GALAXY_BUILD_TOP}/wlan-ap"}
GALAXY_OPENWRT_PATH=${GALAXY_OPENWRT_PATH:="${GALAXY_BUILD_TOP}/openwrt"}
GALAXY_PROWLAN_FEED_PATH=${GALAXY_PROWLAN_FEED_PATH:="${GALAXY_OPENWRT_PATH}/nucleus/feeds"}

#
# define galaxy-ap board files
#
GALAXY_FEEDS="${GALAXY_BUILD_DIR}/config/${GALAXY_BUILD_PRODUCT}.feeds.conf"
GALAXY_KERNEL_VER=${GALAXY_KERNEL_VER:="4.4"}
GALAXY_KCONFIG="${GALAXY_BUILD_DIR}/config/${GALAXY_BUILD_PRODUCT}.config-${GALAXY_KERNEL_VER}"
GALAXY_DEFCONFIG="${GALAXY_BUILD_DIR}/config/${GALAXY_BUILD_PRODUCT}.defconfig"
GALAXY_TARGET=$(grep 'CONFIG_TARGET_BOARD' ${GALAXY_DEFCONFIG} | cut -d '=' -f 2 | sed -e 's/\"//g')
GALAXY_SUBTARGET=$(grep 'CONFIG_TARGET_SUBTARGET' ${GALAXY_DEFCONFIG} | cut -d '=' -f 2 | sed -e 's/\"//g')

# define additional files
CPREP_FILE_LIST="apps_list app_wd.conf ZLDconfig conf/*.conf conf/__system_default.xml"
ZLD_KERNEL_HEADERS="k_ifacename_change.h k_ifacename_list.h netlink_extern.h prowlan_ipc.h prowlan_var.h"

# for install rootfs files to base-file dir in overlay
OVERLAY_ROOTFS_DIR=${GALAXY_OPENWRT_PATH}/overlay/${GALAXY_TARGET}/base-files/files

# for calling gen-image
GEN_IMAGE_DIR=${GEN_IMAGE_DIR:="$(dirname $PWD)/gen-image"}

function env_setup {
	#
	# call customized_env_setup
	#
	customized_env_setup
        # do cprep for files in list
        for f in ${CPREP_FILE_LIST}; do
                ${GALAXY_ZLD_REPO_PATH}/zld/cprep.sh ${GALAXY_BUILD_DIR}/${f} ${GALAXY_BUILD_DIR}/include/zld-spec.h 1 > /dev/null 2>&1
        done
}

function build_prepare {
	#
	# call customized_build_prepare
	#
	customized_build_prepare
        # cprep.sh
        install -m 755 ${GALAXY_ZLD_REPO_PATH}/zld/cprep.sh ${GALAXY_PROWLAN_FEED_PATH}/cprep.sh
        # zld-spec.mk
        ${GALAXY_ZLD_REPO_PATH}/zld/convert-header-to-mkfile ${GALAXY_BUILD_DIR}/include/zld-spec.h
        install -m 644 ${GALAXY_BUILD_DIR}/include/zld-spec.mk ${GALAXY_PROWLAN_FEED_PATH}/zld-spec.mk
        # /etc/zyxel/ftp/*
        install -m 755 -d ${OVERLAY_ROOTFS_DIR}/etc/zyxel/ftp/conf
        install -m 777 -d ${OVERLAY_ROOTFS_DIR}/etc/zyxel/ftp/cert
        install -m 777 -d ${OVERLAY_ROOTFS_DIR}/etc/zyxel/ftp/cert/trusted
        # conf/*
        install -m 755 -d ${OVERLAY_ROOTFS_DIR}/etc/zyxel/conf
        install -m 644 ${GALAXY_BUILD_DIR}/ZLDconfig.cprep ${OVERLAY_ROOTFS_DIR}/etc/zyxel/conf/ZLDconfig
        install -m 644 ${GALAXY_BUILD_DIR}/conf/system-default.conf.cprep ${OVERLAY_ROOTFS_DIR}/etc/zyxel/conf/system-default.conf
        install -m 755 ${GALAXY_BUILD_DIR}/conf/regen-fw.sh ${OVERLAY_ROOTFS_DIR}/etc/zyxel/conf/regen-fw.sh
        install -m 755 -d ${OVERLAY_ROOTFS_DIR}/etc/zyxel/conf/default
        install -m 644 ${GALAXY_BUILD_DIR}/conf/cloud-temp.conf.cprep ${OVERLAY_ROOTFS_DIR}/etc/zyxel/conf/default/cloud-temp.conf
        install -m 644 ${GALAXY_BUILD_DIR}/conf/managed-temp.conf.cprep ${OVERLAY_ROOTFS_DIR}/etc/zyxel/conf/default/managed-temp.conf
        install -m 644 ${GALAXY_BUILD_DIR}/conf/standalone-temp.conf.cprep ${OVERLAY_ROOTFS_DIR}/etc/zyxel/conf/default/standalone-temp.conf
        # this __system_default.xml is ro
        install -m 644 ${GALAXY_BUILD_DIR}/conf/__system_default.xml.cprep ${OVERLAY_ROOTFS_DIR}/etc/zyxel/conf/__system_default.xml
        # app_wd.conf
        install -m 755 -d ${OVERLAY_ROOTFS_DIR}/etc
        install -m 644 ${GALAXY_BUILD_DIR}/app_wd.conf.cprep ${OVERLAY_ROOTFS_DIR}/etc/app_wd.conf
        #
        # zld-files header files
        #
        install -m 755 -d ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/files/include/
        # zld-spec.h
        install -m 644 ${GALAXY_BUILD_DIR}/include/zld-spec.h ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/files/include/zld-spec.h
        # platform_common.h: Please check libgpio_control when this file is removed.
        install -m 644 ${GALAXY_ZLD_REPO_PATH}/platform/include/platform_common.h ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/files/include/platform_common.h
        # MRD.h
        install -m 644 ${GALAXY_ZLD_REPO_PATH}/zld/include/MRD.h ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/files/include/MRD.h
        # zld-include package
        install -m 644 ${GALAXY_ZLD_REPO_PATH}/common/zld-include/*.h ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/files/include
        # FIXME: zyxel_event_type.h from wireless common header
        install -m 644 ${GALAXY_ZLD_REPO_PATH}/wireless/common_header/zyxel_event_type.h ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/files/include
        # FIXME: model_info.h
        install -m 644 ${GALAXY_BUILD_DIR}/include/model_info.h ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/files/include/model_info.h
        # FIXME: headers of kernel modules should be installed by kernel module packages
        install -m 755 -d ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/files/include/zld
        for f in ${ZLD_KERNEL_HEADERS}; do
                install -m 644 ${GALAXY_ZLD_REPO_PATH}/kernel-modules/zld-kernel-hack-ipq807x-4.4.60/include/${f} ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/files/include/zld
        done
        # FIXME: web_auth.h
        install -m 644 ${GALAXY_ZLD_REPO_PATH}/aaa/mlogin-1.0.0/web_auth.h ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/files/include
}

function clean_dirs {
        ( cd ${GALAXY_OPENWRT_PATH} && \
                git checkout -- . && \
                git clean -fdx package/ ; )
        ( cd ${GALAXY_OPENWRT_PATH}/overlay && \
                git checkout -- . && \
                git clean -fdx ; )
        ( cd ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files && \
                git clean -fdx ; )
        ( cd ${GEN_IMAGE_DIR} && \
                git clean -fdx ; )
        ( cd ${GALAXY_BUILD_DIR} && \
                git checkout -- . && \
                git clean -fdx ; )
}

function print_build_usage {
        echo "Usage: $0 ( setup | prepare | clean | root )"
        exit 0
}

function build_galaxy_main {
        if [ $# -eq 1 ]; then
                case $1 in
                setup)
                        env_setup
                        ;;
                prepare)
                        build_prepare
                        ;;
                clean)
                        clean_dirs
                        ;;
                all)
                        env_setup
                        build_prepare
                        ;;
                *)
                        print_build_usage
                        ;;
                esac
        else
                print_build_usage
        fi
}
