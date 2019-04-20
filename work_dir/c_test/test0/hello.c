
#include "stdio.h"
#include "stdint.h"


int32_t main(int32_t argc, char *argv[])
{

	char *message;

	if(argc != 2)
	{
		fprintf(stderr, "usage: %s <message>\n", argv[0]);
		exit(1);
	}

	message = argv[1];


	f_print_msg(message);

	return 0;

}



int32_t f_print_msg(char *msg)
{

	fprintf(stdout, "MESSAGE:\n%s\n", msg);
	return 0;
}
