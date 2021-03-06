#include <stdio.h>
#include <stdlib.h>
#include <obliv.h>
#include <string.h>
#include "max.h"

int main (int argc, char *argv[]) {
	printf("Big-Int Oblivious Maximum\n");
	printf("================================\n");

	if (argc == 4) {
		const char *remote_host = strtok(argv[1], ":");
		const char *port = strtok(NULL, ":");
		ProtocolDesc pd;
		ProtocolIO *max = malloc(sizeof(ProtocolIO));
		int currentParty;

		printf("Connecting to %s on port %s .. \n", remote_host, port);

		if(argv[2][0] == '1') {
      		if(protocolAcceptTcp2P(&pd,port)!=0) {
				printf("TCP accept from %s failed\n", remote_host);
				exit(1);
      		}
    	}
   		else {
      		if(protocolConnectTcp2P(&pd,remote_host,port)!=0) {
				printf("TCP connect to %s failed\n", remote_host);
				exit(1);
			}
		}
		printf("Establishing parties...\n");
		currentParty = (argv[2][0] =='1'?1:2);
		setCurrentParty(&pd, currentParty);
		max->data = atoi(argv[3]);

		printf("Executing Yao's Protocol...\n");
		execYaoProtocol(&pd, oblivMax, max);
		cleanupProtocol(&pd);

		printf("Oblivious Maximum produced: %d\n", max->result);
		free(max);
	}
	else {
		printf("Usage: %s <hostname:port> <1|2> <data>  \n"
	    "\tHostname usage:\n"
		"\tlocal -> 'localhost' remote -> IP address or DNS name\n", argv[0]);
	}

	return 0;

}


