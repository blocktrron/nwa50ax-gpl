#!/bin/sh -x

TARGET_ROOT=$1
SRC_DIRS="bin sbin usr/sbin"
DST_DIR="usr/bin/"

for dir in $SRC_DIRS; do
	mv -n $TARGET_ROOT/$dir/* $TARGET_ROOT/$DST_DIR || true
	files=$(find $TARGET_ROOT/$dir -mindepth 1 || true)
	if [ ! -z "$files" ]; then
		echo "ERROR: Cannot merge $dir into $DST_DIR due to duplicate files:"
		echo "$files"
		exit 1
	fi
	rm -fr $TARGET_ROOT/$dir
	ln -snfr $TARGET_ROOT/$DST_DIR $TARGET_ROOT/$dir
done
