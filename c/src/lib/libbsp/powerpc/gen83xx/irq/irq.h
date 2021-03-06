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
| this file declares constants of the interrupt controller        |
\*===============================================================*/
#ifndef GEN83xx_IRQ_IRQ_H
#define GEN83xx_IRQ_IRQ_H

#include <rtems.h>
#include <rtems/irq.h>

/*
 * the following definitions specify the indices used 
 * to interface the interrupt handler API
 */

/*
 * Base index for the module specific irq handlers
 */
#define BSP_ASM_IRQ_VECTOR_BASE 0x0
#define BSP_IPIC_VECTOR_BASE	BSP_ASM_IRQ_VECTOR_BASE

/*
 * Peripheral IRQ handlers related definitions
 */
#define BSP_IPIC_PER_IRQ_NUMBER	        128
#define BSP_IPIC_IRQ_LOWEST_OFFSET   BSP_IPIC_VECTOR_BASE  /* 0 */
#define BSP_IPIC_IRQ_MAX_OFFSET      (BSP_IPIC_IRQ_LOWEST_OFFSET\
                                         +BSP_IPIC_PER_IRQ_NUMBER-1)

#define BSP_IS_IPIC_IRQ(irqnum)				\
          (((irqnum) >= BSP_IPIC_IRQ_LOWEST_OFFSET) &&	\
	   ((irqnum) <= BSP_IPIC_IRQ_MAX_OFFSET))
/*
 * Processor IRQ handlers related definitions
 */
#define BSP_PROCESSOR_IRQ_NUMBER        1
#define BSP_PROCESSOR_IRQ_LOWEST_OFFSET	(BSP_IPIC_IRQ_MAX_OFFSET+1)
#define BSP_PROCESSOR_IRQ_MAX_OFFSET	(BSP_PROCESSOR_IRQ_LOWEST_OFFSET\
                                         +BSP_PROCESSOR_IRQ_NUMBER-1)

#define BSP_IS_PROCESSOR_IRQ(irqnum)				\
          (((irqnum) >= BSP_PROCESSOR_IRQ_LOWEST_OFFSET) &&	\
	   ((irqnum) <= BSP_PROCESSOR_IRQ_MAX_OFFSET))
/*
 * Summary
 */
#define BSP_IRQ_NUMBER                  (BSP_PROCESSOR_IRQ_MAX_OFFSET+1)
#define BSP_LOWEST_OFFSET		BSP_IPIC_IRQ_LOWEST_OFFSET
#define BSP_MAX_OFFSET                  BSP_PROCESSOR_IRQ_MAX_OFFSET

#define BSP_IS_VALID_IRQ(irqnum) 	\
          (BSP_IS_PROCESSOR_IRQ(irqnum)	\
           || BSP_IS_IPIC_IRQ(irqnum))

