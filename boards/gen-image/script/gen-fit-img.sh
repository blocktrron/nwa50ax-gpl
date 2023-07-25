#!/bin/sh

BASE_DIR=`realpath "$(dirname "$0")/../"`

IMG_DIR=${BASE_DIR}/image
ZLD_SPEC=${BASE_DIR}/include/zld-spec.mk
partition=${BASE_DIR}/config/zyxel-partition.xml
flash_script=${IMG_DIR}/script
its=${IMG_DIR}/zyxel.its

source ${BASE_DIR}/include/common.mk

# Get compatible models
compat_models="[ "
max_model_num=$(get_zld_parm_int "ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_NUM" ${ZLD_SPEC})
for ((i=0;i<$max_model_num;i++))
do
	tmp=$(get_zld_parm_str "ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_${i}" ${ZLD_SPEC})

	compat_models+=${tmp:0:2}" "
	compat_models+=${tmp:2:4}" "
done
compat_models+="]"
fw_version=${FIRMWARE_VER}

# Create flash partition script for u-boot upgrade
part_count=$(xmllint --xpath 'count(//partition)' ${partition})
printf "echo ' '\n" > ${flash_script}
for ((i=1; i<=part_count; i++))
do
	part_name="$(get_xml_tag ${partition} partition[$i] name)"
	part_size="$(get_xml_tag ${partition} partition[$i] size)"
	part_start_addr="$(get_xml_tag ${partition} partition[$i] start_addr)"
	part_start_addr_1="$(get_xml_tag ${partition} partition[$i] start_addr_1)"
	part_img="$(get_xml_tag ${partition} partition[$i] img)"
	part_img_size=$(stat -c%s ${IMG_DIR}/${part_img} 2> /dev/null)
	normal_update="$(get_xml_tag ${partition} partition[$i] normal_update)"
	img_xtract_name=${part_name}

	gen_flash_partition_script ${flash_script} ${partition}
	if [ -n "${part_start_addr_1}" ]; then
		part_name="${part_name}_1"
		part_start_addr=${part_start_addr_1}
		gen_flash_partition_script ${flash_script}
	fi
done

# Create its
des="$(get_xml_tag ${partition} description)"
printf "/dts-v1/;\n"                                            >  ${its}
printf "\n"                                                     >> ${its}
printf "/ {\n"                                                  >> ${its}
printf "\tdescription = \"${des}\";\n"                          >> ${its}

printf "\tcompat-models = ${compat_models};\n"                  >> ${its}
printf "\tfw_version = \"${fw_version}\";\n"                        >> ${its}
printf "\n"                                                     >> ${its}
printf "\timages {\n"                                           >> ${its}

printf "\t\tscript {\n"                                         >> ${its}
printf "\t\t\tdata = /incbin/(\"${flash_script}\");\n"          >> ${its}
printf "\t\t\ttype = \"script\";\n"                             >> ${its}
printf "\t\t\tcompression = \"none\";\n"                        >> ${its}
printf "\t\t\thash@1 {algo = \"sha256\";};\n"                   >> ${its}
printf "\t\t};\n"                                               >> ${its}

part_count=$(xmllint --xpath 'count(//partition)' ${partition})
for ((i=1; i<=part_count; i++))
do
	part_name="$(get_xml_tag ${partition} partition[$i] name)"
	part_size="$(get_xml_tag ${partition} partition[$i] size)"
	part_img="$(get_xml_tag ${partition} partition[$i] img)"
	part_img_size=$(stat -c%s ${IMG_DIR}/${part_img} 2>/dev/null)

	if [ -z ${part_img} ] || [ "${part_img}" = "erase" ]; then
		continue
	fi

	if [ ${part_img_size} -gt $((${part_size}*1024)) ]; then
		printf "${part_name} exceeds partition size ${part_size} kilobytes.\n"
		exit 1
	fi

	printf "\t\t${part_name} {\n"                           >> ${its}
	printf "\t\t\tdata = /incbin/(\"${IMG_DIR}/${part_img}\");\n"      >> ${its}
	printf "\t\t\ttype = \"firmware\";\n"                   >> ${its}
	printf "\t\t\tcompression = \"none\";\n"                >> ${its}
	printf "\t\t\thash@1 {algo = \"sha256\";};\n"           >> ${its}
	printf "\t\t};\n"                                       >> ${its}
done

printf "\t};\n"                                                 >> ${its}
printf "};\n"                                                   >> ${its}
# Create ZLD-current
for ((i=0;i<$max_model_num;i++))
do
	tmp=$(get_zld_parm_str "ZLDSYSPARM_COMPATIBLE_PRODUCT_NAME_${i}" ${ZLD_SPEC})

	if [ -n "${tmp}" ]; then
		cp ${IMG_DIR}/mrd-${tmp}.bin ${IMG_DIR}/mrd.bin
		mkimage -f ${its} ${IMG_DIR}/${tmp}.img

		if [ $i -eq 0 ]; then
			cp ${IMG_DIR}/${tmp}.img ${IMG_DIR}/ZLD-current
		fi
	fi
done

# Remove unused image
for ((i=1; i<=part_count; i++))
do
	part_img="$(get_xml_tag ${partition} partition[$i] img)"

	if [ -z ${part_img} ] || [ "${part_img}" = "erase" ]; then
		continue
	fi

	rm -f ${IMG_DIR}/${part_img}
done
rm -rf ${IMG_DIR}/mrd*.bin ${its} ${flash_script}
