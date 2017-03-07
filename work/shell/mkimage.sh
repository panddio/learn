#!/bin/bash
#email: qiuwei.wang@ingenic.com


if [ $# -lt 1 ]; then
	echo "USAGE:`basename $0` [-a] [-k] [-u] [-m] [-c]" 
	echo "   eg:`basename $0` -k -u"
	echo "   eg:`basename $0` -c"
	echo "   eg:`basename $0` -a"
	exit
fi



#PRODUCT=mozart
#SOURCE_DIR=$HOME/work/$PRODUCT
SOURCE_DIR=$(pwd)
IMAGE_DIR=$SOURCE_DIR/out
ENVSET_FILE=$SOURCE_DIR/tools/source.sh

if [ ! -d $IMAGE_DIR ]; then
	mkdir -p $IMAGE_DIR
	if [ $? -ne 0 ]; then
		echo "mkdir $IMAGE_DIR failed..."
		echo "$IMAGE_DIR = $SOURCE_DIR"
		IMAGE_DIR=$SOURCE_DIR
	else
		echo "IMAGE_DIR = $IMAGE_DIR"
	fi
fi


if [ -d $SOURCE_DIR/u-boot/tools ];then
	echo "PATH=$SOURCE_DIR/u-boot/tools:\$PATH"
	export PATH=$SOURCE_DIR/u-boot/tools:$PATH
fi

if [ -f $ENVSET_FILE ];then
	echo "source $ENVSET_FILE"
	source $ENVSET_FILE
fi


echo "SOURCE_DIR: $SOURCE_DIR"
echo " IMAGE_DIR: $IMAGE_DIR"


while getopts ":akumc" opt
do
	case $1 in

	-a)
		echo "compiling u-boot ..."
		cd $SOURCE_DIR/u-boot
		make distclean
		make halley2_v20_zImage_sfc_nor_config && make -j8

		if [ $? -eq 0 ]; then
			cp u-boot-with-spl.bin $IMAGE_DIR
		fi

		echo "compiling kernel ..."
		cd $SOURCE_DIR/kernel*

		if [ -f .config ];then
			make zImage -j8
		else
			make clean
			make halley2_v20_oss_defconfig && make zImage -j8
		fi

		if [ $? -eq 0 ]; then
			cp arch/mips/boot/compressed/zImage $IMAGE_DIR
		fi

		echo "compiling mozart ..."
		cd $SOURCE_DIR/mozart
		make canna_v2.0_43438_cramfs_config && make

		if [ $? -eq 0 ]; then
			cp output/target/appfs.cramfs $IMAGE_DIR
			cp output/target/updater.cramfs $IMAGE_DIR
			cp output/target/usrdata.jffs2 $IMAGE_DIR
		fi
		echo "make all ..."
		;;
	-k)
		echo "compiling kernel ..."
		cd $SOURCE_DIR/kernel*

		if [ -f .config ];then
			make zImage -j8
		else
			make clean;
			make halley2_v20_oss_defconfig && make zImage -j8
		fi

		if [ $? -eq 0 ]; then
			cp arch/mips/boot/compressed/zImage $IMAGE_DIR
		fi
		;;
	-u)
		echo "compiling u-boot ..."
		cd $SOURCE_DIR/u-boot
		make distclean
		make halley2_v20_zImage_sfc_nor_config && make -j8

		if [ $? -eq 0 ]; then
			cp u-boot-with-spl.bin $IMAGE_DIR
		fi
		;;
	-m)
		echo "compiling mozart ..."
		cd $SOURCE_DIR/mozart

		if [ -f output/mozart/usr/include/mozart_config.h ];then
			make
		else
			make canna_v2.0_43438_cramfs_config && make
		fi

		if [ $? -eq 0 ]; then
			cp output/target/appfs.cramfs $IMAGE_DIR
			cp output/target/updater.cramfs $IMAGE_DIR
			cp output/target/usrdata.jffs2 $IMAGE_DIR
		fi
		;;
	-c)
		echo "make distclean ..."
		if [ -d $IMAGE_DIR ];then
			rm $IMAGE_DIR -rf
		fi

		cd $SOURCE_DIR/u-boot && make distclean
		cd $SOURCE_DIR/kernel* && make distclean
		cd $SOURCE_DIR/mozart && make distclean
		return $?
		;;
	\?)
		 echo "Invalid option : `basename $0` [-a] [-k] [-u] [-m] [-c]"
		;;
	esac
done
