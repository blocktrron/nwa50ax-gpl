#!/bin/bash

### !! do not remove these functions !! ###

# pre env_setup actions:
function customized_env_setup {
        return 0
}

# pre build_prepare actions:
function customized_build_prepare {
        # generate package config from apps_list
        rm -f ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/apps_list.in
        touch ${GALAXY_PROWLAN_FEED_PATH}/zld-common-files/zld-files/apps_list.in
        return 0
}

source ../_scripts/build-galaxy.sh

build_galaxy_main $@
