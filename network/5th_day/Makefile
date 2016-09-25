all:filch feiQ udp sock_raw arp

filch:
	gcc -o filch filch.c gb2312_ucs2.c

feiQ:
	gcc raw_feiQ.c gb2312_ucs2.c -o feiQ

udp:
	gcc raw_udp.c -o udp

sock_raw:sock_raw.c
	gcc -o sock_raw sock_raw.c

arp:
	gcc -o arp arp.c

.PHONY:clean
clean:
	rm sock_raw feiQ udp filch
