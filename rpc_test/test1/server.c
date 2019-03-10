
#include "rpc/rpc.h"
#include "hello.h"


char ** hello_1_svc(void *a, struct svc_req *req)
{

	static char msg[256];
	static char *p;

	printf("Getting ready to return value\n");

	strcpy(msg, "Hello, from RPC server\n");

	p = msg;

	printf("Return value...\n");

	return (&p);

}
