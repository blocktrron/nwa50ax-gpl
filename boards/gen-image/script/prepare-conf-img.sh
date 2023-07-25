#!/bin/sh -x

rootfs_dir="$1"

BASE_DIR=`realpath "$(dirname "$0")/../"`

partition=${BASE_DIR}/config/zyxel-partition.xml

source ${BASE_DIR}/include/common.mk

part_count=$(xmllint --xpath 'count(//partition)' ${partition})
for ((i=1; i<=part_count; i++))
do
	part_name="$(get_xml_tag ${partition} partition[$i] name)"

	if [ "${part_name}" = "rootfs_data" ]; then
		block_size="$(get_xml_tag ${partition} partition[$i] block_size)"
	fi
done

dirs=(
'etc/zyxel/ftp'
);

for ((i=0; i < ${#dirs[@]}; i++))
do
	mkfs.jffs2 -U --root=${rootfs_dir}/${dirs[$i]} --eraseblock=$((${block_size}*1024)) \
	-l --squash -o ${BASE_DIR}/tmp${i}.bin && rm -rf ${rootfs_dir}/${dirs[$i]}/*
done

${BASE_DIR}/script/gen-ubi.img.sh "rootfs_data"
rm -f ${BASE_DIR}/tmp*.bin
cp ${BASE_DIR}/image/rootfs_data.img ${rootfs_dir}
