/*
 *  This include file contains all board IO definitions.
 *
 *  generic sh2
 *
 *  Author: Ralf Corsepius (corsepiu@faw.uni-ulm.de)
 *
 *  COPYRIGHT (c) 1997-1998, FAW Ulm, Germany
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 *  COPYRIGHT (c) 1998.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  Minor adaptations for sh2 by:
 *  John M. Mills (jmills@tga.com)
 *  TGA Technologies, Inc.
 *  100 Pinnacle Way, Suite 140
 *  Norcross, GA 30071 U.S.A.
 *
 *  This modified file may be copied and distributed in accordance
 *  the above-referenced license. It is provided for critique and
 *  developmental purposes without any warranty nor representation
 *  by the authors or by TGA Technologies.
 *
 *  $Id$
 */

#ifndef _BSP_H
#define _BSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems.h>
#include <rtems/clockdrv.h>
#include <rtems/console.h>

#include <bspopts.h>

/*
 *  confdefs.h overrides for this BSP:
 *   - number of termios serial ports (defaults to 1)
 *   - Interrupt stack space is not minimum if defined.
 */

/* #define CONFIGURE_NUMBER_OF_TERMIOS_PORTS 2 */
#define CONFIGURE_INTERRUPT_STACK_MEMORY  (4 * 1024)

#if 0
#include <rtems/devnull.h>
#define BSP_CONSOLE_DEVNAME "/dev/null"
#define BSP_CONSOLE_DRIVER_TABLE_ENTRY DEVNULL_DRIVER_TABLE_ENTRY
#else
#include <sh/sci.h>
/* FIXME:
 *   These definitions will be no longer necessary if the old
 *   implementation of SCI driver will be droped
 */
#define BSP_CONSOLE_DEVNAME "/dev/sci0"
#define BSP_CONSOLE_MINOR_NUMBER ((rtems_device_minor_number) 0)
#define BSP_CONSOLE_DRIVER_TABLE_ENTRY DEVSCI_DRIVER_TABLE_ENTRY
#define BSP_CONSOLE_DEVICE_TERMIOS_HANDLERS (sh_sci_get_termios_handlers(TRUE))
#endif

/* Constants */

/*
 *  Simple spin delay in microsecond units for device drivers.
 *  This is very dependent on the clock speed of the target.
 */

#define rtems_bsp_delay( microseconds ) CPU_delay(microseconds)
#define sh_delay( microseconds ) CPU_delay( microseconds )

/*
 * Defined in the linker script 'linkcmds'
 */

extern uint32_t         HeapStart ;
extern uint32_t         HeapEnd ;
extern uint32_t         WorkSpaceStart ;
extern uint32_t         WorkSpaceEnd ;

extern void *CPU_Interrupt_stack_low ;
extern void *CPU_Interrupt_stack_high ;

/* miscellaneous stuff assumed to exist */

extern rtems_configuration_table BSP_Configuration;

extern void bsp_cleanup( void );

/*
 *  Device Driver Table Entries
 */

/*
 * We redefine CONSOLE_DRIVER_TABLE_ENTRY to redirect /dev/console
 *
 * FIXME: Since console driver works properly this is not
 * necessary. When enabled - causes error in console_initialize.
 */
#if 0
#undef CONSOLE_DRIVER_TABLE_ENTRY
#define CONSOLE_DRIVER_TABLE_ENTRY \
  BSP_CONSOLE_DRIVER_TABLE_ENTRY, \
  { console_initialize, console_open, console_close, \
      console_read, console_write, console_control }
#endif

/*
 * NOTE: Use the standard Clock driver entry
 */

#ifdef __cplusplus
}
#endif

#endif
