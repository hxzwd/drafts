

typedef int st_rpc_array<4096>;

program RPC_TEST_3_PROG
{
	version RPC_TEST_3_VERS
	{
		string F_TEST3(st_rpc_array) = 1;
	} = 1;
} = 0x30000824;

