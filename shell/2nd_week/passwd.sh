#!/bin/bash

IFS.OLD=$IFS

IFS=$'\n'
for entry in `cat /etc/passwd`
do
	echo "value in $entry"
	IFS=:
	for value in $entry
	do
		echo "$value"
	done
done

IFS=$IFS.OLD
