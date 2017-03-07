#!/bin/bash

export WORKPATH=`pwd`
TOP=$WORKPATH
while true;do
	if [ -d $TOP/toolchains ];then
		#echo $TOP
		break
	fi

	if [ x$TOP == x ];then #这里x的作用用于判断$TOP是否为空, if [ X$str = Xabc ], 谨防$str 为空
		echo "no"
		break
	else
		echo "yes"
	fi
	TOP=${TOP%/*}
done

#if [ `uname -m`x = "i686"x ]; then
#	TOOLCHAIN=$TOP/toolchains/mips-gcc472-glibc216-32bit/bin
#else
#	TOOLCHAIN=$TOP/toolchains/mips-gcc472-glibc216/bin
#fi

TOOLCHAIN=$TOP/toolchains/mipsel-gcc472-glibc216-mips32/bin
PATH=$TOOLCHAIN:$PATH
echo "setup PATH=$TOOLCHAIN:\$PATH"

export CROSS_COMPILE='mips-linux-gnu-'


