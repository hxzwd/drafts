
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#include "rpc/rpc.h"
#include "test3.h"


st_rpc_array * f_test3_1_svc(st_rpc_array *a, struct svc_req *req)
{

	static char msg[256];
	static int data[16384] = { 0 };
	uint32_t words_readed;
	static st_rpc_array out;
	out.st_rpc_array_len = 0;
	out.st_rpc_array_val = NULL;
	static char *p;
	FILE *fd;

	if((fd = fopen("random_data.bin", "rb")) == NULL)
	{
		fprintf(stderr, "Error: can not open file\n");
		sprintf(msg, "Error: can not open file: random_data.bin\n");
		p = msg;
		fprintf(stderr, "Return error...\n");
		return NULL;
//		return (&out);
//		return (&p);
	}

	printf("Receive argument a [typeof(a) = st_rpc_array *]:\n");
	printf("a->st_rpc_array_len = %d\n", a->st_rpc_array_len);
	for(uint32_t i = 0; i < a->st_rpc_array_len; i++)
	{
		printf("a->st_rpc_array_val[%d] = %02X\n", i, a->st_rpc_array_val[i]);
	}
	printf("\n");

	printf("Getting ready to return value\n");

//	strcpy(msg, "Hello, from RPC server\n");
//	sprintf(msg, "Hello, from RPC server [argument is %d]\n", *a);
//	p = msg;

	uint32_t data_len = 65536/4;
//	words_readed = fread(data, 4, 65536/4, fd);
	words_readed = fread(data, 4, data_len, fd);
	fclose(fd);
	printf("Words readed: %d\n", words_readed);

/*
	for(uint32_t i = 0; i < 65536/4; i++)
	{
		printf("%08X ", data[i]);
	}
	printf("\n\n");
*/

	printf("Return value...\n");

	out.st_rpc_array_len = data_len;
	out.st_rpc_array_val = (int *)data;

	return (&out);

//	p = data;
//	return (&p);

//	return (&p);

}
