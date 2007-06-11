/*
 *  CPU Usage Reporter
 *
 *  COPYRIGHT (c) 1989-2007
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

#include <rtems/cpuuse.h>
#include <rtems/bspIo.h>

#if defined(RTEMS_ENABLE_NANOSECOND_RATE_MONOTONIC_STATISTICS) || \
    defined(RTEMS_ENABLE_NANOSECOND_CPU_USAGE_STATISTICS)
  #include <rtems/score/timespec.h>

  /* We print to 1/10's of milliseconds */
  #define NANOSECONDS_DIVIDER 100000
  #define PERCENT_FMT "%04" PRId32
#endif

#ifndef RTEMS_ENABLE_NANOSECOND_CPU_USAGE_STATISTICS
  uint32_t   CPU_usage_Ticks_at_last_reset;
#endif

/*PAGE
 *
 *  rtems_cpu_usage_report
 */

void rtems_cpu_usage_report( void )
{
  uint32_t             i;
  uint32_t             api_index;
  Thread_Control      *the_thread;
  Objects_Information *information;
  char                 name[5];
  uint32_t             ival, fval;
  #ifdef RTEMS_ENABLE_NANOSECOND_CPU_USAGE_STATISTICS
    struct timespec    uptime;
  #else
    uint32_t           total_units = 0;
  #endif

  /*
   *  When not using nanosecond CPU usage resolution, we have to count
   *  the number of "ticks" we gave credit for to give the user a rough
   *  guideline as to what each number means proportionally.
   */
  #ifdef RTEMS_ENABLE_NANOSECOND_CPU_USAGE_STATISTICS
    _TOD_Get_uptime( &uptime );
  #else
    for ( api_index = 1 ; api_index <= OBJECTS_APIS_LAST ; api_index++ ) {
      if ( !_Objects_Information_table[ api_index ] )
        continue;
      information = _Objects_Information_table[ api_index ][ 1 ];
      if ( information ) {
        for ( i=1 ; i <= information->maximum ; i++ ) {
          the_thread = (Thread_Control *)information->local_table[ i ];

          if ( the_thread )
            total_units += the_thread->ticks_executed;
        }
      }
    }
  #endif
  
  printk( "CPU Usage by thread\n"
    #ifdef RTEMS_ENABLE_NANOSECOND_CPU_USAGE_STATISTICS
          "   ID        NAME    SECONDS   PERCENT\n"
    #else
          "   ID        NAME     TICKS    PERCENT\n"
    #endif
  );

  for ( api_index = 1 ;
        api_index <= OBJECTS_APIS_LAST ;
        api_index++ ) {
    if ( !_Objects_Information_table[ api_index ] )
      continue;
    information = _Objects_Information_table[ api_index ][ 1 ];
    if ( information ) {
      for ( i=1 ; i <= information->maximum ; i++ ) {
        the_thread = (Thread_Control *)information->local_table[ i ];

        if ( !the_thread )
          continue;

        rtems_object_get_name( the_thread->Object.id, sizeof(name), name );
 
        printk( "0x%08" PRIx32 "   %4s    ", the_thread->Object.id, name );

        #ifdef RTEMS_ENABLE_NANOSECOND_CPU_USAGE_STATISTICS
          _Timespec_Divide( &the_thread->cpu_time_used, &uptime, &ival, &fval );

          printk(
            "%" PRId32 ".%06d"                 /* cpu time used */     
            " %3" PRId32 ".%02" PRId32 "\n",  /* percentage */
            the_thread->cpu_time_used.tv_sec,
              the_thread->cpu_time_used.tv_nsec /
                 TOD_NANOSECONDS_PER_MICROSECOND,
            ival,
            fval
          );
        #else
          ival = (total_units) ?
                   the_thread->ticks_executed * 10000 / total_units : 0;
          fval = ival % 100;
          ival /= 100;
          printk(
            "%8" PRId32 "     %3" PRId32 ".%02" PRId32"\n",
            the_thread->ticks_executed,
            ival,
            fval
          );
        #endif
      }
    }
  }

  #ifdef RTEMS_ENABLE_NANOSECOND_CPU_USAGE_STATISTICS
    printk( "Uptime %d.%06d seconds\n\n",
       uptime.tv_sec,
       uptime.tv_nsec / TOD_NANOSECONDS_PER_MICROSECOND
    );
  #else
    printk(
      "Ticks since last reset = %" PRId32 "\n",
      _Watchdog_Ticks_since_boot - CPU_usage_Ticks_at_last_reset
    );
    printk( "Total Units = %" PRId32 "\n\n", total_units );
  #endif
}