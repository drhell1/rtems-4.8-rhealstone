/*-------------------------------------------------------------------------+
| bsp.h - ARM BSP 
+--------------------------------------------------------------------------+
| This include file contains definitions related to the ARM BSP.
+--------------------------------------------------------------------------+
|
| Copyright (c) Canon Research France SA.]
| Emmanuel Raguet, mailto:raguet@crf.canon.fr
|
|  The license and distribution terms for this file may be
|  found in found in the file LICENSE in this distribution or at
|  http://www.rtems.com/license/LICENSE.
| 
|  $Id$
+--------------------------------------------------------------------------*/


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
#include <s3c2400.h>

extern rtems_configuration_table BSP_Configuration;

#define gp32_initButtons() {rPBCON=0x0;}
#define gp32_getButtons() ( (((~rPEDAT >> 6) & 0x3 )<<8) | (((~rPBDAT >> 8) & 0xFF)<<0) )

/*functions to get the differents s3c2400 clks*/
uint32_t get_FCLK(void);
uint32_t get_HCLK(void);
uint32_t get_PCLK(void);
uint32_t get_UCLK(void);


void gp32_setPalette( unsigned char pos, uint16_t color);

/* What is the input clock freq in hertz? */
#define BSP_OSC_FREQ  12000000    /* 12 MHz oscillator */
#define M_MDIV 81	/* FCLK=133Mhz */
#define M_PDIV 2
#define M_SDIV 1
#define M_CLKDIVN 2	/* HCLK=FCLK/2, PCLK=FCLK/2 */

#define REFEN	0x1	/* enable refresh */
#define TREFMD	0x0	/* CBR(CAS before RAS)/auto refresh */
#define Trp	0x0	/* 2 clk */
#define Trc	0x3	/* 7 clk */
#define Tchr	0x2 	/* 3 clk */


/* How many serial ports? */
#define CONFIGURE_NUMBER_OF_TERMIOS_PORTS 1

/* How big should the interrupt stack be? */
#define CONFIGURE_INTERRUPT_STACK_MEMORY  (16 * 1024)

#ifdef __cplusplus
}
#endif

#endif /* _BSP_H */

