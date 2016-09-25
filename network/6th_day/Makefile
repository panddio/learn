all:pcap libnet

pcap:
	gcc -o pcap pcap_test.c -lpcap

libnet:
	gcc -o libnet libnet_test.c -lnet


.PHONY:clean
clean:
	rm pcap libnet
