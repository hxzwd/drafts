
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#include "rpc/rpc.h"
#include "test2.h"


char ** f_test2_1_svc(int *a, struct svc_req *req)
{

	static char msg[256];
	static char data[2049] = { 0 };
	uint32_t bytes_readed;
	static char *p;
	FILE *fd;

	if((fd = fopen("random_data.bin", "rb")) == NULL)
	{
		fprintf(stderr, "Error: can not open file\n");
		sprintf(msg, "Error: can not open file: random_data.bin\n");
		p = msg;
		fprintf(stderr, "Return error...\n");
		return (&p);
	}

	printf("Getting ready to return value\n");

//	strcpy(msg, "Hello, from RPC server\n");
//	sprintf(msg, "Hello, from RPC server [argument is %d]\n", *a);
//	p = msg;

	bytes_readed = fread(data, sizeof(char), 2048, fd);
	fclose(fd);
	printf("Bytes readed: %d\n", bytes_readed);


	printf("Return value...\n");
	p = data;
	return (&p);

//	return (&p);

}
