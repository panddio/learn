#!/bin/sh

/usr/fs/etc/init.d/S04bsa.sh stop
iwconfig wlan0 txpower off
ifconfig wlan0 down
