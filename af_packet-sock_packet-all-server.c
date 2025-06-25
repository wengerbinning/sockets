#include <linux/if_ether.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "develop.h"
#include "tools.h"

#include "ethertype.h"

int main (int argc, char argv[]) {
	int sock, clisock;
	struct sockaddr addr;
	struct sockaddr_in cliaddr;
	int addrlen;
	int ret;
	char buffer[1024];


	if ((sock = socket(PF_PACKET, SOCK_PACKET, htons(ETH_P_ALL))) < 0) {
		error("Failed to create socket!");
		exit(sock);
	}

	strcpy(addr.sa_data, "eth0");

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr))) {
		error("Failed to bind address!");
		exit(0);
	}

	debug("Running in Server ...");

	while (1) {
		if ((ret = recv(sock, buffer, sizeof(buffer), 0)) < 0) {
			error("Failed to Receive!");
			close(sock);
			exit(-1);
		}

		debug("receive %d data", ret);
	}


	return 0;
}


struct sock_proto_ops {
	int init(ctx);
	int send(ctx, buf, size);
	int recv(ctx, buf, size);
	int exit(ctx);
};

struct sock_proto {
	char * name;
	struct sock_proto_ops *ops;
};

struct sock_context {
	int flags, sock;

}

sock_init(ctx, ethernet)
sock_bind(ctx, iface)
sock_listen(ctx, addr, port)
sock_send(ctx, buf, size)
sock_recv(ctx, buf, size)
sock_exit(ctx)










init ethernet
bind eth0
send frame-1
recv frame-2
exit ethernet


init ethernet
bind eth0
recv frame-a
send frame-b
exit ethernet




init tcp
bind 192.168.122.0, 0
conn 192.168.122.0, 20
quit 12
exit tcp


queue  test
