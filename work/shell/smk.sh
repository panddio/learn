#!/bin/bash
#
# Copyright (C) 2016 Ingenic Semiconductor, Inc.
# Wang Qiuwei <qiuwei.wang@ingenic.com, panddio@163.com>

#
# Build config seting
if [ "nand" = "$1" ]; then
UBOOT_BUILD_CONFIG=halley2_v20_zImage_sfc_nand
KERNEL_BUILD_CONFIG=halley2_v20_sfc_nand_defconfig
MOZART_BUILD_CONFIG=halley2_v2.0_43438_ubifs_config
MOZART_TARGET_FILE="appfs.img  updater.img  nv.img"
else
UBOOT_BUILD_CONFIG=halley2_v10_zImage_sfc_nor_config
KERNEL_BUILD_CONFIG=halley2_v10_nor_oss_defconfig
MOZART_BUILD_CONFIG=halley2_v2.0_43438_cramfs_config
MOZART_TARGET_FILE="appfs.cramfs  updater.cramfs  usrdata.jffs2  nv.img"
fi

UBOOT_TARGET_FILE=u-boot-with-spl.bin
KERNEL_IMAGE_PATH=arch/mips/boot/compressed
KERNEL_TARGET_FILE=zImage
MOZART_IMAGE_PATH=output/target

#
# Multithread compiling
MP=8

echoc()
{
    echo -e "\e[0;91m$1\e[0m"
}

usage()
{
    echoc "---------------------------------------------------------------------------"
    echo "\
    usage:
      smk [OPTIONS]
        used to quickly compile the mozart
        support invoke from any location
        image output directory: $OUTPUT_DIR

      OPTIONS:
        -a | --all        ---> make all
        -u | --uboot      ---> make uboot
        -k | --kernel     ---> make kernel
        -m | --mozart     ---> make mozart
        -c | --clean      ---> distclean uboot、kernel、mozart, or all
        -j | --jobs       ---> set multithread compiling
        -s | --setupinfo  ---> get setup informations
        -h | --help       ---> get help message

      eg:
        smk -m       ---> will make mozart
        smk -u -k    ---> will make uboot and kernel
        smk -j 8     ---> will set number of jobs to -j8
        smk -c k     ---> will distclean kernel
        smk -c       ---> will distclean all, include the \$OUTPUT_DIR"
    echoc "---------------------------------------------------------------------------"
    return 0
}

setupinfo()
{
    echoc "---------- smk envsetup ---------------------------------------------------"
    echo " SOURCE_DIR = $SOURCE_DIR"
    echo " TOOLCHAINS = $TOOLCHAINS"
    echo "MKIMAGE_DIR = $MKIMAGE_DIR"
    echo " OUTPUT_DIR = $OUTPUT_DIR"
    echo "export PATH = \$TOOLCHAINS:\$MKIMAGE_DIR:\$PATH"
    echo ""
    echo " UBOOT_BUILD_CONFIG = $UBOOT_BUILD_CONFIG"
    echo "KERNEL_BUILD_CONFIG = $KERNEL_BUILD_CONFIG"
    echo "MOZART_BUILD_CONFIG = $MOZART_BUILD_CONFIG"
    echo ""
    echo " UBOOT_TARGET_FILE = $UBOOT_TARGET_FILE"
    echo "KERNEL_TARGET_FILE = $KERNEL_TARGET_FILE"
    echo "MOZART_TARGET_FILE = $MOZART_TARGET_FILE"
    echoc "---------- If need help: smk -h -------------------------------------------"
}

