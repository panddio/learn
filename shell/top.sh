#!/bin/bash

HEADFLAGD="-n 20"
PSFLAGS=aux
SLEEPFLAGS=2
SORTFLAGS=`-k3nr -k1,1 -k2n`

HEADER="`ps $PSFLAGS | head -n 1`"

while true
do
	clear
	uptime
	echo "$HEADER"
	ps $HEADER |
		sed -e ld |
			sort $SORTFLAGS |
				head $HEADFLAGD

	sleep $SLEEPFLAGS
done
