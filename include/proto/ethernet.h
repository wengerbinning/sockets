#ifndef __PROTO_ETHERNET_H__
#define __PROTO_ETHERNET_H__

#define ETHHDRIZE  14
#define ETHADDRIZE  6
#define ETHTYPEIZE  2

#define ETHADDRIZE_OUI    3
#define ETHADDRIZE_EUI    3

/* Ethernet Address APIs
 - ETH_ADDR_FMT0:
 - ETH_ADDR_FMT1:
 - ETH_ADDR_FMT2:
 - ETH_ADDR_FMT3:
 - STR2ETH_ADDR(addr):
 - ETH_ADDR2STR(addr):
 */
#define ETH_ADDR_FMT0 "%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx"
#define ETH_ADDR_FMT1 "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx"
#define ETH_ADDR_FMT2 "%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX"
#define ETH_ADDR_FMT3 "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX"
#define _STR2ETH_ADDR(a) &(a)[0], &(a)[1], &(a)[2], &(a)[3], &(a)[4], &(a)[5]
#define _ETH_ADDR2STR(a)  (a)[0],  (a)[1],  (a)[2],  (a)[3],  (a)[4],  (a)[5]
#define STR2ETH_ADDR(addr) _STR2ETH_ADDR((unsigned char *)(addr))
#define ETH_ADDR2STR(addr) _ETH_ADDR2STR((unsigned char *)(addr))

/* eth_addr_t - ethernet addreess
 - addr: unsigned char [ETHADDRIZE]
 - oui:  unsigned char [ETHADDRIZE_OUI]
 - eui:  unsigned char [ETHADDRIZE_EUI]
 */
typedef union eth_addr {
    unsigned char addr[ETHADDRIZE];
    struct {
        unsigned char oui[ETHADDRIZE_OUI];
        unsigned char eui[ETHADDRIZE_EUI];
    };
    struct {
        unsigned char ig:1;
        unsigned char _resv0:6;
        unsigned char gl:1;
    } flags;
} eth_addr_t;

/* eth_type_t - ethernet type
 - data: unsigned char [ETHTYPEIZE]
 - type: unsigned short
 */
typedef union eth_type {
    unsigned char data[ETHTYPEIZE];
    unsigned short type;
} eth_type_t;

/* eth_hdr_t - ethernet header
 - dst: eth_addr_t
 - src: eth_addr_t
 - type: eth_type_t
 */
typedef union eth_hdr {
    unsigned char data[ETHHDRIZE];
    struct {
        eth_addr_t dst;
        eth_addr_t src;
        eth_type_t type;
    };
} eth_hdr_t;


#endif /* __PROTO_ETHERNET_H__ */