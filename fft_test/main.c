
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "math.h"

#include "gsl/gsl_errno.h"
#include "gsl/gsl_fft_complex.h"


#define REAL(z, i) ((z)[2*(i)])
#define IMAG(z, i) ((z)[2*(i) + 1])

int32_t main(int32_t argc, char *argv[])
{

	uint32_t n;
	uint32_t i;
	double *data;


	if(argc != 2)
	{
		fprintf(stderr, "usage: %s <data-size>\n", argv[0]);
		exit(1);
	}

	if(argc >= 2)
	{
		n = atoi(argv[1]);
	}

	i = n;

	data = (double *)malloc(sizeof(double)*(2*n));
	if(!data)
	{
		fprintf(stderr, "Error: Can not alloc memory\n");
		exit(1);
	}


	gsl_fft_complex_wavetable * wavetable;
	gsl_fft_complex_workspace * workspace;

	for(uint32_t i = 0; i < n; i++)
	{
//		data[i] = 0.0;
		REAL(data, i) = 0.0;
		IMAG(data, i) = 0.0;
	}

	data[0] = 1.0;

	for(uint32_t i = 1; i <= 10; i++)
	{
//		data[i] = 1.0;
		REAL(data, i) = REAL(data, n - i) = 1.0;
	}

	FILE *fd = NULL;
	if((fd = fopen("fft_data.txt", "w")) == NULL)
	{
		fprintf(stderr, "Error: Can not open file: fft_data.txt\n");
		if(data)
		{
			free(data);
		}
		exit(1);
	}

	for(uint32_t i = 0; i < n; i++)
	{
		fprintf(fd, "%f %f\n", REAL(data, i), IMAG(data, i));
	}
	fclose(fd);
	fd = NULL;

	workspace = gsl_fft_complex_workspace_alloc(n);
	wavetable = gsl_fft_complex_wavetable_alloc(n);

	gsl_fft_complex_forward(data, 1, n, wavetable, workspace);


	if((fd = fopen("fft_data_out.txt", "w")) == NULL)
	{
		fprintf(stderr, "Error: Can not open file: fft_data_out.txt\n");
		if(data)
		{
			free(data);
		}
		exit(1);
	}

	for(uint32_t i = 0; i < n; i++)
	{
		fprintf(fd, "%f %f\n", REAL(data, i), IMAG(data, i));
	}
	fclose(fd);



	gsl_fft_complex_wavetable_free(wavetable);
	gsl_fft_complex_workspace_free(workspace);


	if(data)
	{
		free(data);
	}

	return 0;

}
