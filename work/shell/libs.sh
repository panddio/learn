#!/bin/bash

i=0
libs="ld-2.16.so
ld.so.1
libc-2.16.so
libcrypto.so
libcrypto.so.1.0.0
libc.so.6
libdl-2.16.so
libdl.so.2
libm-2.16.so
libm.so.6
libnss_dns-2.16.so
libnss_dns.so.2
libnss_files-2.16.so
libnss_files.so.2
libpthread-2.16.so
libpthread.so.0
libresolv-2.16.so
libresolv.so.2
librt-2.16.so
librt.so.1

libnl-3.so
libnl-3.so.200
libnl-3.so.200.19.0
libnl-genl-3.so
libnl-genl-3.so.200
libnl-genl-3.so.200.19.0
libssl.so
libssl.so.1.0.0"

#for line in `cat libs`
for line in $libs
do
    echo "line$i = $line"
    i=$[ $i + 1 ]
done

