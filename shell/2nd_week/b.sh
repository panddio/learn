#!/bin/bash

str=" I love linux.I love UNIX too."
str2="$str"
#str2=${str/love/like}

echo "str =$str"
echo "str2=$str2"
exit
str="I love linux, I love GNU too."

echo ${str%,*.}

exit


echo -n "input a string:"
#read -s -p "input a string:" str
read str

echo "$str"

unset color
echo "the shy is ${color:-grey} today"
echo "$color"

echo "the sky is ${color:=grey} today"
echo "$color"

color=yellow

echo "the shy is ${color:?error} today"
echo "$color"


echo "the shy is ${color:+blue} today"
echo "$color"