#ifndef ASM
#ifdef __cplusplus
extern "C" {
#endif

/*
 * index table for the module specific handlers, a few entries are only placeholders
 */
  typedef enum {
    BSP_IPIC_IRQ_FIRST	   = BSP_IPIC_IRQ_LOWEST_OFFSET,
    BSP_IPIC_IRQ_ERROR	   = BSP_IPIC_IRQ_LOWEST_OFFSET +  0,
    /* reserved irqs  1- 8 */
    BSP_IPIC_IRQ_UART1	   = BSP_IPIC_IRQ_LOWEST_OFFSET +  9,
    BSP_IPIC_IRQ_UART2 	   = BSP_IPIC_IRQ_LOWEST_OFFSET + 10,
    BSP_IPIC_IRQ_SEC  	   = BSP_IPIC_IRQ_LOWEST_OFFSET + 11,
    /* reserved irqs 12-13 */
    BSP_IPIC_IRQ_I2C1      = BSP_IPIC_IRQ_LOWEST_OFFSET + 14,
    BSP_IPIC_IRQ_I2C2      = BSP_IPIC_IRQ_LOWEST_OFFSET + 15,
    BSP_IPIC_IRQ_SPI       = BSP_IPIC_IRQ_LOWEST_OFFSET + 16,
    BSP_IPIC_IRQ_IRQ1      = BSP_IPIC_IRQ_LOWEST_OFFSET + 17,
    BSP_IPIC_IRQ_IRQ2      = BSP_IPIC_IRQ_LOWEST_OFFSET + 18,
    BSP_IPIC_IRQ_IRQ3      = BSP_IPIC_IRQ_LOWEST_OFFSET + 19,
    BSP_IPIC_IRQ_IRQ4      = BSP_IPIC_IRQ_LOWEST_OFFSET + 20,
    BSP_IPIC_IRQ_IRQ5      = BSP_IPIC_IRQ_LOWEST_OFFSET + 21,
    BSP_IPIC_IRQ_IRQ6      = BSP_IPIC_IRQ_LOWEST_OFFSET + 22,
    BSP_IPIC_IRQ_IRQ7      = BSP_IPIC_IRQ_LOWEST_OFFSET + 23,
    /* reserved irqs 24-31 */
    BSP_IPIC_IRQ_TSEC1_TX  = BSP_IPIC_IRQ_LOWEST_OFFSET + 32,
    BSP_IPIC_IRQ_TSEC1_RX  = BSP_IPIC_IRQ_LOWEST_OFFSET + 33,
    BSP_IPIC_IRQ_TSEC1_ERR = BSP_IPIC_IRQ_LOWEST_OFFSET + 34,
    BSP_IPIC_IRQ_TSEC2_TX  = BSP_IPIC_IRQ_LOWEST_OFFSET + 35,
    BSP_IPIC_IRQ_TSEC2_RX  = BSP_IPIC_IRQ_LOWEST_OFFSET + 36,
    BSP_IPIC_IRQ_TSEC2_ERR = BSP_IPIC_IRQ_LOWEST_OFFSET + 37,
    BSP_IPIC_IRQ_USB_DR    = BSP_IPIC_IRQ_LOWEST_OFFSET + 38,
    BSP_IPIC_IRQ_USB_MPH   = BSP_IPIC_IRQ_LOWEST_OFFSET + 39,
    /* reserved irqs 40-47 */
    BSP_IPIC_IRQ_IRQ0      = BSP_IPIC_IRQ_LOWEST_OFFSET + 48,
    /* reserved irqs 49-63 */
    BSP_IPIC_IRQ_RTC_SEC   = BSP_IPIC_IRQ_LOWEST_OFFSET + 64,
    BSP_IPIC_IRQ_PIT       = BSP_IPIC_IRQ_LOWEST_OFFSET + 65,
    BSP_IPIC_IRQ_PCI1      = BSP_IPIC_IRQ_LOWEST_OFFSET + 66,
    BSP_IPIC_IRQ_PCI2      = BSP_IPIC_IRQ_LOWEST_OFFSET + 67,
    BSP_IPIC_IRQ_RTC_ALR   = BSP_IPIC_IRQ_LOWEST_OFFSET + 68,
    BSP_IPIC_IRQ_MU        = BSP_IPIC_IRQ_LOWEST_OFFSET + 69,
    BSP_IPIC_IRQ_SBA       = BSP_IPIC_IRQ_LOWEST_OFFSET + 70,
    BSP_IPIC_IRQ_DMA       = BSP_IPIC_IRQ_LOWEST_OFFSET + 71,
    BSP_IPIC_IRQ_GTM4      = BSP_IPIC_IRQ_LOWEST_OFFSET + 72,
    BSP_IPIC_IRQ_GTM8      = BSP_IPIC_IRQ_LOWEST_OFFSET + 73,
    BSP_IPIC_IRQ_GPIO1     = BSP_IPIC_IRQ_LOWEST_OFFSET + 74,
    BSP_IPIC_IRQ_GPIO2     = BSP_IPIC_IRQ_LOWEST_OFFSET + 75,
    BSP_IPIC_IRQ_DDR       = BSP_IPIC_IRQ_LOWEST_OFFSET + 76,
    BSP_IPIC_IRQ_LBC       = BSP_IPIC_IRQ_LOWEST_OFFSET + 77,
    BSP_IPIC_IRQ_GTM2      = BSP_IPIC_IRQ_LOWEST_OFFSET + 78,
    BSP_IPIC_IRQ_GTM6      = BSP_IPIC_IRQ_LOWEST_OFFSET + 79,
    BSP_IPIC_IRQ_PMC       = BSP_IPIC_IRQ_LOWEST_OFFSET + 80,
    /* reserved irqs 81-83 */
    BSP_IPIC_IRQ_GTM3      = BSP_IPIC_IRQ_LOWEST_OFFSET + 84,
    BSP_IPIC_IRQ_GTM7      = BSP_IPIC_IRQ_LOWEST_OFFSET + 85,
    /* reserved irqs 86-89 */
    BSP_IPIC_IRQ_GTM1      = BSP_IPIC_IRQ_LOWEST_OFFSET + 90,
    BSP_IPIC_IRQ_GTM5      = BSP_IPIC_IRQ_LOWEST_OFFSET + 91,
    /* reserved irqs 92-127 */

    BSP_IPIC_IRQ_LAST     = BSP_IPIC_IRQ_MAX_OFFSET,
    BSP_DECREMENTER       = BSP_PROCESSOR_IRQ_LOWEST_OFFSET + 0
  } rtems_irq_symbolic_name;

  extern rtems_irq_connect_data *BSP_rtems_irq_tbl;
  void BSP_rtems_irq_mng_init(unsigned cpuId);

  /* ipic.c */
  rtems_status_code BSP_irq_handle_at_ipic(uint32_t excNum);
  void BSP_irq_enable_at_ipic (rtems_irq_number irqnum);
  void BSP_irq_disable_at_ipic (rtems_irq_number irqnum);

#ifdef __cplusplus
}
#endif
#endif /* ASM */

#endif /* GEN83XX_IRQ_IRQ_H */
