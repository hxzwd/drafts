

#include "stdint.h"

uint32_t u32_value = 1337;

int32_t func_fact(int32_t n)
{
	if(n <= 1)
	{
		return 1;
	}
	else
	{
		return n * func_fact(n - 1);
	}

}

