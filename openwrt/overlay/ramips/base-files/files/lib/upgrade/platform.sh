#
# Copyright (C) 2010 OpenWrt.org
#

upgrade_fail ()
{
	if [ "$MULTIBOOT" -eq 1 ]; then
		[ ! -f /tmp/multiboot_status ] && {
			echo "255" > /tmp/multiboot_status
		}
	else
		echo "Upgrade failed"
		sync
		reboot -f
		sleep 5
		echo 1 > /proc/support/sw_reset
	fi
}
trap upgrade_fail EXIT

get_full_section_name() {
	local img=$1
	local sec=$2

	dumpimage -l ${img} | grep "^ Image.*(${sec})" | \
		sed 's,^ Image.*(\(.*\)),\1,'
}

print_sections() {
	local img=$1

	dumpimage -l ${img} | awk '/^ Image.*(.*)/ { print gensub(/Image .* \((.*)\)/,"\\1", $0) }'
}

image_demux() {
	local img=$1

	for sec in $(print_sections ${img}); do
		local fullname=$(get_full_section_name ${img} ${sec})

		local position=$(dumpimage -l ${img} | grep "(${fullname})" | awk '{print $2}')
		dumpimage -i ${img} -o /tmp/${fullname}.bin -T "flat_dt" -p "${position}" ${fullname} > /dev/null || { \
			echo "Error while extracting \"${sec}\" from ${img}"
			return 1
		}
	done
	return 0
}

do_flash_dual_partition() {
	local bin=$1
	local mtdname=$2

	[ ${upgradeImg} -eq 1 ] && {
		mtdname="${mtdname}_1"
	}

	do_flash_mtd $bin $mtdname
}

do_flash_mtd() {
	local bin=$1
	local mtdname=$2
	local append=""

	local mtdpart=$(grep "\"${mtdname}\"" /proc/mtd | awk -F: '{print $1}')
	local flash_type=$(mtdinfo "/dev/${mtdpart}" | grep Type | awk '{FS=":"}; {print $2}')

	case "${flash_type}" in
		nand) flash_eraseall "/dev/${mtdpart}" && nandwrite -p "/dev/${mtdpart}" "/tmp/${bin}.bin";;
		nor)
			if [ "$(is_the_same_nor_partition ${bin} ${mtdpart})" -eq 1 ] ;then 
				echo "up-to-date. Section ${mtdname} ignored"
			else
				flash_eraseall "/dev/${mtdpart}"
				flashcp -v "/tmp/${bin}.bin" "/dev/${mtdpart}"
			fi
			;;
		*) echo "Unhandled flash type";;
	esac
}

do_flash_ubi() {
	local bin=$1
	local mtdname=$2
	local mtdpart
	local primaryboot

	mtdpart=$(grep "\"${mtdname}\"" /proc/mtd | awk -F: '{print $1}')
	ubiformat /dev/${mtdpart} -y -f /tmp/${bin}.bin
}

flash_section() {
	local sec=$1

	case "${sec}" in
		firmware*) do_flash_dual_partition ${sec} "firmware";;
		*) echo "Section ${sec} ignored"; return 0;;
	esac

	echo "Flashed ${sec}"
}

platform_check_image() {
	return 0
}

platform_pre_upgrade() {
	echo "Upgrade started"
	echo "Current time: $(date)"
	echo "----- kernel cmdline -----"
	cat /proc/cmdline
	echo "------- FW version -------"
	cat /rw/fwversion
	
	killall lldpcli 1>/dev/null 2>/dev/null
	/usr/local/sbin/lldpcli fwupdate 2>/dev/null

	/etc/init.d/switch_disable stop
	/etc/init.d/zylogd stop
	/bin/zysh -p 100 -e "_hybrid-mode reduce startup config"
	/etc/init.d/save-time.sh
	/etc/init.d/nc_conn_dbg_keeper stop
	return 0
}

platform_do_upgrade() {
	set -e
	upgradeImg=$(zyDualImageKit getUpgradeImageNum | awk -F'=' '{print $2}')
	zyDualImageKit setImageState Image${upgradeImg} fail
	echo "${upgradeImg}" > /etc/zyxel/ftp/keep/sendUpgradeLog
	sync

	image_demux $1 || {\
		echo "Error: \"$1\" couldn't be extracted. Abort..."
		return 1
	}

	for sec in $(print_sections $1); do
		if [ ! -e /tmp/${sec}.bin ]; then
			echo "Error: Cant' find ${sec}, aborting upgrade!"
			reboot
		fi
	done

	for sec in $(print_sections $1); do
		flash_section ${sec}
	done

	rm -rf /etc/zyxel/ftp/tmp/*

	echo "Upgrade ImageNum=${upgradeImg}"
	zyDualImageKit setImageState Image${upgradeImg} new
	sync
}

platform_copy_config() {
	touch /etc/zyxel/ftp/keep/warm_start
	rm -f /etc/zyxel/ftp/keep/firmware-upgraded-cli-change
	sync

	return 0
}

blink_led() {
	zyled led_firmware_upgrading
	return 0
}

disable_watchdog() {
	return 0
}

append sysupgrade_pre_upgrade disable_watchdog
append sysupgrade_pre_upgrade blink_led