envsetup()
{
    local dir=$(pwd)
    SOURCE_DIR=$dir

    while true; do
        if [ -d $SOURCE_DIR/mozart -a \
             -d $SOURCE_DIR/u-boot -a \
             -d $SOURCE_DIR/kernel* ]; then
            break
        fi

        if [ x$SOURCE_DIR == x ]; then
            echoc "Error, please read tools/README"
            return -1;
        fi
        SOURCE_DIR=${SOURCE_DIR%/*}
    done

    OUTPUT_DIR=$SOURCE_DIR/out
    MKIMAGE_DIR=$SOURCE_DIR/u-boot/tools
    TOOLCHAINS=$SOURCE_DIR/tools/toolchains/mipsel-gcc472-glibc216-mips32/bin

    if [ -d $TOOLCHAINS ]; then
        export PATH=$TOOLCHAINS:$PATH;
    else
        echoc "TOOLCHAINS is not exist! Please read tools/README"
        return -1
    fi

    if [ -d $MKIMAGE_DIR ]; then
        export PATH=$MKIMAGE_DIR:$PATH
    fi

    if [ ! -d $OUTPUT_DIR ]; then
        mkdir -p $OUTPUT_DIR
        if [ $? -ne 0 ]; then
            echoc "Create $OUTPUT_DIR failed, set OUTPUT_DIR=\$SOURCE_DIR"
            OUTPUT_DIR=$SOURCE_DIR
        fi
    fi

    setupinfo
}
declare -f croot > /dev/null || envsetup

make_uboot()
{
    echoc "\nsmk: compiling u-boot ..."
    cd $SOURCE_DIR/u-boot

    make $UBOOT_BUILD_CONFIG && make -j$MP

    if [ $? -eq 0 ]; then
        cp $UBOOT_TARGET_FILE $OUTPUT_DIR
    else
        echoc "Failed to compile uboot, try 'smk -c u', then 'smk -u'"
        return -1
    fi

    return 0
}

make_kernel()
{
    echoc "\nsmk: compiling kernel ..."
    cd $SOURCE_DIR/kernel*

    make $KERNEL_BUILD_CONFIG && make $KERNEL_TARGET_FILE -j$MP

    if [ $? -eq 0 ]; then
        cp $KERNEL_IMAGE_PATH/$KERNEL_TARGET_FILE $OUTPUT_DIR
    else
        echoc "Failed to compile kernel, try 'smk -c k', then 'smk -k'"
        return -1
    fi

    return 0;
}

make_mozart()
{
    echoc "\nsmk: compiling mozart ..."
    cd $SOURCE_DIR/mozart

    make $MOZART_BUILD_CONFIG && make

    if [ $? -eq 0 ]; then
        cd $MOZART_IMAGE_PATH
        cp $MOZART_TARGET_FILE $OUTPUT_DIR
    else
        echoc "Failed to compile mozart, try 'smk -c m', then 'smk -m'"
        return -1
    fi

    return 0
}

make_clean()
{
    case "$1" in
    u | uboot)
        echoc "smk: clean uboot ..."
        cd $SOURCE_DIR/u-boot && make distclean
        ;;
    k | kernel)
        echoc "smk: clean kernel ..."
        cd $SOURCE_DIR/kernel* && make distclean
        ;;
    m | mozart)
        echoc "smk: clean mozart ..."
        cd $SOURCE_DIR/mozart && make distclean
        ;;
    all|*)
        echoc "smk: clean all ..."

        if [ -d $OUTPUT_DIR -a $OUTPUT_DIR != $SOURCE_DIR ]; then
        rm $OUTPUT_DIR -rf
        fi

        cd $SOURCE_DIR/u-boot && make distclean
        cd $SOURCE_DIR/kernel* && make distclean
        cd $SOURCE_DIR/mozart && make distclean
        break
        ;;
    esac

    return 0
}

set_jobs()
{
    case "$1" in
    [1-9][0-9] | [1-9])
        MP=$1
        echoc "smk: set MP=$MP"
        ;;
    *)
        echoc "Invalid param, eg: smk -j 8"
        return -1
        ;;
    esac

    return 0
}

smk()
{
    local dir=$(pwd)

    if [ $# -eq 0 ]; then
        usage
        return $?
    fi

    if [ ! -d $OUTPUT_DIR ]; then
        mkdir -p $OUTPUT_DIR
        if [ $? -ne 0 ]; then
            echoc "Create $OUTPUT_DIR failed, set OUTPUT_DIR=\$SOURCE_DIR"
            OUTPUT_DIR=$SOURCE_DIR
        fi
    fi

    while [ $# -gt 0 ]
    do
        case $1 in
        -a | --all)
            echoc "smk: compiling all ..."
            make_uboot && make_kernel && make_mozart
            break
            ;;

        -k | --kernel)
            make_kernel || break
            ;;

        -u | --uboot)
            make_uboot || break
            ;;

        -m | --mozart)
            make_mozart || break
            ;;

        -c | --clean)
            shift
            make_clean $1
            break
            ;;

        -j | --jobs)
            shift
            set_jobs $1
            return $?
            ;;

        -s | --setupinfo)
            setupinfo
            return $?
            ;;

        -h | --help)
            usage
            return $?
            ;;

        *)
            echoc "Invalid option '$1', if need help: smk -h"
            return -1
            ;;
        esac
        shift
    done

    cd $dir
    echoc "smk: done !!!"
    return 0
}

# auto complete
_smk()
{
    local cur=${COMP_WORDS[COMP_CWORD]}
    local prev=${COMP_WORDS[COMP_CWORD-1]}
    local penult=${COMP_WORDS[COMP_CWORD-2]}

    [[ "$cur" == "" && "$prev" == "=" ]] && return 0


    local flag_preset="no"
    local flag_separate="no"
    local full_args="--jobs --all --uboot --kernel --mozart --clean --setupinfo --help"

    if [[ "$cur" == * ]]; then
        if (( $COMP_CWORD == 1 )); then
            COMPREPLY=( $( compgen -W "$full_args" -- $cur ) )
        else
            for i in "${COMP_WORDS[@]}"
            do
                [ "$i" == "$cur" ] && break
                case "$i" in
                --all|--clean|--help|--setupinfo|-j) return ;;
                --uboot) flag_separate="yes"; full_args=`echo "$full_args" | sed "s/--uboot//g"` ;;
                --kernel) flag_separate="yes"; full_args=`echo "$full_args" | sed "s/--kernel//g"` ;;
                --mozart) flag_separate="yes"; full_args=`echo "$full_args" | sed "s/--mozart//g"` ;;
                esac
            done
            COMPREPLY=( $( compgen -W "$full_args" -- $cur ) )
        fi
    fi
    return 0
}

complete -F _smk smk
