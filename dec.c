#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <obliv.h>
#include <time.h>
#include "dec.h"

#define ROWS 500
#define COLUMNS 10

int main (int argc, char *argv[])
{
time_t start, end;
        printf("Oblivious Distributed ID3\n");
        printf("================================\n");
        
        if (argc == 4) {
            const char *remote_host = strtok(argv[1], ":");
            const char *port = strtok(NULL, ":");
            ProtocolDesc pd;
            ProtocolIO *dec = malloc(sizeof(ProtocolIO));
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
            dec->filename = argv[3];
            
            printf("Executing Yao's Protocol...\n");
            
        	start=clock();
            execYaoProtocol(&pd, oblivDec, dec);
            end=clock();
            cleanupProtocol(&pd);
                      
            printf("Oblivious ID3 produced: %d\n", dec->result);
            free(dec);
        }
        else {
            printf("Usage: %s <hostname:port> <1|2> <data>  \n"
                   "\tHostname usage:\n"
                   "\tlocal -> 'localhost' remote -> IP address or DNS name\n", argv[0]);
        }
                       
        printf("Time required for execution:", (end - start)/CLOCKS_PER_SEC ,"seconds");
        return 0;
        
    }
