#!/bin/bash

name=`ls *.ko`

if [ -z "$name" ]
then
	exit 1
fi

devno=
devname=${name%.ko}
#echo "devname = $devname"

if [ -n "`cat /proc/devices | grep $devname`" ]
then
	sudo rmmod $devname

	if [ -e /dev/$devname ]
	then
		sudo rm /dev/$devname
	fi
fi

echo "installing $name"
sudo insmod ./$name

if [ $? -eq 0 ]
then
	echo "install $name successful"
else
	echo "Cannot install $name"
	exit 1
fi

#以下是为了创建设备文件
i=1

for arg in `cat /proc/devices | grep "$devname"`
do
	if [ $i -eq 1 ]
	then
		devno=$arg
	fi
	i=$[ $i + 1 ]
done
#echo "#$devno#   #$devname#"

#cd /dev
if [ ! -e /dev/$devname ]
then
	sudo mknod /dev/$devname c $devno 0

	if [ $? -eq 0 ]
	then
		echo "Create device file successful"
	fi
fi
