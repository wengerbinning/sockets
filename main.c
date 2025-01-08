#include <stdio.h>


#include "proto/ethernet.h"

#include "hexdump.h"


int main(int argc, char *argv[]) {
    unsigned char buffer[ETHHDRIZE] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
        0x10, 0x20, 0x30, 0x40, 0x50, 0x60,
        0xaa, 0xbb
    };
    hexdump(buffer, ETHHDRIZE);
    eth_hdr_t *eth = (eth_hdr_t *)buffer;


    printf("Dst Addr: " ETH_ADDR_FMT3 ", IEEE: %s, Multicast: %s\n",
        ETH_ADDR2STR(eth->dst.addr),
        eth->dst.flags.gl ? "true": "false",
        eth->dst.flags.ig ? "true": "false");
    printf("Src Addr: " ETH_ADDR_FMT3 ", IEEE: %s, Multicast: %s\n",
        ETH_ADDR2STR(eth->src.addr),
        eth->src.flags.gl ? "true": "false",
        eth->src.flags.ig ? "true": "false");


    printf("Ethernet: 0x%04X\n", eth->type);







    return 0;
}