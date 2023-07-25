#!/bin/bash

# We can use gen_apps_list.sh to generate package list in feed and edit it if necessary.
# Then use this script to convert it to openwrt config.

if [ $# -ne 2 ]; then
	echo "Usage: $(basename $0) <apps_list.cprep file> <apps_list.in file>"
	exit
fi

echo -ne "" > $2

while read apps; do
        if [ ! -z "${apps}" ]; then
                echo -ne "config PACKAGE_${apps}\n\ttristate\n\tdefault y\n\n" >> $2
        fi
done < $1
