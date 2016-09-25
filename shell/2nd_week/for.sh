#!/bin/bash

for file in $HOME/share/*.c ../homework/*
do
	if [ -d "$file" ]
	then
		echo "$file is a directory"
	elif [ -f "$file" ]
	then
		echo "$file is a file"
	fi
done >output.txt

for ((i=0;i<4;i++))
do
	echo "the number is $i"
done

for state in Shanghai Beijing Guangzhou Zhanjiang "New York"
do
	echo "$state is the next place to go"
done | sort
