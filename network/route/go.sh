#!/bin/bash

clear
echo "compiling the route project..."
rm route
make

if [ -e route ]
then
	echo "running..."
	sudo ./route
fi
