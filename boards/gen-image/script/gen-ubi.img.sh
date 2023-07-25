#!/bin/sh

img=$1

BASE_DIR=`realpath "$(dirname "$0")/../"`
partition=${BASE_DIR}/config/zyxel-partition.xml
ubi_cfg=${BASE_DIR}/config/ubinize-${img}.cfg
output=${BASE_DIR}/image/${img}.img

source ${BASE_DIR}/include/common.mk

# Get logs info
part_count=$(xmllint --xpath 'count(//partition)' ${partition})
for ((i=1; i<=part_count; i++))
do
	part_name="$(get_xml_tag ${partition} partition[$i] name)"

	if [ "${part_name}" = "${img}" ]; then
		block_size="$(get_xml_tag ${partition} partition[$i] block_size)"
		min_io_size="$(get_xml_tag ${partition} partition[$i] min_io_size)"
	fi
done

# gen logs image
(cd ${BASE_DIR} && ubinize -v -o ${output} -m ${min_io_size} -p ${block_size}KiB \
	${ubi_cfg})
