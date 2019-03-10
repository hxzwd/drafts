
#include "file_proc.h"




void flpr_hello()
{
	printf("\n_________________________________\n\n");
	printf("Hello from file_proc lib\n");
	printf("Version: 0.0.0\n");
	printf("\n_________________________________\n");
}

void flpr_free_buffer(char *buffer[], int32_t buffer_size)
{
	if(buffer)
		for(uint32_t i = 0; i < buffer_size; i++)
			if(buffer[i])
				free(buffer[i]);
}

int32_t flpr_num_of_lines(char *filename)
{
	FILE *fd;

	if((fd = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "[file_proc:flpr_num_of_lines] Error open file: %s\n", filename);
		return -1;
	}

	size_t nread;
	size_t len = 0;
	int32_t lines_counter = 0;
	char *line;

	while((nread = getline(&line, &len, fd)) != -1)
		lines_counter++;

	free(line);
	fclose(fd);

	return lines_counter;

}

int32_t flpr_readlines(char *filename, char ***buffer)
{

	FILE *fd;
	char *line;
	size_t len = 0;
	size_t nread;
	int32_t num_of_lines = flpr_num_of_lines(filename);

	if(num_of_lines <= 0)
	{
		fprintf(stderr, "[file_proc:flpr_readlines] Empty file or error open, file: %s\n", filename);
		return -1;
	}

	if((fd = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "[file_proc:flpr_readlines] Error open file: %s\n", filename);
		return -1;
	}

	*buffer = (char **)malloc(sizeof(char *) * num_of_lines);

	if(!(*buffer))
	{
		fprintf(stderr, "[file_proc:flpr_readlines] Memory allocation error, file name: %s\n", filename);
		fclose(fd);
		return -1;
	}

	for(uint32_t i = 0; i < num_of_lines; i++)
		(*buffer)[i] = NULL;

	uint32_t i = 0;
	while((nread = getline(&line, &len, fd)) != -1)
	{
		(*buffer)[i] = (char *)malloc(sizeof(char) * len);
		if(!(*buffer)[i])
		{
			fprintf(stderr, "[file_proc:flpr_readlines] Memory allocation error, file name: %s\n", filename);
			flpr_free_buffer(*buffer, num_of_lines);
			*buffer = NULL;
			fclose(fd);
			return -1;
		}
		strcpy((*buffer)[i], line);
		i++;
	}

	free(line);
	fclose(fd);

	return num_of_lines;

}

int32_t flpr_appendline(char *filename, char *line)
{

	FILE *fd;

	if((fd = fopen(filename, "a+")) == NULL)
	{
		fprintf(stderr, "[file_proc:flpr_appendline] Error open file: %s\n", filename);
		return -1;
	}

	fprintf(fd, "%s", line);

	fclose(fd);
	return 0;
}

int32_t flpr_appendlines(char *filename, char *buffer[], int32_t buffer_size)
{

	FILE *fd;

	if((fd = fopen(filename, "a+")) == NULL)
	{
		fprintf(stderr, "[file_proc:flpr_appendlines] Error open file: %s\n", filename);
		return -1;
	}

	for(uint32_t i = 0; i < buffer_size; i++)
	{
		fprintf(fd, "%s", buffer[i]);
	}

	fclose(fd);
	return 0;

}

int32_t flpr_str_replace(char *buffer, char *target, char *old, char *replace)
{

	uint32_t new_len;
	uint32_t flag_static = 1;
	char *pos;
/*
	if((*buffer))
	{
		fprintf("[file_proc:flpr_str_replace] Error: need clear buffer (*buffer == NULL is True) [target = %s; old = %s; replace = %s]\n", target, old, replace);
		return -1;
	}
*/
	new_len = strlen(target) - strlen(old) + strlen(replace);


	if(buffer != NULL)
	{
		fprintf(stderr, "[file_proc:flpr_str_replace] flag_static = 1\n");
		flag_static = 1;
	}
	else
	{
		buffer = (char *)malloc(sizeof(char) * new_len);
		flag_static = 0;
	}

	if(!flag_static)
		if(!(*buffer))
		{
			fprintf(stderr, "[file_proc:flpr_str_replace] Memory allocation error [target = %s; old = %s; replace = %s]\n", target, old, replace);
			return -1;
		}

	pos = strstr(target, old);
	if(!pos)
	{
		fprintf(stderr, "[file_proc:flpr_str_replace] Error: Can not find old substring in target string [target = %s; old = %s; replace = %s]\n", target, old, replace);
		if(!flag_static)
			if(buffer)
				free(buffer);
		return -1;
	}


	strncpy(buffer, target, pos - target);
	(buffer)[pos - target] = '\0';
	sprintf((buffer)+(pos - target), "%s%s", replace, pos + strlen(old));

//	fprintf(stderr, "dbg: %s\n", buffer);

	return 0;

}


int32_t flpr_int32_t_array_to_string(int32_t *data, char *buffer, uint32_t array_size, uint32_t buffer_size)
{

	uint32_t res_len = 0;
	char tmp_buffer[128];
	char delim = ',';
	char *pos = buffer;

	for(uint32_t i = 0; i < array_size; i++)
	{
		if(i == array_size - 1)
			sprintf(tmp_buffer, "%d", data[i]);
		else
			sprintf(tmp_buffer, "%d%c", data[i], delim);
		res_len += strlen(tmp_buffer);
		if(res_len > buffer_size)
		{
			fprintf(stderr, "[file_proc:flpr_int32_t_array_to_string]: Error: string length > buffer size [res_len = %d; buffer_size = %d]\n", res_len, buffer_size);
			return -1;
		}
		//strncpy(buffer, tmp_buffer, strlen(tmp_buffer));
		pos = strcat(pos, tmp_buffer);
	}

	fprintf(stderr, "dbg: buffer = %s\n", buffer);

	return 0;

}
