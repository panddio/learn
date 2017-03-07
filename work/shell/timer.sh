#!/bin/sh

for i in $(seq 1 2)
do
	sleep 20s
	echo "20s later..."
done

echo "reboot system now..."
reboot
