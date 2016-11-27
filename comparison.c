#include <stdio.h>
#include <stdlib.h>
#include <obliv.h>
#include <string.h>
#include "comparison.h"

int main (int argc, char *argv[]) {
	printf("Big-Int Oblivious Equality Testing\n");
	printf("================================\n");

	if (argc == 4) {
		const char *remote_host = strtok(argv[1], ":");
		const char *port = strtok(NULL, ":");
		ProtocolDesc pd;
		ProtocolIO *eqt = malloc(sizeof(ProtocolIO));
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
		eqt->data = atoi(argv[3]);

		printf("Executing Yao's Protocol...\n");
		execYaoProtocol(&pd, oblivEqt, eqt);
		cleanupProtocol(&pd);

		printf("Oblivious Equality Testing produced: %d\n", eqt->result);
		free(eqt);
	}
	else {
		printf("Usage: %s <hostname:port> <1|2> <data>  \n"
	    "\tHostname usage:\n"
		"\tlocal -> 'localhost' remote -> IP address or DNS name\n", argv[0]);
	}

	return 0;

}
