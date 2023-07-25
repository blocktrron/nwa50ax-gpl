#!/bin/sh

BASE_DIR=`realpath "$(dirname "$0")/../"`
IMG_DIR=${BASE_DIR}/image
ZLD_SPEC=${BASE_DIR}/include/zld-spec.mk

source ${BASE_DIR}/include/common.mk

product=$(get_zld_parm_str "ZLDSYSPARM_PRODUCT_NAME" ${ZLD_SPEC})
max_model_num=$(get_zld_parm_int "ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_NUM" ${ZLD_SPEC})

gen_wtp_info()
{
	local wtp_info=$1
	printf "<WTP_wtp_image/${product}>\n"		>   ${wtp_info}
	printf "<list>\n"				>>  ${wtp_info}
	printf "name                :code\n"		>>  ${wtp_info}
	printf "version             :${FIRMWARE_VER}\n"	>>  ${wtp_info}
	printf "</list>\n"				>>  ${wtp_info}
	printf "<model>\n"				>>  ${wtp_info}
	for ((i=0;i<$max_model_num;i++))
	do
		printf "COMPATIBLE_PRODUCT_MODEL[${i}]=$(get_zld_parm_str \
			"ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_${i}" ${ZLD_SPEC})\n"	>>  ${wtp_info}
	done
	printf "</model>\n"				>>  ${wtp_info}
	printf "</WTP_wtp_image/${product}>\n"		>>  ${wtp_info}
}

gen_wtp_xml()
{
	local wtp_xml=$1
	printf "\t\t<set name=\"WTP_wtp_image/${product}\">\n"		>    ${wtp_xml}
	printf "\t\t\t<scope>-f wtp_image/${product} -D /db</scope>\n"	>>   ${wtp_xml}
	printf "\t\t\t<version>${FIRMWARE_VER}</version>\n"		>>   ${wtp_xml}
	printf "\t\t\t<build_date>${BUILD_TIME}</build_date>\n"		>>   ${wtp_xml}
	printf "\t\t</set>\n"						>>   ${wtp_xml}
}

gen_wtp_info ${IMG_DIR}/${product}.wtpinfo
gen_wtp_xml ${IMG_DIR}/${product}.xml
