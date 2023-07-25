#!/bin/sh

PREPARSE_PATH=$1 
GLOBAL_HEADER_PATH=$2
TEMP_PATH=/tmp/cprep_util.$$
C_PREPROCESSOR_OPTION="-E -x c -P -nostdinc -include " #Don't remove the include option.
ORIGINAL_PATH=$PWD
COMPACT_EMPTY_LINE=$3
KEEP_ALL_TEMP_FILE=0 #1 if you want to see all temp file for debugging or ..

C_PREPROCESSOR_PATH="gcc"

#Parameter check
if [ $# != "3" ] ; then
	echo "Usage : $0 [Parse file] [Global header] [Compact_empty_line:0|1]"
	exit 1;
fi
####################################
# Extract the file name
####################################
if [ ! -f $PREPARSE_PATH ] ; then
	echo "Preparse file:$PREPARSE_PATH is not existed!" 
	exit 1;
fi
PREPARSE_FILE=`echo $PREPARSE_PATH | awk -F / '{print $NF}'`
PREPARSE_TEMP_FILE=$PREPARSE_FILE.$$

if [ ! -f $GLOBAL_HEADER_PATH ] ; then
	echo "Global header file:$GLOBAL_HEADER_PATH is not existed!" 
	exit 1;
fi
GLOBAL_HEADER_FILE=`echo $GLOBAL_HEADER_PATH | awk -F / '{print $NF}'`
GLOBAL_TEMP_HEADER_FILE=$GLOBAL_HEADER_FILE.$$

if [ ! -d $TEMP_PATH ] ; then
	mkdir -p $TEMP_PATH;
	chmod 777 $TEMP_PATH;
fi

if [ ! -d $TEMP_PATH ] ; then
	echo "Can't create the temp path : $TEMP_PATH!"
	exit 1;
fi
######################################################
# Preserved the support C directives and 
# translate the C token
######################################################
cp $PREPARSE_PATH $TEMP_PATH/$PREPARSE_TEMP_FILE
cp $GLOBAL_HEADER_PATH $TEMP_PATH/$GLOBAL_TEMP_HEADER_FILE
cd $TEMP_PATH

# Translate C directives only if it is prefix token
sed '
s/^[[:blank:]]*#if/c0p1t2k3n_@c_if/g;
s/^[[:blank:]]*#else/c0p1t2k3n_@c_else/g;
s/^[[:blank:]]*#elif/c0p1t2k3n_@c_elif/g;
s/^[[:blank:]]*#endif/c0p1t2k3n_@c_endif/g;' <  $PREPARSE_TEMP_FILE > $PREPARSE_TEMP_FILE.replace_directive.1

# Translate non-C-directives lines (Prevent preprocessor from processing such text material)
sed  -e '/c0p1t2k3n_@c/! s/\t/c0p1t2k3n_T_TAB/g;
/c0p1t2k3n_@c/! s/#/c0p1t2k3n_T_#/g;
/c0p1t2k3n_@c/! s/\/\*/c0p1t2k3n_T_CSM/g;
/c0p1t2k3n_@c/! s/\*\//c0p1t2k3n_T_CEM/g;
/c0p1t2k3n_@c/! s/\\/c0p1t2k3n_T_SLASH/g;
/c0p1t2k3n_@c/! s/\//c0p1t2k3n_T_RSLASH/g;
/c0p1t2k3n_@c/! s/ /c0p1t2k3n_T_SPACE/g;
/c0p1t2k3n_@c/! s/^$/c0p1t2k3n_T_EL/g;
/c0p1t2k3n_@c/! s/"/c0p1t2k3n_T_DQ/g;' -e "/c0p1t2k3n_c@/! s/'/c0p1t2k3n_T_SQ/g" <  $PREPARSE_TEMP_FILE.replace_directive.1 > $PREPARSE_TEMP_FILE.replace_ctok.2

sed 's/c0p1t2k3n_@c_if/#if/g;
s/c0p1t2k3n_@c_else/#else/g;
s/c0p1t2k3n_@c_elif/#elif/g;
s/c0p1t2k3n_@c_endif/#endif/g;' <  $PREPARSE_TEMP_FILE.replace_ctok.2 > $PREPARSE_TEMP_FILE.pre_parse.3
######################################################
# Run the C preprocessor to parsing the file
######################################################
$C_PREPROCESSOR_PATH $C_PREPROCESSOR_OPTION $GLOBAL_TEMP_HEADER_FILE $PREPARSE_TEMP_FILE.pre_parse.3  > $PREPARSE_TEMP_FILE.pre_rpfx.4
# See if the pre-processing is successful
if [ $? != "0" ]; then
	echo "Error in parsing $TEMP_PATH/$PREPARSE_TEMP_FILE.pre_parse.3"
	# Remove TEMP_PATH folder
	rm -rf $TEMP_PATH
	exit 1;
fi
######################################################
# Remove prefix lines causing by -include option
######################################################
echo "1" > cal_line_count.$$.tmp
$C_PREPROCESSOR_PATH $C_PREPROCESSOR_OPTION $GLOBAL_TEMP_HEADER_FILE cal_line_count.$$.tmp  > cal_line_count.$$.tmp2
TMP1_LINE_COUNT=`wc -l cal_line_count.$$.tmp | awk '{print $1}'`
TMP2_LINE_COUNT=`wc -l cal_line_count.$$.tmp2 | awk '{print $1}'`
#EXTRA_LINE_COUNT=`expr $TMP2_LINE_COUNT - $TMP1_LINE_COUNT`
EXTRA_LINE_COUNT=$((TMP2_LINE_COUNT - TMP1_LINE_COUNT))
PREPARSE_FILE_LINE_COUNT=`wc -l $PREPARSE_TEMP_FILE.pre_parse.3 | awk '{print $1}'`
#TAIL_LINE_COUNT=`expr $PREPARSE_FILE_LINE_COUNT - $EXTRA_LINE_COUNT`
TAIL_LINE_COUNT=$((PREPARSE_FILE_LINE_COUNT - EXTRA_LINE_COUNT))

rm -f cal_line_count.$$.tmp cal_line_count.$$.tmp2
tail -n$TAIL_LINE_COUNT $PREPARSE_TEMP_FILE.pre_rpfx.4 > $PREPARSE_TEMP_FILE.pre_compact.5
######################################################
# Compact the empty line if this option is on
######################################################
if [ $COMPACT_EMPTY_LINE != "0" ] ; then
	sed '/^$/d' $PREPARSE_TEMP_FILE.pre_compact.5 > $PREPARSE_TEMP_FILE.pre_trans.6
else
	cp $PREPARSE_TEMP_FILE.pre_compact.5  $PREPARSE_TEMP_FILE.pre_trans.6
fi
#######################################################
# Final token translation & Outputing the final result
#######################################################
sed -e 's/c0p1t2k3n_T_TAB/\t/g;
s/c0p1t2k3n_T_#/#/g;
s/c0p1t2k3n_T_CSM/\/\*/g;
s/c0p1t2k3n_T_CEM/\*\//g;
s/c0p1t2k3n_T_SLASH/\\/g;
s/c0p1t2k3n_T_RSLASH/\//g;
s/c0p1t2k3n_T_SPACE/ /g;
s/c0p1t2k3n_T_EL//g;
s/c0p1t2k3n_T_DQ/"/g;' -e "s/c0p1t2k3n_T_SQ/'/g" <  $PREPARSE_TEMP_FILE.pre_trans.6 > $PREPARSE_TEMP_FILE.final
# Outputing the final result
cd $ORIGINAL_PATH
cp $TEMP_PATH/$PREPARSE_TEMP_FILE.final $PREPARSE_PATH.cprep

if [ $KEEP_ALL_TEMP_FILE != "1" ] ; then
	rm -f $TEMP_PATH/${PREPARSE_TEMP_FILE}*
	rm -f $TEMP_PATH/$GLOBAL_TEMP_HEADER_FILE
fi

# Remove TEMP_PATH folder
rm -rf $TEMP_PATH

echo "Preprocessing '$PREPARSE_FILE' with '$GLOBAL_HEADER_FILE' successfully."
exit 0;
