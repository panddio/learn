#!/bin/bash

if [ $# -gt 0 ]; then
    TARGET_DEVICE=$1
fi

if [ x"$TARGET_DEVICE" = x ]; then
    TARGET_DEVICE="halley2"
fi

echo "TARGET_DEVICE = $TARGET_DEVICE"
./out/host/tools/mkfs.jffs2 -e 0x8000 -p 0xc80000 -d ./out/product/$TARGET_DEVICE/system/ -o ./out/product/$TARGET_DEVICE/image/system.jffs2
