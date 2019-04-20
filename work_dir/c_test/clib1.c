
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"


static int32_t counter;

int32_t test_func(void)
{

	counter++;

	fprintf(stderr, "[clib1]: test_func()\n");

	return counter;

}
