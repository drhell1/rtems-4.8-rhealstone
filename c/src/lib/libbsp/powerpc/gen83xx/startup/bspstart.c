/*===============================================================*\
| Project: RTEMS generic MPC83xx BSP                              |
+-----------------------------------------------------------------+
|                    Copyright (c) 2007                           |
|                    Embedded Brains GmbH                         |
|                    Obere Lagerstr. 30                           |
|                    D-82178 Puchheim                             |
|                    Germany                                      |
|                    rtems@embedded-brains.de                     |
+-----------------------------------------------------------------+
| The license and distribution terms for this file may be         |
| found in the file LICENSE in this distribution or at            |
|                                                                 |
| http://www.rtems.com/license/LICENSE.                           |
|                                                                 |
+-----------------------------------------------------------------+
| this file contains the BSP startup code                         |
\*===============================================================*/

/*
 *  $Id$
 */

#include <bsp.h>

#include <rtems/libio.h>
#include <rtems/libcsupport.h>
#include <rtems/powerpc/powerpc.h>
#include <rtems/score/thread.h>

#include <rtems/bspIo.h>
#include <libcpu/cpuIdent.h>
#include <libcpu/spr.h>
#include <bsp/irq.h>

#include <string.h>

SPR_RW(SPRG0)
SPR_RW(SPRG1)

/*
 *  The original table from the application (in ROM) and our copy of it with
 *  some changes. Configuration is defined in <confdefs.h>. Make sure that
 *  our configuration tables are uninitialized so that they get allocated in
 *  the .bss section (RAM).
 */
extern rtems_configuration_table Configuration;
extern unsigned long intrStackPtr;
rtems_configuration_table  BSP_Configuration;
static char *BSP_heap_start, *BSP_heap_end;
rtems_cpu_table Cpu_table;
char *rtems_progname;

/*
 * constants for c_clock driver:
 * system bus frequency (for timebase etc)
 * and 
 * Time base divisior: scaling value:
 * BSP_time_base_divisor = TB ticks per millisecond/BSP_bus_frequency
 */
unsigned int BSP_bus_frequency = BSP_CSB_CLK_FRQ;
unsigned int BSP_time_base_divisor = 4000;  /* 4 bus clicks per TB click */

/*
 *  Use the shared implementations of the following routines.
 *  Look in rtems/c/src/lib/libbsp/shared/bsppost.c and
 *  rtems/c/src/lib/libbsp/shared/bsplibc.c.
 */
void bsp_postdriver_hook(void);
void bsp_libc_init( void *, uint32_t, int );
extern void initialize_exceptions(void);
extern void cpu_init(void);

void BSP_panic(char *s)
  {
  printk("%s PANIC %s\n",_RTEMS_version, s);
  /*
   * FIXME: hang/restart system
   */
  __asm__ __volatile ("sc");
  }

void _BSP_Fatal_error(unsigned int v)
  {
  printk("%s PANIC ERROR %x\n",_RTEMS_version, v);
  /*
   * FIXME: hang/restart system
   */
  __asm__ __volatile ("sc");
  }

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

void
bsp_pretasking_hook(void)
{

  /*
   * initialize libc including the heap
   */
  bsp_libc_init( BSP_heap_start, 
		 BSP_heap_end - BSP_heap_start,
		 0);


#ifdef STACK_CHECKER_ON
  /*
   *  Initialize the stack bounds checker
   *  We can either turn it on here or from the app.
   */

  Stack_check_Initialize();
#endif

#ifdef RTEMS_DEBUG
  rtems_debug_enable( RTEMS_DEBUG_ALL_MASK );
#endif
}



void bsp_predriver_hook(void)
{
}

