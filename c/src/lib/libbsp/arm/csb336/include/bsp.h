/*
 *  BSP CSB336 header file
 *
 *  Copyright (c) 2004 Cogent Computer Systems
 *  Written by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *
 *  http://www.rtems.com/license/LICENSE.
 *
 *
 *  $Id$
*/
#ifndef _BSP_H
#define _BSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bspopts.h>

#include <rtems.h>
#include <rtems/iosupp.h>
#include <rtems/console.h>
#include <rtems/clockdrv.h>
#include <mc9328mxl.h>
  

/* What is the input clock freq in hertz? */
#define BSP_OSC_FREQ  16000000    /* 16 MHz oscillator */
#define BSP_XTAL_FREQ 32768       /* 32.768 KHz crystal */

/* How many serial ports? */
#define CONFIGURE_NUMBER_OF_TERMIOS_PORTS 2

/* How big should the interrupt stack be? */
#define CONFIGURE_INTERRUPT_STACK_MEMORY  (16 * 1024)

extern rtems_configuration_table BSP_Configuration;

int get_perclk1_freq(void);

/*
 * Network driver configuration
 */
extern struct rtems_bsdnet_ifconfig *config;

/* Change these to match your board */
int rtems_mc9328mxl_enet_attach(struct rtems_bsdnet_ifconfig *config, 
                                void *chip);
#define RTEMS_BSP_NETWORK_DRIVER_NAME	"eth0"
#define RTEMS_BSP_NETWORK_DRIVER_ATTACH	rtems_mc9328mxl_enet_attach

#ifdef __cplusplus
}
#endif

#endif /* _BSP_H */

