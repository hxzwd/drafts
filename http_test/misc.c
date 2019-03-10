
#include "misc.h"
#include "file_proc.h"


void f_catch_test()
{

	fprintf(stderr, "Catch request test.html\n");
	fprintf(stderr, "Now do something...\n");

}


void f_catch_plotly_test()
{

	char *filename = "plotly_test.html";
	char **buffer = NULL;
	int32_t buffer_size;

	fprintf(stderr, "Catch request plotly_test.html\n");
	fprintf(stderr, "Now do something...\n");

	FILE *fd;

	if((fd = fopen("plotly_test.html", "r")) == NULL)
	{
		fprintf(stderr, "Error: Can not open file: plotly_test.html\n");
	}


	flpr_hello();

	buffer_size = flpr_readlines(filename, &buffer);

	for(uint32_t i = 0; i < buffer_size; i++)
	{
		fprintf(stderr, "[%d] %s", i, buffer[i]);
	}

	flpr_appendline("test_out.txt", buffer[0]);
	flpr_appendline("test_out.txt", buffer[1]);

	char buf[1024] = { 0 };

	flpr_str_replace(buf, "var x = {{ template }}", "template", "[0, 1, 2, 4, 5, 6, 7, 8]");
	fprintf(stderr, "flpr_str_replace: %s\n", buf);

	int32_t data[] = { 123, 23392, 1, 2, 3, 10, 12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 23432, 123123, 345345, 24324 };
	memset(buf, 0, sizeof(buf));
	flpr_int32_t_array_to_string(data, buf, sizeof(data)/sizeof(int32_t), sizeof(buf));
	fprintf(stderr, "flpr_int32_t_array_to_string: %s\n", buf);


	if(buffer)
		flpr_free_buffer(buffer, buffer_size);

//	fprintf(stderr, "flpr_num_of_lines: %d\n", flpr_num_of_lines(filename));

}
