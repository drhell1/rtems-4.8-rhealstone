/*
 *  This is a shared BSP post driver hook designed to open
 *  /dev/console for stdin, stdout, and stderr if it exists.
 *  Newlib will automatically associate the file descriptors
 *  with the first thress files opened.
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#include <rtems.h>
#include <rtems/libio.h>
#include <fcntl.h>

void bsp_postdriver_hook(void)
{
  extern void open_dev_console(void);

  open_dev_console();
}
