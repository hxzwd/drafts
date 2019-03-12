
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "math.h"


#define M_PI 3.14159265358979323846

int32_t main(void)
{

	FILE *fd;
	fd = fopen("out.bin", "wb");

	for(uint32_t i = 0; i < 10000; i++)
	{
		int32_t tmp;
		tmp = (int32_t)(100.0*sin(i*0.1));
		fwrite(&tmp, sizeof(int32_t), 1, fd);
	}



	fclose(fd);
	return 0;
}
