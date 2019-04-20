
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
mqd_t mq_handle_response;
struct sigevent sev;

void f_send_response(char * msg)
{

	int32_t write_status;
	char buffer[MESSAGE_MAX_SIZE + MESSAGE_MAX_SIZE] = { 0 };

	sprintf(buffer, "%s", msg);

	write_status = mq_send(mq_handle_response, buffer, MESSAGE_MAX_SIZE, NULL);

	if(write_status)
	{
		fprintf(stderr, "[new response]: write_status is not 0 (%d) (buffer: %s) (Error)!\nWrite error, return from f_send_response() function\n", write_status, buffer);
		return; 
	}
	else
	{
		fprintf(stderr, "[new response]: [write_status = %d] buffer = %s\n", write_status, buffer);	
	}

}

static void thread_func(union sigval sv)
{

	
	ssize_t bytes_read;

	char msg_buffer[MESSAGE_MAX_SIZE + MESSAGE_MAX_SIZE] = { 0 };
	uint32_t msg_buffer_size = sizeof(msg_buffer);
	
	fprintf(stderr, "In thread_func()!\n");
	fprintf(stderr, "sv.sival_ptr = %p\n*(sv.sival_ptr) = %d\n", sv.sival_ptr, *((mqd_t *)(sv.sival_ptr)));
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
		fprintf(stderr, "quit command catched\nNow close and unlink posix queue (request and response) and exit with code 0\n");
		mq_close(mq_handle);
		mq_unlink(POSIX_QUEUE_NAME);
		mq_close(mq_handle_response);
		mq_unlink("/test_mq_response");

		exit(0);
	} 
	else if(!strcmp(msg_buffer, "command_0"))
	{
		fprintf(stderr, "command #0 catched\nWrite response: call f_send_response()\n");
		f_send_response("command 0 some response!... Ok!...");
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
	mq_handle_response = mq_open("/test_mq_response", O_CREAT | O_RDWR | O_NONBLOCK, 0664, &attr);

	fprintf(stderr, "mq_handle = %d\nmq_handle_response = %d\n", mq_handle, mq_handle_response);

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

