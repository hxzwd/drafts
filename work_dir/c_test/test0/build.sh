#!/bin/bash


#gcc hello.c -o bin_hello -std=c99


rpcgen hello.x
gcc client.c hello_clnt.c -o bin_client -lnsl
gcc server.c hello_svc.c -o bin_server -lnsl


gcc -c server_1.c -o server_1.o -std=c99 -fPIC
gcc -c hello_svc_1.c -o hello_svc_1.o -std=c99 -fPIC
gcc -shared server_1.o hello_svc_1.o -o librpc_test.so -lnsl

