#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "socket.h"
#include "develop.h"



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


static char chrs[] = "b:hi:psvPV";
static struct option opts[__OPT_MAX] = {
    [OPT_HELP]     = {"help",       no_argument,       'h', 0},
    [OPT_VERISON]  = {"version",    no_argument,        0, 0},
    [OPT_VERBOSE]  = {"verbose",    optional_argument,  0, 0},
    [OPT_INTEFACE] = {"interface",  required_argument,  0, 0},
    [OPT_PORT]     = {"port",       required_argument,  0, 0},
    [OPT_BIND]     = {"bind",       required_argument,  0, 0},
    [OPT_SERVER]   = {"server",     no_argument,        0, 0},
    [OPT_PARALLEL] = {"parallel",   required_argument,  0, 0},

    [OPT_DATA_BIN_PACKET] = {"binary",  no_argument,  0, 0},

};

/*

    -h, --help
    -v, --version
    --verbose
    --force
    --debug
    --queit

    --interface
    --port
    --tcp
    --udp

    --8021q
    --8021d
    --vid
    --cvid
    --svid
    --cpri
    --spri

8021 Frame






Ethernet Frame
---------------
	--ethernet
	--srcmac <MAC ADDR>
	--dstmac <MAC ADDR>
	--ethtype <ETHTYPE>
	--payload <PADLOAD>

8021Q Frame
------------
	--8021q
	--pri <PRI>
	--dei
	--vid <VID>

8021ad Frame
-------------

	--8021ad
	--spri <S PRI>
	--sdei
	--svid <S VID>
	--cpri <C PRI>
	--cdei
	--cvid <C VID>

IPv4 Packet
------------
	--ipv4

	--srcaddr
	--dstaddr

IPv6 Package
------------
	--ipv6
	--srcaddr
	--dstaddr


UDP Dream
----------
	--udp
	--port

TCP Stream
----------
	--tcp
	--port



	--listen
	--output <file>


 */



enum options_idx {
	OPT_HELP,
	OPT_VERISON,
	/* Common option */
	OPT_VERBOSE,
	OPT_INTEFACE,
	OPT_BIND,
	OPT_PORT,
	/* Server option */
	OPT_SERVER,
	/* Client option */
	OPT_PARALLEL,
	OPT_DATA_BIN_PACKET,
	OPT_DATA_XML_PACKET,

	__OPT_MAX
};



struct argment {
	int flags;
	char chr, *opt, *msg;
};











static char prog_name[] ="socket";
static char short_options[] = "b:hi:psvPV";
static struct option long_options[__OPT_MAX] = {
	[OPT_HELP]     = {"help",       no_argument,       0, 0},
	[OPT_VERISON]  = {"version",    no_argument,       0, 0},
	[OPT_VERBOSE]  = {"verbose",    optional_argument, 0, 0},
	[OPT_INTEFACE] = {"interface",  required_argument, 0, 0},
	[OPT_PORT]     = {"port",       required_argument, 0, 0},
	[OPT_BIND]     = {"bind",       required_argument, 0, 0},
	[OPT_SERVER]   = {"server",     no_argument,       0, 0},
	[OPT_PARALLEL] = {"parallel",   required_argument, 0, 0},

	[OPT_DATA_BIN_PACKET] = {"binary", 	no_argument, 	0, 0},

};

static struct socket_param_t param;

int help (const char *prog);
int version (const char *prog);
int dump_param (const struct socket_param_t *param);

static inline int parse_long_options (const struct option *opt, int idx, struct socket_param_t *param) {
	switch (idx) {
	case OPT_HELP:
		help(prog_name);
		return 0;
	case OPT_VERBOSE:
		param->verbose = 1;
		break;
	case OPT_VERISON:
		version(prog_name);
		return 0;
	case OPT_INTEFACE:
		param->iface = optarg;
		break;
	case OPT_SERVER:
		param->server = 1;
		break;

	default:
		warning("Unknown handling this option: --%s", opt[idx].name);
	}
}

int main (int argc, char *argv[]) {
	int opt, idx;

	char buffer[64];
    int i;

	if (argc <= 1) {
		help(argv[0]);
		return 0;
	}

	while ((opt = getopt_long(argc, argv, short_options, long_options, &idx)) != -1) {
		switch (opt) {
		/* Handing long options. */
		case 0:
			parse_long_options(long_options, idx, &param);
			break;

		/* Handling short options. */
		case 'b':
			strncpy(param.address, optarg, sizeof(param.address));
			break;
		case 'h':
			help(argv[0]);
			return 0;
		case 'i':
			param.iface = optarg;
			break;
		case 's':
			param.server = 1;
			break;
		case 'v':
			param.verbose = 1;
			break;
		case 'V':
			version(argv[0]);
			return 0;

		/* Handle invalid option. */
		case '?':
		/* Handle unknown valid option. */
		default:
			warning("Unknown handling this option: -%c", opt);
			help(argv[0]);
			return 0;
		}
	}

    if (optind < argc) {
        for (i = optind; i < argc; i++) {
            if (param.verbose) printf("argv[%d] =  %s\n", i, argv[i]);
			param.file = argv[i];
        }
    }

	dump_param(&param);

    pf_packet_packet_all(&param);




	return 0;
}



int help (const char *prog) {
	info("%s - This is a network debug tools.\n", prog);
	info("Usage: %s [OPTIONS] <packet file>\n", prog);
	info("\nOptions:\n");
	info("\t-h, --help                  \tDisplay help information and exit");
	info("\t-i, --interface INTERFACE   \tBind interface");
	info("\t-v, --verbose               \tPrint detial inforation");
	info("\t-V, --version               \tDisplay version information and exit");
	return 0;
}

int version (const char *prog) {
	info("%s Version v0.0.0.1", prog);
	return 0;
}

int dump_param (const struct socket_param_t *param) {
	debug("Display param value:");
	info("\tinterface: %s", param->iface);
	info("\tserver : %d", param->server);
	info("\tpacket file: %s", param->file);
	info("");
	return 0;
}
