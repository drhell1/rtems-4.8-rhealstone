/*===============================================================*\
| Project: RTEMS support for MPC83xx                              |
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
| this file contains the MPC83xx I2C driver declarations          |
\*===============================================================*/
#ifndef _MPC83XX_I2CDRV_H
#define _MPC83XX_I2CDRV_H

#include <mpc83xx/mpc83xx.h>
#include <rtems/libi2c.h>
#include <rtems/irq.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mpc83xx_i2c_softc {
  m83xxI2CRegisters_t *reg_ptr;
  int                  initialized;
  rtems_irq_number     irq_number;
  rtems_id             irq_sema_id;
} mpc83xx_i2c_softc_t ;

typedef struct {
  rtems_libi2c_bus_t	   bus_desc;	
  struct mpc83xx_i2c_softc softc;
} mpc83xx_i2c_desc_t;


extern rtems_libi2c_bus_ops_t mpc83xx_i2c_ops;

#ifdef __cplusplus
}
#endif


#endif /* _MPC83XX_I2CDRV_H */
