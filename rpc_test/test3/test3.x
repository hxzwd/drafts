

typedef int st_rpc_array<65536>;

program RPC_TEST_3_PROG
{
	version RPC_TEST_3_VERS
	{
		st_rpc_array F_TEST3(st_rpc_array) = 1;
	} = 1;
} = 0x30000824;

