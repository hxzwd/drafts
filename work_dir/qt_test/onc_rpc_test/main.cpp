#include <QCoreApplication>

#include "stdio.h"
#include "stdint.h"

#include "rpc/rpc.h"
#include "hello.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CLIENT *client;
//	char **p;

    int *p;

    if(argc != 2)
    {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        exit(1);
    }


    client = clnt_create(argv[1], RPC_TEST_PROG, RPC_TEST_VERS, "tcp");
    if(client == NULL)
    {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    printf("Getting ready to call server function\n");

    p = hello_1(NULL, client);

    printf("Back from server function\n");

    if(p == NULL)
    {
        clnt_perror(client, argv[1]);
        exit(1);
    }

//	printf("Returned string = %s\n", *p);
    printf("Returned int = %d\n", p[0]);

    return a.exec();
}
