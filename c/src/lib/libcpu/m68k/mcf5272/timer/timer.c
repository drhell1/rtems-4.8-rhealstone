/*
 *  Timer Init
 *
 *  This module initializes TIMER 2 for on the MCF5272 for benchmarks.
 *
 *  Copyright (C) 2000 OKTET Ltd., St.-Petersburg, Russia
 *  Author: Victor V. Vengerov <vvv@oktet.ru>
 *
 *  Based on work:
 *  Author:
 *    David Fiddes, D.J@fiddes.surfaid.org
 *    http://www.calm.hw.ac.uk/davidf/coldfire/
 *
 *  COPYRIGHT (c) 1989-1998.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *
 *  http://www.rtems.com/license/LICENSE.
 * 
 *  timer.c,v 1.1 2001/10/26 19:32:40 joel Exp
 */

#include <rtems.h>
#include <bsp.h>
#include <mcf5272/mcf5272.h>

#define TRR2_VAL 65530  

uint32_t Timer_interrupts;

rtems_boolean Timer_driver_Find_average_overhead;

/* External assembler interrupt handler routine */
extern rtems_isr timerisr(rtems_vector_number vector);


/* Timer_initialize --
 *     Initialize timer 2 for accurate time measurement.
 *
 * PARAMETERS:
 *     none
 *
 * RETURNS:
 *     none
 */
void
Timer_initialize(void)
{
    uint32_t icr;
    /* Catch timer2 interrupts */
    set_vector(timerisr, BSP_INTVEC_TMR2, 0);
    
    /* Reset Timer */
    g_timer_regs->tmr2 = MCF5272_TMR_RST;
    g_timer_regs->tmr2 = MCF5272_TMR_CLK_STOP;
    g_timer_regs->tmr2 = MCF5272_TMR_RST;
    g_timer_regs->tcn2 = 0;  /* reset counter */
    Timer_interrupts   = 0;  /* Clear timer ISR counter */
    g_timer_regs->ter2 = MCF5272_TER_REF | MCF5272_TER_CAP;
    g_timer_regs->trr2 = TRR2_VAL -1 ;


    /* Set Timer 2 prescaler so that it counts in microseconds */
    g_timer_regs->tmr2 = (
        (((BSP_SYSTEM_FREQUENCY / 1000000) - 1) << MCF5272_TMR_PS_SHIFT) |
        MCF5272_TMR_CE_DISABLE                                           |
        MCF5272_TMR_ORI                                                  |
        MCF5272_TMR_FRR                                                  |
        MCF5272_TMR_CLK_MSTR                                             |
        MCF5272_TMR_RST);

    /* Initialize interrupts for timer2 */
    icr = g_intctrl_regs->icr1;
    icr = icr & ~(MCF5272_ICR1_TMR2_MASK | MCF5272_ICR1_TMR2_PI);
    icr |= (MCF5272_ICR1_TMR2_IPL(BSP_INTLVL_TMR2) | MCF5272_ICR1_TMR2_PI);
    g_intctrl_regs->icr1 = icr;

}

/*
 *  The following controls the behavior of Read_timer().
 *
 *  FIND_AVG_OVERHEAD *  instructs the routine to return the "raw" count.
 *
 *  AVG_OVEREHAD is the overhead for starting and stopping the timer.  It
 *  is usually deducted from the number returned.
 *
 *  LEAST_VALID is the lowest number this routine should trust.  Numbers
 *  below this are "noise" and zero is returned.
 */

#define AVG_OVERHEAD      0  /* It typically takes 2.0 microseconds */
                             /* (Y countdowns) to start/stop the timer. */
                             /* This value is in microseconds. */
#define LEAST_VALID       1  /* Don't trust a clicks value lower than this */

/* Read_timer --
 *     Read timer value in microsecond units since timer start.
 *
 * PARAMETERS:
 *     none
 *
 * RETURNS:
 *     number of microseconds since timer has been started
 */
int
Read_timer( void )
{
    uint16_t clicks;
    uint32_t total;

    /*
     *  Read the timer and see how many clicks it has been since counter
     *  rolled over.
     */
    clicks = g_timer_regs->tcn2;
  
    /* Stop Timer... */
    g_timer_regs->tmr2 = MCF5272_TMR_CLK_STOP | MCF5272_TMR_RST;

    /*
     *  Total is calculated by taking into account the number of timer 
     *  overflow interrupts since the timer was initialized and clicks
     *  since the last interrupts.
     */

    total = (Timer_interrupts * TRR2_VAL) + clicks;

    if ( Timer_driver_Find_average_overhead == 1 )
        return total;          /* in XXX microsecond units */

    if ( total < LEAST_VALID )
        return 0;            /* below timer resolution */

    /*
     *  Return the count in microseconds
     */
    return (total - AVG_OVERHEAD);
}


/* Empty_function --
 *     Empty function call used in loops to measure basic cost of looping
 *     in Timing Test Suite.
 *
 * PARAMETERS:
 *     none
 *
 * RETURNS:
 *     RTEMS_SUCCESSFUL
 */
rtems_status_code
Empty_function(void)
{
    return RTEMS_SUCCESSFUL;
}

/* Set_find_average_overhead --
 *     This routine is invoked by the "Check Timer" (tmck) test in the
 *     RTEMS Timing Test Suite. It makes the Read_timer routine not
 *     subtract the overhead required to initialize and read the benchmark
 *     timer.
 *
 * PARAMETERS:
 *     find_flag - boolean flag, TRUE if overhead must not be subtracted.
 *
 * RETURNS:
 *     none
 */
void
Set_find_average_overhead(rtems_boolean find_flag)
{
  Timer_driver_Find_average_overhead = find_flag;
}
