/*  timer.c
 *
 *  This file implements a benchmark timer using the General Purpose Timer.
 *
 *  Notes:
 *
 *  BSP_TIMER_AVG_OVERHEAD and BSP_TIMER_LEAST_VALID are required to be
 *  provided in bsp.h
 *
 *  COPYRIGHT (c) 1989-1997.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may in
 *  the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#include <assert.h>

#include <bsp.h>

uint64_t         Timer_driver_Start_time;

rtems_boolean Timer_driver_Find_average_overhead;

/*
 * Timer_initialize
 */

void Timer_initialize()
{

  /*
   *  Timer runs long and accurate enough not to require an interrupt.
   */

  Timer_driver_Start_time = PPC_Get_timebase_register();
}

/*
 *  Read_timer
 */

int Timer_read()
{
  uint64_t          clicks;
  uint64_t          total64;
  uint32_t          total;

  /* approximately CLOCK_SPEED clicks per microsecond */

  clicks = PPC_Get_timebase_register();

  assert( clicks > Timer_driver_Start_time );

  total64 = clicks - Timer_driver_Start_time;

  assert( total64 <= 0xffffffff );  /* fits into a uint32_t   */

  total = (uint32_t) total64;

  if ( Timer_driver_Find_average_overhead == 1 )
    return total;          /* in "clicks" of the decrementer units */

  if ( total < BSP_TIMER_LEAST_VALID )
    return 0;            /* below timer resolution */

  return BSP_Convert_decrementer(total - BSP_TIMER_AVG_OVERHEAD);
}

rtems_status_code Empty_function( void )
{
  return RTEMS_SUCCESSFUL;
}

void Set_find_average_overhead(
  rtems_boolean find_flag
)
{
  Timer_driver_Find_average_overhead = find_flag;
}
