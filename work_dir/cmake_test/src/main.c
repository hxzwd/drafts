

#include "misc.h"

void hello_func(char * msg)
{
	fprintf(stdout, "[stdout]:\t%s\n", msg);
	fprintf(stderr, "[stderr]:\t%s\n", msg);
}

int32_t main(int32_t argc, char **argv)
{

	char * msg = "hello (this for cmake test)";

	hello_func(msg);


	return 0;

}
