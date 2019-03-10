
#include "stdio.h"
#include "stdint.h"

#include "rpc/rpc.h"
#include "test2.h"

int32_t main(int32_t argc, char *argv[])
{

	CLIENT *client;
	char **p;
	int a = 10;

	if(argc < 2)
	{
		fprintf(stderr, "usage: %s <hostname> [value (default is 10)]\n", argv[0]);
		exit(1);
	}
	else if(argc == 3)
	{
		a = atoi(argv[2]);
	}


	client = clnt_create(argv[1], RPC_TEST_2_PROG, RPC_TEST_2_VERS, "tcp");
	if(client == NULL)
	{
		clnt_pcreateerror(argv[1]);
		exit(1);
	}

	printf("Getting ready to call server function\n");

	p = f_test2_1(&a, client);

	printf("Back from server function\n");

	if(p == NULL)
	{
		clnt_perror(client, argv[1]);
		exit(1);
	}

//	printf("Returned string = %s\n", *p);

	printf("Returned bytes:\n");
	for(uint32_t i = 0; i < 2048; i++)
	{
		printf("%02X ", (uint8_t)(*p)[i]);
	}
	printf("\n");

	return 0;

}
