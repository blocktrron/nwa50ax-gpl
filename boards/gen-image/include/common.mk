source ${BASE_DIR}/include/image.mk

get_zld_parm_int() {
	local parm=$1
	local zld_spec_mk=$2
	echo "$(grep -w ${parm} ${zld_spec_mk} | awk -F'=' '{print $2}')"
}

get_zld_parm_str() {
	local parm=$1
	local zld_spec_mk=$2
	echo "$(grep -w ${parm} ${zld_spec_mk} | awk -F'"' '{print $2}')"
}

get_xml_tag()
{
	local xml=$1
	local parent=$2
	local tag=$3
	echo $(xmllint --xpath '(//'"${parent}"'/'"${tag}"'/text())' ${xml})
}

gen_flash_partition_script()
{
	if [ -z ${part_img} ]; then
		return
	fi
	local flash_script=$1
	local partition=$2

	printf "failedmsg='[   failed   ]'\n"                             >> ${flash_script}
	printf "echo \\\\\c'%-40.40s'\n" "Flashing ${part_name}:"         >> ${flash_script}
	printf "if test "x\${verbose}" = "x"; then\n"                     >> ${flash_script}
	printf "setenv stdout nulldev\n"                                  >> ${flash_script}
	printf "fi\n"                                                     >> ${flash_script}

	if [ ${normal_update} -eq 0 ]; then
		printf "if test \${normal_update} -ne 1; then\n"          >> ${flash_script}
	fi

	if [ "${part_img}" != "erase" ]; then
		printf "failreason='error: failed on image extraction'\n" >> ${flash_script}
		printf "imxtract ${imgaddr} ${img_xtract_name} ${fileaddr} || setenv stdout serial \
&& echo \"\${failedmsg}\" && echo \"\${failreason}\" && exit 1\n" >> ${flash_script}
	fi

	printf "failreason='error: failed on partition erase'\n"          >> ${flash_script}
	erase ${part_start_addr} $((${part_size}*1024)) ${flash_script}
	printf "|| setenv stdout serial && echo \"\${failedmsg}\" && \
echo \"\${failreason}\" && exit 1\n"                                      >> ${flash_script}

	if [ "${part_img}" != "erase" ]; then
		printf "failreason='error: failed on partition write'\n"  >> ${flash_script}
		write ${part_start_addr} ${part_img_size} ${flash_script}
		printf "|| setenv stdout serial && echo \"\${failedmsg}\" && \
echo \"\${failreason}\" && exit 1\n"                                      >> ${flash_script}
	fi

	printf "resultmsg='[    done    ]'\n"                             >> ${flash_script}
	if [ ${normal_update} -eq 0 ]; then
		printf "else\n"                                           >> ${flash_script}
		printf "resultmsg='[  skipped!  ]'\n"                     >> ${flash_script}
		printf "fi\n"                                             >> ${flash_script}
	fi
	printf "setenv stdout serial\n"                                   >> ${flash_script}
	printf "echo \"\${resultmsg}\"\n"                                 >> ${flash_script}

	printf "\n"                                                       >> ${flash_script}
}
