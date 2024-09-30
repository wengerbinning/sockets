/***************************************************
* file:     testpcap1.c
* Date:     Thu Mar 08 17:14:36 MST 2001
* Author:   Martin Casado
* Location: LAX Airport (hehe)
*
* Simple single packet capture program

*****************************************************/
#include <stdio.h>
#include <stdlib.h>
// #include <pcap.h> /* if this gives you an error try pcap/pcap.h */
#include <errno.h>
#include <time.h>

#include <pcap/pcap.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */

#include <hexdump.h>

/* Ethernet header */
struct sniff_ethernet {
	u_char ether_dhost[ETHER_ADDR_LEN]; /* Destination host address */
	u_char ether_shost[ETHER_ADDR_LEN]; /* Source host address */
	u_short ether_type; /* IP? ARP? RARP? etc */
};

int main(int argc, char *argv[])
{
	pcap_t *handle;			/* Session handle */
	char *dev;			/* The device to sniff on */
	char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
	struct bpf_program fp;		/* The compiled filter */
	char filter_exp[] = "";	/* The filter expression */
	bpf_u_int32 mask;		/* Our netmask */
	bpf_u_int32 net;		/* Our IP */
	struct pcap_pkthdr header;	/* The header that pcap gives us */
	const u_char *packet;		/* The actual packet */
    const struct sniff_ethernet *ethernet; /* The ethernet header */

	/* Define the device */
	dev = pcap_lookupdev(errbuf);
	if (dev == NULL) {
		fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
		return(2);
	}
	/* Find the properties for the device */
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
		fprintf(stderr, "Couldn't get netmask for device %s: %s\n", dev, errbuf);
		net = 0;
		mask = 0;
	}
	/* Open the session in promiscuous mode */
	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL) {
		fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
		return(2);
	}
	/* Compile and apply the filter */
	if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
		fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
		return(2);
	}
	if (pcap_setfilter(handle, &fp) == -1) {
		fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
		return(2);
	}





    /* Grab a packet */
	packet = pcap_next(handle, &header);
	/* Print its length */
    printf("Jacked a packet with length of [%d]\n", header.len);
    hexdump(packet, header.len);
    ethernet = (struct sniff_ethernet*)(packet);
    printf("src: %X , dst: %X, type%04X", ethernet->ether_shost, ethernet->ether_dhost, ethernet->ether_type);


    /* And close the session */
	pcap_close(handle);
	return(0);
}



// <https://www.tcpdump.org/pcap.html>
// <https://stackoverflow.com/questions/71698140/libpcap-pcap-loop-does-not-return-any-packets>