void bsp_calc_mem_layout()
{
  /*
   * these labels (!) are defined in the linker command file
   * or when the linker is invoked
   * NOTE: the information(size) is the address of the object,
   * not the object otself
   */
  extern unsigned char TopRamReserved;
  extern unsigned char _WorkspaceBase;

  /*
   * compute the memory layout:
   * - first unused address is Workspace start
   * - Heap starts at end of workspace
   * - Heap ends at end of memory - reserved memory area
   */
  BSP_Configuration.work_space_start = &_WorkspaceBase;

  BSP_heap_start = ((char *)BSP_Configuration.work_space_start +
                    BSP_Configuration.work_space_size);

#if defined(HAS_UBOOT)
  BSP_heap_end = (uboot_bdinfo_ptr->bi_memstart 
		  + uboot_bdinfo_ptr->bi_memsize
		  - (uint32_t)&TopRamReserved);
#else
  BSP_heap_end = (void *)(RAM_END - (uint32_t)&TopRamReserved);
#endif

}


void bsp_start(void)
{
  ppc_cpu_id_t myCpu;
  ppc_cpu_revision_t myCpuRevision;
  register unsigned char* intrStack;

  /*
   * Get CPU identification dynamically. Note that the get_ppc_cpu_type() function
   * store the result in global variables so that it can be used latter...
   */
  myCpu 	    = get_ppc_cpu_type();
  myCpuRevision = get_ppc_cpu_revision();
  /*
   * determine heap and workspace placement
   */
  bsp_calc_mem_layout();

  cpu_init();

  /*
   * Initialize some SPRG registers related to irq handling
   */

  intrStack = (((unsigned char*)&intrStackPtr) - PPC_MINIMUM_STACK_FRAME_SIZE);

  _write_SPRG1((unsigned int)intrStack);

  /* Signal them that this BSP has fixed PR288 - eventually, this should go away */
  _write_SPRG0(PPC_BSP_HAS_FIXED_PR288);

  /*
   *  initialize the CPU table for this BSP
   */

  Cpu_table.pretasking_hook        = bsp_pretasking_hook;    /* init libc, etc. */
  Cpu_table.predriver_hook         = bsp_predriver_hook;     /* init PCI / RTC ...   */
  Cpu_table.postdriver_hook        = bsp_postdriver_hook;
  Cpu_table.clicks_per_usec        = (BSP_CSB_CLK_FRQ/1000000);
  Cpu_table.exceptions_in_RAM      = TRUE;

  if( Cpu_table.interrupt_stack_size < 4*1024 )
    Cpu_table.interrupt_stack_size = 4 * 1024;

 /*
  * Install our own set of exception vectors
  */

  initialize_exceptions();

  /*
   * Enable instruction and data caches. Do not force writethrough mode.
   */
#if INSTRUCTION_CACHE_ENABLE
  rtems_cache_enable_instruction();
#endif
#if DATA_CACHE_ENABLE
  rtems_cache_enable_data();
#endif

  /*
   *  Allocate the memory for the RTEMS Work Space.  This can come from
   *  a variety of places: hard coded address, malloc'ed from outside
   *  RTEMS world (e.g. simulator or primitive memory manager), or (as
   *  typically done by stock BSPs) by subtracting the required amount
   *  of work space from the last physical address on the CPU board.
   */

  /*
   * Initalize RTEMS IRQ system
   */
  BSP_rtems_irq_mng_init(0);

#ifdef SHOW_MORE_INIT_SETTINGS
  printk("Exit from bspstart\n");
#endif

  }

/*
 *
 *  _Thread_Idle_body
 *
 *  Replaces the one in c/src/exec/score/src/threadidlebody.c
 *  The MSR[POW] bit is set to put the CPU into the low power mode
 *  defined in HID0.  HID0 is set during starup in start.S.
 *
 */
Thread _Thread_Idle_body(uint32_t ignored )
  {

  for(;;)
    {

    asm volatile("mfmsr 3; oris 3,3,4; sync; mtmsr 3; isync; ori 3,3,0; ori 3,3,0");

    }

  return 0;

  }

