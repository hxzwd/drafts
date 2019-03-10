
#include "stdio.h"
#include "stdint.h"

#include "rpc/rpc.h"
#include "test3.h"

int32_t main(int32_t argc, char *argv[])
{

	CLIENT *client;
	char **p;
	int a = 10;
	st_rpc_array arg;
	static int arg_data[] = { 0xFF, 0xDD, 0xEE, 0xCC, 0xBB, 0xAA, 0xF0, 0xAF };
	int arg_data_len = 8;
	arg.st_rpc_array_len = arg_data_len;
	arg.st_rpc_array_val = (int *)arg_data;


	if(argc != 2)
	{
		fprintf(stderr, "usage: %s <hostname>\n", argv[0]);
		exit(1);
	}

	client = clnt_create(argv[1], RPC_TEST_3_PROG, RPC_TEST_3_VERS, "tcp");
	if(client == NULL)
	{
		clnt_pcreateerror(argv[1]);
		exit(1);
	}

	printf("Getting ready to call server function\n");

	p = f_test3_1(&arg, client);

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
