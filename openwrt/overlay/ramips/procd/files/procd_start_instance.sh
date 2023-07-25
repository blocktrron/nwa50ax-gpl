#!/bin/sh
. /lib/functions.sh

usage()
{
	echo "usage: $0 [procd_script_name] [respawn_count] [respawn_retry] [instance_name]"
	exit 1
}

echo_to_console(){
	echo "$@" > /dev/console
}

APP_WD_RECOVER_LOG="/etc/zyxel/ftp/tmp/app_wd_recover.log"
echo_to_recover_log(){
	echo "$@" >> $APP_WD_RECOVER_LOG
}

app_name=$1
respawn_count=$2
respawn_retry=$3
instance_name=$4

# add something want to do here before we respawn the application, below is an example
# echo_to_console "procd respawn: app_name:$app_name, instance_name:$instance_name, respawn_count:$respawn_count, respawn_retry:$respawn_retry"

FIRMWARE_VERSION=$(cat /rw/fwversion | grep "FIRMWARE" | cut -d "=" -f2)
DATE=$(date +"%Y-%m-%d %H:%M:%S")
#64 KB
MAX_LOG_FILE_SIZE=65536

if [ ! -f "$APP_WD_RECOVER_LOG" ]; then
	#echo "$APP_WD_RECOVER_LOG does not exist."
	touch $APP_WD_RECOVER_LOG
fi
LOG_SIZE=$(ls -la $APP_WD_RECOVER_LOG | awk '{print $5}')

if [ "$LOG_SIZE" -gt "$MAX_LOG_FILE_SIZE" ] ;then
	#Clear log and print exceed maximum log
	echo "" > $APP_WD_RECOVER_LOG
	echo_to_console "The $APP_WD_RECOVER_LOG size exceed maximum. 64 KB. Clear it "
fi
	echo_to_recover_log "Firmware version: $FIRMWARE_VERSION, Recover date: $DATE, App name: $app_name, Recover count: $respawn_count"




