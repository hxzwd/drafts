
/*
posix mqueue message receiver
*/


#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#include "sys/types.h"
#include "unistd.h"

#include "errno.h"
#include "mqueue.h"


#define POSIX_QUEUE_NAME	"/test_mq"
#define MESSAGE_MAX_SIZE	1024
#define MESSAGE_MAX_NUM		10



int32_t main(void)
{

	struct mq_attr attr;
	mqd_t mq_handle;
	ssize_t bytes_read;

	char msg_buffer[MESSAGE_MAX_SIZE + MESSAGE_MAX_SIZE] = { 0 };
	uint32_t msg_buffer_size = sizeof(msg_buffer);
	fprintf(stderr, "msg_buffer_size = %d\n", msg_buffer_size);

	attr.mq_flags = 0;
	attr.mq_maxmsg = MESSAGE_MAX_NUM;
	attr.mq_msgsize = MESSAGE_MAX_SIZE;
	attr.mq_curmsgs = 0;


	mq_handle = mq_open(POSIX_QUEUE_NAME, O_CREAT | O_RDWR | O_NONBLOCK, 0664, &attr);

	
	while(1)
	{
		memset(msg_buffer, 0x00, msg_buffer_size);
		bytes_read = mq_receive(mq_handle, msg_buffer, MESSAGE_MAX_SIZE, NULL);

		if(bytes_read >= 0)
		{
			fprintf(stderr, "[new message]: [bytes_readed = %d] msg_buffer = \n\t%s\n", bytes_read, msg_buffer);
		}
		else
		{
			fprintf(stderr, "[new message]: empty (none message)\n");
		}

		fflush(stderr);

		usleep((int32_t)(1.250 * 1e6));

	}


	mq_close(mq_handle);
	mq_unlink(POSIX_QUEUE_NAME);


	return 0;

}

