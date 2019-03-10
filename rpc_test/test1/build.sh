#!/bin/bash


#gcc hello.c -o bin_hello -std=c99


rpcgen hello.x
gcc client.c hello_clnt.c -o bin_client -lnsl
gcc server.c hello_svc.c -o bin_server -lnsl

