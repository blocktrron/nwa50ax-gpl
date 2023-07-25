#!/bin/sh

PATH=/bin:/usr/bin:/sbin:/usr/sbin

# save time
date -u +%m%d%H%M%Y.%S > /etc/zyxel/ftp/conf/.time-cache.conf

# save timezone
if [ -f "/etc/TZ" ]; then
	cat /etc/TZ > /etc/zyxel/ftp/conf/.TZ
fi
