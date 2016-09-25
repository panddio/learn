
str=`ps | grep mplayer`
echo "$str"

i=1
for arg in `ps | grep ./mplayer`
do
	if [ $i -eq 1 ]
	then
		kill -9 $arg
		echo "mplayer killed!!"
	fi

	i=$[ $i + 1 ]
done

j=1
for arg2 in `ps | grep mplayer`
do
	if [ $j -eq 1 ]
	then
		kill -9 $arg2
		echo "mplayer killed!!"
		exit
	fi

	j=$[ $j + 1 ]
done
