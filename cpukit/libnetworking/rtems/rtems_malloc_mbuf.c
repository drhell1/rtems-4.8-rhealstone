/*
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#define RTEMS_FAST_MUTEX

#ifdef RTEMS_FAST_MUTEX
#define __RTEMS_VIOLATE_KERNEL_VISIBILITY__ 1
#endif

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>

#include <rtems.h>
#include <rtems/rtems_bsdnet.h>

/*
 * Default allocator for mbuf data. Over-ride in user code to change 
 * the way mbuf's are allocated.
 */

void* rtems_bsdnet_malloc_mbuf(size_t size, int type)
{
   extern void *malloc(size_t);
   return malloc(size);
}


