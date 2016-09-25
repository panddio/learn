#!/bin/sh

#auto get ip
#udhcpc

#config ip netmask gw
ifconfig eth0 10.221.2.112 netmask 255.255.255.0
route add default gw 10.221.2.254

serverip=10.221.2.221
serverpath=/home/edu
localpath=/mnt

echo "usage:./mount_nfs serverip serverpath localpath"
if [ -z $serverip ]; then
	echo "serverip is NULL"
	exit 1
fi
if [ -z $serverpath ]; then
	echo "serverpath is NULL"
	exit 1
fi
if [ -z $localpath ]; then
	localpath=/mnt/nfs
	echo "localpath default /mnt/nfs"
fi

mount -o nolock,wsize=1024,rsize=1024 $serverip:$serverpath $localpath


if [ $? = 0 ]; then
	echo "nfs mount succeed!!"
	echo "if you want to umount the serverpath"
	echo "please input umount like this: umount /mnt"
else
	echo "nfs mount failed,please check and try again!!"
fi
