/* MVME5500I2C.c
 *
 * Copyright (c) 2003, 2004 Brookhaven National Laboratory
 * Author:    S. Kate Feng <feng1@bnl.gov>
 *            under the Deaprtment of Energy contract DE-AC02-98CH10886
 * All rights reserved.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 *
 * To read inoformation of the EEPROM via the I2C
 *
 */

#include <rtems/bspIo.h>	    /* printk */
#include "bsp/GT64260TWSI.h"

/* #define I2C_DEBUG*/
typedef unsigned int u32;
typedef unsigned char unchar;

unchar I2cAddrPack(unchar busAddr,u32 offset)
{
  return(busAddr | ((offset & 0x700) >> 7));
}
unchar I2cDevByteAddr(u32 devA2A1A0, unchar byteNum)
{
  return(( devA2A1A0 >>(byteNum*8)) & 0xff);
}
/****************************************************************************
* I2Cread_eeprom - read EEPROM VPD from the I2C
*/
int I2Cread_eeprom(unchar I2cBusAddr,u32 devA2A1A0,u32 AddrBytes,void *pBuff,u32 numBytes)
{
  int status=0, lastByte=0;
  unchar *ptr=(unchar *) pBuff;

  switch (AddrBytes) {
    case 1:
      if ((status=GT64260TWSIstart()) != -1) {
	if ((status=GT64260TWSIwrite(I2cAddrPack(I2cBusAddr,devA2A1A0)))!= -1){
	  if ((status=GT64260TWSIwrite(devA2A1A0))!=-1){
	    if ((status=GT64260TWSIstart())!=-1)
	        status=GT64260TWSIwrite(I2cAddrPack((I2cBusAddr|0x01),devA2A1A0));
	  }
        }
      }
      break;
    case 2:
      if ((status=GT64260TWSIstart())!=-1) {
	if ((status=GT64260TWSIwrite(I2cBusAddr))!= -1) {
	  if ((status=GT64260TWSIwrite(I2cDevByteAddr(devA2A1A0,1)))!=-1) {
	    if ((status=GT64260TWSIwrite(I2cDevByteAddr(devA2A1A0,0)))!= -1){
	      if ((status=GT64260TWSIstart()) != -1) {
		status = GT64260TWSIwrite((I2cBusAddr | 0x01));
              }
            }
          }
        }
      }
      break;
    case 3:
      if ((status = GT64260TWSIstart())!= -1) {
	if ((status = GT64260TWSIwrite(I2cBusAddr))!= -1) {
	  if ((status=GT64260TWSIwrite(I2cDevByteAddr(devA2A1A0,2)))!= -1){
	    if ((status=GT64260TWSIwrite(I2cDevByteAddr(devA2A1A0,1)))!= -1){
	      if ((status=GT64260TWSIwrite(I2cDevByteAddr(devA2A1A0,0)))!= -1){
  	        if ((status=GT64260TWSIstart())!= -1) {
		  status = GT64260TWSIwrite(I2cBusAddr | 0x01);
                }
              }
            }
          }
        }
      }
      break;
    default: 
      status=-1;
      break;  
  }
  if (status !=-1) {
#ifdef I2C_DEBUG
     printk("\n");
#endif
     /* read data from device */
     for ( ; numBytes > 0; numBytes-- ) {      
       if ( numBytes == 1) lastByte=1;
       if (GT64260TWSIread(ptr,lastByte) == -1) {
	 printk("numBytes %d\n", numBytes);
          return (-1);
       }
#ifdef I2C_DEBUG
       printk("%2x ", *ptr);
       if ( (numBytes % 20)==0 ) printk("\n");
#endif
       ptr++;	
     }
#ifdef I2C_DEBUG
     printk("\n");
#endif
     if (GT64260TWSIstop() == -1) return (-1);
  }
  return (status);
}

