/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "test3.h"

bool_t
xdr_st_rpc_array (XDR *xdrs, st_rpc_array *objp)
{
	register int32_t *buf;

	 if (!xdr_array (xdrs, (char **)&objp->st_rpc_array_val, (u_int *) &objp->st_rpc_array_len, 65536,
		sizeof (int), (xdrproc_t) xdr_int))
		 return FALSE;
	return TRUE;
}
