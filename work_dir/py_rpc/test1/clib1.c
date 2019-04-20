
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"


static int32_t counter;
static char * memory_ptr;
static uint32_t memory_size;

int32_t test_func(void)
{

	counter++;

	fprintf(stderr, "[clib1]: test_func()\n");

	return counter;

}

void dump_memory_block(void)
{
	fprintf(stderr, "memory size: %d\nmemory ptr: %p\n", memory_size, memory_ptr);
	
	for(uint32_t i = 0; i < memory_size; i++)
	{
			if(i % 16 == 0 && i != 0)
			{
				fprintf(stderr, "\n");
			}
			
			uint8_t tmp = (uint8_t)(memory_ptr[i]);
			fprintf(stderr, "%02hhX ", tmp);
		
		
	}
		
	fprintf(stderr, "\n");
	

}

char * alloc_memory_block(uint32_t size)
{
	fprintf(stderr, "[alloc_memory_block] size = %d\n", size);

	char * memory_block;
	memory_block = NULL;

	memory_block = (char *)(malloc(sizeof(char) * size));
	fprintf(stderr, "[alloc_memory_block] memory_block = %p\n", memory_block);

	memset(memory_block, 0xFF, sizeof(char) * size);
	memory_ptr = memory_block;
	memory_size = sizeof(char) * size;

	return memory_block;

}

void free_memory_block(char * ptr)
{

	fprintf(stderr, "[free_memory_block] ptr = %p\n", ptr);
	if(ptr)
	{
		free(ptr);
		memory_ptr = NULL;
		memory_size = 0;
	}

}




