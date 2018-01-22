#!/bin/bash

name=`ls *.ko`

if [ -z "$name" ]
then
	exit 1
fi

devname=${name%.ko}
devno=
#echo "devname=$devname"

if [ -z "`cat /proc/devices | grep $devname`" ]
then
	echo "$devname haven't installed!"
	exit 1
fi

#echo "$devno  $devname"

if [ -e /dev/$devname ]
then
	sudo rm /dev/$devname

	if [ $? -eq 0 ]
	then
		echo "remove /dev/$devname successful"
	fi
fi

sudo rmmod $devname

if [ $? -eq 0 ]
then 
	echo "uninstall $devname successful"
fi
