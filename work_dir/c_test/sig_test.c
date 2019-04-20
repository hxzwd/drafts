
#define _POSIX_C_SOURCE		199309L

#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "stdint.h"

#include "unistd.h"

#include "errno.h"

#include "signal.h"
#include "sys/types.h"


int32_t func_proc_h(pid_t cpid);
int32_t func_proc_l(void);
void func_handler(int32_t signum, siginfo_t * siginfo, void * extra);

int32_t func_proc_h(pid_t cpid)
{
	union sigval value;

	fprintf(stderr, "sleep 3 seconds while fork process runing...\n");
	sleep(3);
	fprintf(stderr, "Continue. Ok!...\n");

	value.sival_int	= 1337;
	sigqueue(cpid, SIGRTMIN, value);

	sleep(3);

	value.sival_int = 1338;
	sigqueue(cpid, SIGRTMIN+1, value);

	sleep(3);

	value.sival_int = 1;
	sigqueue(cpid, SIGRTMIN, value);

	return 0;

}

int32_t func_proc_l(void)
{

	sigset_t mask;
	sigset_t oldmask;

	siginfo_t siginfo;

	struct sigaction sa;
	struct timespec tv;

	int32_t count;
	int32_t recv_sig;

	count = 0;

	sigemptyset(&mask);
	sigaddset(&mask, SIGRTMIN);
	sigaddset(&mask, SIGRTMIN+1);

	sigprocmask(SIG_BLOCK, &mask, &oldmask);

	tv.tv_sec = 1;
	tv.tv_nsec = 1;

	while(count < 2)
	{
		recv_sig = sigtimedwait(&mask, &siginfo, &tv);

		if(recv_sig == -1)
		{
			if(errno == EAGAIN)
			{
				fprintf(stderr, "Timed out! Continue...\n");
				continue;
			}
			else
			{
				perror("error: sigtimedwait()\n");
				return -1;
			}
		}
		else
		{
			fprintf(stderr, "Signal received!\t[recv_sig = %d]\n", recv_sig);
			count++;
		}
	}


	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	sa.sa_sigaction = func_handler;

	if(sigaction(SIGRTMIN, &sa, NULL) == -1)
	{
		perror("error: sigaction().\n");
		return -1;
	}

	sigsuspend(&oldmask);

	return 0;

}

void func_handler(int32_t signum, siginfo_t * siginfo, void * extra)
{
	fprintf(stderr, "[func_handler()] " "signal %d received\n" "signal code = %d\n", siginfo->si_signo, siginfo->si_code, siginfo->si_int);
	fprintf(stderr, "signal value = %d\n", siginfo->si_value);
	fprintf(stderr, "pid of source = %d\n", siginfo->si_pid);
}

int32_t main(int32_t argc, char **argv)
{

	pid_t cpid;

	fprintf(stderr, "parent pid = %d\n", getpid());


	if((cpid = fork()) == 0)
	{
		func_proc_l();
	}
	else
	{
		fprintf(stderr, "child pid = %d\n", cpid);
		func_proc_h(cpid);
	}

	return 0;
}
