
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
#include "pthread.h"


#define POSIX_QUEUE_NAME	"/test_mq"
#define MESSAGE_MAX_SIZE	1024
#define MESSAGE_MAX_NUM		10

mqd_t mq_handle;
struct sigevent sev;

static void thread_func(union sigval sv)
{

	
	ssize_t bytes_read;

	char msg_buffer[MESSAGE_MAX_SIZE + MESSAGE_MAX_SIZE] = { 0 };
	uint32_t msg_buffer_size = sizeof(msg_buffer);
	
	fprintf(stderr, "In thread_func()!\n");
	fprintf(stderr, "[thread_func] msg_buffer_size = %d\n", msg_buffer_size);

	fprintf(stderr, "Re-notify!\n");	

	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = thread_func;
	sev.sigev_notify_attributes = NULL;
	sev.sigev_value.sival_ptr = &mq_handle;

	mq_notify(mq_handle, &sev);

	fprintf(stderr, "Re-notify ended\nTry to receive message\n");
	
	bytes_read = mq_receive(mq_handle, msg_buffer, MESSAGE_MAX_SIZE, NULL);

	if(bytes_read >= 0)
	{
		fprintf(stderr, "[new message]: [bytes_readed = %d] msg_buffer = \n\t%s\n", bytes_read, msg_buffer);
	}
	else
	{
		fprintf(stderr, "[new message]: empty (none message)\n");
		return;	
	}


	if(!strcmp(msg_buffer, "quit"))
	{
		fprintf(stderr, "quit command catched\nNow close and unlink posix queue and exit with code 0\n");
		mq_close(mq_handle);
		mq_unlink(POSIX_QUEUE_NAME);
		exit(0);
	}


}


int32_t main(void)
{

	struct mq_attr attr;
	
	

	attr.mq_flags = 0;
	attr.mq_maxmsg = MESSAGE_MAX_NUM;
	attr.mq_msgsize = MESSAGE_MAX_SIZE;
	attr.mq_curmsgs = 0;


	mq_handle = mq_open(POSIX_QUEUE_NAME, O_CREAT | O_RDWR | O_NONBLOCK, 0664, &attr);


	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = thread_func;
	sev.sigev_notify_attributes = NULL;
	sev.sigev_value.sival_ptr = &mq_handle;

	mq_notify(mq_handle, &sev);
	
	fprintf(stderr, "Loop forever in main (with usleep for 2250000 us)\n");
	
	while(1)
	{
		fflush(stderr);
		usleep((int32_t)(2.250 * 1.0e6));
	}


	return 0;

}

