
#include "rpc/rpc.h"
#include "hello.h"


int * hello_1_svc(void *a, struct svc_req *req)
{

	static char msg[256];
//	static char *p;
	static int **p;

	printf("Getting ready to return value\n");

//	strcpy(msg, "Hello, from RPC server\n");
//	p = msg;

	static int data[4] = { 0xFF, 0, 1, -4 };
	p = data;

	printf("Return value...\n");

	return (&p);

}
