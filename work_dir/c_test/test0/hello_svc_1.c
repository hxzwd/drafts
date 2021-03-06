#define _POSIX_C_SOURCE		199309L


/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */



#include "hello.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "rpc/rpc.h"

#include "sys/types.h"
#include "unistd.h"
#include "stdint.h"



#include "stdarg.h"


#include "errno.h"
#include "signal.h"

int32_t run_test(void);
int32_t func_proc_h(pid_t cpid);
int32_t func_proc_l(void);
void func_handler(int32_t signum, siginfo_t * siginfo, void * extra);

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static int32_t test_flag;

static void
rpc_test_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		int fill;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case HELLO:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) hello_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
run_rpc_test (int argc, char **argv)
{

	pid_t cpid;


	fprintf(stderr, "[run_rpc_test] getpid() = %d\n", getpid());

	if((cpid = fork()) == 0)
	{
		fprintf(stderr, "[run_rpc_test] cpid = 0!\nContinue. Ok!...\n");
	}
	else
	{
		fprintf(stderr, "[run_rpc_test] cpid = %d Return. Ok!...\n", cpid);
		func_proc_l();
		return cpid;
	}


	register SVCXPRT *transp;

	pmap_unset (RPC_TEST_PROG, RPC_TEST_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, RPC_TEST_PROG, RPC_TEST_VERS, rpc_test_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (RPC_TEST_PROG, RPC_TEST_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, RPC_TEST_PROG, RPC_TEST_VERS, rpc_test_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (RPC_TEST_PROG, RPC_TEST_VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}




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

	test_flag = 0;

	sigset_t mask;
	sigset_t oldmask;

	siginfo_t siginfo;

	struct sigaction sa;
	struct timespec tv;

	int32_t count;
	int32_t recv_sig;

/*
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

*/
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	sa.sa_sigaction = func_handler;

	fprintf(stderr, "Reg SIGRTMIN handler function\n");
	if(sigaction(SIGRTMIN, &sa, NULL) == -1)
	{
		perror("error: sigaction().\n");
		return -1;
	}

//	sigsuspend(&oldmask);

	return 0;

}

void func_handler(int32_t signum, siginfo_t * siginfo, void * extra)
{
	fprintf(stderr, "[func_handler()] " "signal %d received\n" "signal code = %d\n", siginfo->si_signo, siginfo->si_code, siginfo->si_int);
	fprintf(stderr, "signal value = %d\n", siginfo->si_value);
	fprintf(stderr, "pid of source = %d\n", siginfo->si_pid);
	test_flag++;
}


