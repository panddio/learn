#!/bin/sh
#########################################################################
########################################################################
# 3. a real report:
#./R_inand-cptest.sh
#########################################################################

#clear
i=0
#export PATH=$PATH:/mnt/sdcard
#测试次数
num=/mnt/sdcard/testlog/set.txt

#校准文件MD5
chk_md5=/mnt/sdcard/testlog/check.md5
tmp_md5=/mnt/sdcard/testlog/tmp.md5

#测试次数
if test ! -e $num; then
 echo Not find $num,test stop !!!
 read
 exit 1
fi
#n=`cat $num`

#get_md5file
get_md5() # $path
{
 cd $1
 busybox find ./ -type f -print0 |busybox xargs -0 busybox md5sum|busybox  sort >$tmp_md5
}

#get_diff
get_diff()
{
  busybox diff $chk_md5 $tmp_md5 >/dev/null
  if [ $? -ne 0 ];then
    echo ---------------------------------------------
    echo  The number $i Test copy NG!
    echo  Test copy NG! >>$nlog
    read
  else
    echo ---------------------------------------------
    echo  The number $i Test copy OK!
    echo  Test copy OK! >>$nlog
  fi
}


#####################测试资源文件######################
star=/mnt/sdcard/scrda
if test ! -d $star; then
 mkdir -p $star
fi

busybox tar -xvf  /mnt/sdcard/custdata.tar -C $star  >/dev/null
if test ! -d $star; then
 echo Not find $star,test stop !!!
 read
 exit 1
fi

#################测试目标文件######################
tmp=`cat /mnt/sdcard/ter.txt`

if test ! -d $tmp; then
 mkdir -p $tmp
fi

if test ! -d $tmp; then
 echo Not find $tmp,test stop !!!
 read
fi


###################测试日志文件########################
if test ! -d /mnt/sdcard/testlog; then
 mkdir -p /mnt/sdcard/testlog
fi
nlog=/mnt/sdcard/testlog/n.txt
#elog=/mnt/sdcard/testlog/err.txt


##############检测拷贝过程#################


echo
echo ================== Test cycle start ==================
echo

#*********************************************************
while [ $i -le 1000 ]
do
  let i=$i+1

  echo ===========current num $i scrda to tmpda============
  echo current num $i scrda to tmpda >$nlog
  busybox rm -r $tmp
  mkdir -p $tmp
  busybox cp -r $star/*  $tmp
  # get_md5 $tmp
  # get_diff

  echo

  echo ===========current num $i tmpda to scrda============
  echo current num $i tmpda to scrda >$nlog
  busybox rm -r $star
  mkdir -p $star
  busybox cp -r $tmp/* $star

  # get_md5 $star
  # get_diff

  echo
  echo
  #n=`cat $num`
done
#*********************************************************

echo
echo ============@@@ copy test over @@@=============
read
exit 1
