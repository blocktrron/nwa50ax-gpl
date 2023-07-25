#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: $(basename $0) <nucleus feeds directory>"
	exit
fi

grep -R 'BuildPackage,' $1 | cut -d ':' -f 2- | sed -r 's#.+?\(call BuildPackage,(.+?)\).+#\1#g' | sort | grep -v 'PKG_NAME' > apps_list
grep -R 'KernelPackage,' $1 | cut -d ':' -f 2- | sed -r 's#.+?\(call KernelPackage,(.+?)\).+#kmod-\1#g' | sort | grep -v 'PKG_NAME' >> apps_list
