#!/bin/sh

BASE_DIR=`realpath "$(dirname "$0")/../"`

partition=${BASE_DIR}/config/zyxel-partition.xml
dts=${BASE_DIR}/partition_tmp.dts

gen_partition_dts()
{
	dts=$1

	printf "\n"                                                     >> ${dts}
	printf "\t\t\tpartition@${part_start_addr#0x} {\n"              >> ${dts}
	printf "\t\t\t\tlabel = \"${part_name}\";\n"                    >> ${dts}
	printf "\t\t\t\treg = <${part_start_addr} ${part_size_hex}>;\n" >> ${dts}
	printf "\t\t\t};\n"                                             >> ${dts}
}

source ${BASE_DIR}/../gen-image/include/common.mk

printf "\tnmbm {\n"                                                     >  ${dts}
printf "\t\tcompatible = \"generic,nmbm\";\n"                           >> ${dts}
printf "\t\t#address-cells = <1>;\n"                                    >> ${dts}
printf "\t\t#size-cells = <1>;\n"                                       >> ${dts}
printf "\t\tlower-mtd-device = <&nandflash>;\n"                         >> ${dts}
printf "\t\tforced-create;\n"                                           >> ${dts}
printf "\t\tpartitions {\n"                                             >> ${dts}
printf "\t\t\tcompatible = \"fixed-partitions\";\n"                     >> ${dts}
printf "\t\t\t#address-cells = <1>;\n"                                  >> ${dts}
printf "\t\t\t#size-cells = <1>;\n"                                     >> ${dts}

part_count=$(xmllint --xpath 'count(//partition)' ${partition})
for ((i=1; i<=part_count; i++))
do
	part_name="$(get_xml_tag ${partition} partition[$i] name)"
	part_size="$(get_xml_tag ${partition} partition[$i] size)"
	part_size_hex="$(printf "0x%x" $((${part_size}*1024)))"
	part_start_addr="$(get_xml_tag ${partition} partition[$i] start_addr)"
	part_start_addr_1="$(get_xml_tag ${partition} partition[$i] start_addr_1)"

	gen_partition_dts ${dts}
	if [ -n "${part_start_addr_1}" ]; then
		part_name="${part_name}_1"
		part_start_addr=${part_start_addr_1}
		gen_partition_dts ${dts}
	fi
done

printf "\t\t};\n"                                                       >> ${dts}
printf "\t};\n"                                                         >> ${dts}
