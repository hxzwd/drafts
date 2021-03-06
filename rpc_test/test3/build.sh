#!/bin/bash

XDR_FILE=test3.x
CLIENT_SRC=client.c
SERVER_SRC=server.c

PRJ_NAME=$(echo $XDR_FILE | cut -d "." -f1)

rpcgen $XDR_FILE
gcc $CLIENT_SRC "$PRJ_NAME"_clnt.c "$PRJ_NAME"_xdr.c -o bin_client -lnsl
gcc $SERVER_SRC "$PRJ_NAME"_svc.c "$PRJ_NAME"_xdr.c -o bin_server -lnsl

