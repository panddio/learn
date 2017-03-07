#!/bin/bash

UBOOT_BUILD_CONFIG=halley2_v10_xImage_sfc_nor
KERNEL_BUILD_CONFIG=halley2_nor_v10_linux_defconfig
KERNEL_TARGET_IMAGE=xImage

echo "$KERNEL_BUILD_CONFIG, $KERNEL_TARGET_IMAGE, $UBOOT_BUILD_CONFIG"

tmp=${1#-j}
echo "$tmp"

x="xx87+ jdlj"
echo $x | grep -o '[0-9]\+'

case "$2" in
	[1-9][0-9]*)
		echo "$2 is number"
		;;
	*)
		;;
	esac

if [ -n "$(echo $2 | sed -n "/^[0-9]\+$/p")" ];then
  echo "$2 is number."
else
  echo 'no.'
fi
