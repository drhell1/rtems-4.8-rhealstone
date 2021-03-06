/*
 *  This routine starts the application.  It includes application,
 *  board, and monitor specific initialization and configuration.
 *  The generic CPU dependent initialization has been performed
 *  before this routine is invoked.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#include <string.h>

#include <bsp.h>
#include <rtems/libio.h>
#include <rtems/libcsupport.h>

/*
 *  The original table from the application and our copy of it with
 *  some changes.
 */

extern rtems_configuration_table Configuration;

rtems_configuration_table  BSP_Configuration;

rtems_cpu_table Cpu_table;

char *rtems_progname;

/*
 *  Use the shared implementations of the following routines
 */

void bsp_postdriver_hook(void);
void bsp_libc_init( void *, uint32_t, int );

/*
 *  Function:   bsp_pretasking_hook
 *  Created:    95/03/10
 *
 *  Description:
 *      BSP pretasking hook.  Called just before drivers are initialized.
 *      Used to setup libc and install any BSP extensions.
 *
 *  NOTES:
 *      Must not use libc (to do io) from here, since drivers are
 *      not yet initialized.
 *
 */

void bsp_pretasking_hook(void)
{
    void         *heapStart;
    unsigned long heapSize;
    extern int WorkspaceBase;

    heapStart =  (void *)
       ((unsigned long)&WorkspaceBase + BSP_Configuration.work_space_size);
    if ( (unsigned long) heapStart > (256 * 1024) )
       rtems_fatal_error_occurred (('H'<<24) | ('E'<<16) | ('A'<<8) | 'P');
    heapSize = (256 * 1024) - (unsigned long)(heapStart);
    bsp_libc_init(heapStart, heapSize, 0);

#ifdef RTEMS_DEBUG
    rtems_debug_enable( RTEMS_DEBUG_ALL_MASK );
#endif

}

/*
 *  bsp_start
 *
 *  This routine does the bulk of the system initialization.
 */

void bsp_start( void )
{
  extern int WorkspaceBase;
  /* Configure Number of Register Caches */

  Cpu_table.pretasking_hook = bsp_pretasking_hook;  /* init libc, etc. */
  Cpu_table.postdriver_hook = bsp_postdriver_hook;
  Cpu_table.interrupt_stack_size = 4096;

/*
  if ( BSP_Configuration.work_space_size >(512*1024) )
   _sys_exit( 1 );
*/

  BSP_Configuration.work_space_start = (void *) &WorkspaceBase;
}

void H8BD_Install_IRQ(
  uint32_t  	vector,
  proc_ptr	new_handler,
  proc_ptr	*old_handler )
{ /* empty */
}
