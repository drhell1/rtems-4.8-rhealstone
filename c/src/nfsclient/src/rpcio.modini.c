#include "librtemsNfs.h"
/* CEXP module support (magic init) */
void
_cexpModuleInitialize(void *mod)
{
	rpcUdpInit();
}

int
_cexpModuleFinalize(void *mod)
{
	return rpcUdpCleanup();
}


