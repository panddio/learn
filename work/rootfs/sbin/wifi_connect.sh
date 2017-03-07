#!/bin/sh

INTERFACE=wlan0
WPA_CONF=/etc/wpa_supplicant.conf

# wpa_supplicant config file
if [ ! -f "$WPA_CONF" ]; then
	echo "No configuration file"
	exit 0
fi

ifconfig $INTERFACE up
wpa_supplicant -Dnl80211 -i$INTERFACE -c$WPA_CONF -B
usleep 1300000
udhcpc -i $INTERFACE -q

exit 0

