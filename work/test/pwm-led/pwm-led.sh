#!/bin/sh

cd /sys/class/leds/led_state/

val=`cat brightness`

for i in $(seq $val 254)
do
    echo $i
    echo $i > brightness
    usleep 20000
done

for i in $(seq 254 0)
do
    echo $i
    echo $i > brightness
    usleep 20000
done
