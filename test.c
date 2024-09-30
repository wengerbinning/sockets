#include <stdio.h>
// #include <stdlib.h>

#include <pcap/pcap.h>


int main (int argc, char *argv[]) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldev, *dev;


    if (0 <= pcap_findalldevs(&alldev, errbuf)) {
        dev = alldev;

        do {
            printf("%s loopback: %s, connect: %s, up: %s\n",
                dev->name,
                (dev->flags & PCAP_IF_LOOPBACK) ? "true": "false",
                (dev->flags & PCAP_IF_CONNECTION_STATUS_CONNECTED) ? "true": "false",
                (dev->flags & PCAP_IF_UP) ? "true": "false");
            dev = dev->next;
        } while (dev);

        pcap_freealldevs(alldev);
    }



    return 0;
}




// <https://www.tcpdump.org/manpages/pcap_findalldevs.3pcap.html>