/*===============================================================*\
| Project: RTEMS generic MPC5200 BSP                              |
+-----------------------------------------------------------------+
| Partially based on the code references which are named below.   |
| Adaptions, modifications, enhancements and any recent parts of  |
| the code are:                                                   |
|                    Copyright (c) 2005                           |
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
| this file has to be included by the mscan driver                |
\*===============================================================*/
#ifndef __MSCAN_INT_H__
#define __MSCAN_INT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../mscan/mscan.h"

#define MIN_NO_OF_TQ         7
#define NO_OF_TABLE_ENTRIES  4
#define TSEG_1               1
#define TSEG_2               2
#define SJW                  3

#define MSCAN_RX_BUFF_NUM        4
#define MSCAN_TX_BUFF_NUM        3

#define MSCAN_NON_INITIALIZED_MODE   0
#define MSCAN_INITIALIZED_MODE       1
#define MSCAN_INIT_NORMAL_MODE       2
#define MSCAN_NORMAL_MODE            4
#define MSCAN_SLEEP_MODE             8

#define CAN_BIT_RATE_MAX         1000000
#define CAN_BIT_RATE_MIN         100000

#define CAN_BIT_RATE             100000
#define CAN_MAX_NO_OF_TQ         25
#define CAN_MAX_NO_OF_TQ_TSEG1   15
#define CAN_MAX_NO_OF_TQ_TSEG2   7
#define CAN_MAX_NO_OF_TQ_SJW     2

#define MSCAN_RX_BUFF_NOACTIVE   (0 << 4)
#define MSCAN_RX_BUFF_EMPTY      (1 << 6)
#define MSCAN_RX_BUFF_FULL       (1 << 5)
#define MSCAN_RX_BUFF_OVERRUN    ((MSCAN_RX_BUFF_EMPTY) | (MSCAN_RX_BUFF_FULL))
#define MSCAN_RX_BUFF_BUSY       (1 << 4)

#define MSCAN_MBUFF_MASK         0x07

#define MSCAN_TX_BUFF0           (1 << 0)
#define MSCAN_TX_BUFF1           (1 << 1)
#define MSCAN_TX_BUFF2           (1 << 2)

#define MSCAN_IDE                (1 << 0)
#define MSCAN_RTR                (1 << 1)
#define MSCAN_READ_RXBUFF_0      (1 << 2)
#define MSCAN_READ_RXBUFF_1      (1 << 2)
#define MSCAN_READ_RXBUFF_2      (1 << 2)
#define MSCAN_READ_RXBUFF_3      (1 << 2)

#define CTL0_RXFRM               (1 << 7)
#define CTL0_RXACT               (1 << 6)
#define CTL0_CSWAI               (1 << 5)
#define CTL0_SYNCH               (1 << 4)
#define CTL0_TIME                (1 << 3)
#define CTL0_WUPE                (1 << 2)
#define CTL0_SLPRQ               (1 << 1)
#define CTL0_INITRQ              (1 << 0)

#define CTL1_CANE                (1 << 7)
#define CTL1_CLKSRC              (1 << 6)
#define CTL1_LOOPB               (1 << 5)
#define CTL1_LISTEN              (1 << 4)
#define CTL1_WUPM                (1 << 2)
#define CTL1_SLPAK               (1 << 1)
#define CTL1_INITAK              (1 << 0)

#define BTR0_SJW(btr0)           ((btr0) << 6)
#define BTR0_BRP(btr0)           ((btr0) << 0)

#define BTR1_SAMP                (1 << 7)
#define BTR1_TSEG_22_20(btr1)    ((btr1) << 4)
#define BTR1_TSEG_13_10(btr1)    ((btr1) << 0)

#define RFLG_WUPIF               (1 << 7)
#define RFLG_CSCIF               (1 << 6)
#define RFLG_RSTAT               (3 << 4)
#define RFLG_TSTAT               (3 << 2)
#define RFLG_OVRIF               (1 << 1)
#define RFLG_RXF                 (1 << 0)
#define RFLG_GET_RX_STATE(rflg)  (((rflg) >> 4) & 0x03)
#define RFLG_GET_TX_STATE(rflg)  (((rflg) >> 2) & 0x03)

#define MSCAN_STATE_OK           0
#define MSCAN_STATE_ERR          1
#define MSCAN_STATE_WRN		     2
#define MSCAN_STATE_BUSOFF       3

#define RIER_WUPIE               (1 << 7)
#define RIER_CSCIE               (1 << 6)
#define RIER_RSTAT(rier)         ((rier) << 4)
#define RIER_TSTAT(rier)         ((rier) << 2)
#define RIER_OVRIE               (1 << 1)
#define RIER_RXFIE               (1 << 0)

#define TFLG_TXE2                (1 << 2)
#define TFLG_TXE1                (1 << 1)
#define TFLG_TXE0                (1 << 0)

#define TIER_TXEI2               (1 << 2)
#define TIER_TXEI1               (1 << 1)
#define TIER_TXEI0               (1 << 0)

#define TARQ_ABTRQ2              (1 << 2)
#define TARQ_ABTRQ1              (1 << 1)
#define TARQ_ABTRQ0              (1 << 0)

#define TAAK_ABTRQ2              (1 << 2)
#define TAAK_ABTRQ1              (1 << 1)
#define TAAK_ABTRQ0              (1 << 0)

#define BSEL_TX2                 (1 << 2)
#define BSEL_TX1                 (1 << 1)
#define BSEL_TX0                 (1 << 0)

#define IDAC_IDAM1               (1 << 5)
#define IDAC_IDAM0               (1 << 4)
#define IDAC_IDHIT(idac)         ((idac) & 0x7)

#define TX_MBUF_SEL(buf_no)      (1 << (buf_no))
#define TX_DATA_LEN(len)         ((len) & 0x0F)

#define TX_MBUF_EMPTY(val)       (1 << (val))

#define ID_RTR                   (1 << 4)

#define SET_IDR0(u16)            ((uint8_t)((u16) >> 3))
#define SET_IDR1(u16)            (MSCAN_MESS_ID_HAS_RTR(u16) ? ((uint8_t)(((u16) & 0x0007) << 5))|((uint8_t)(ID_RTR)) : ((uint8_t)(((u16) & 0x0007) << 5)))

#define SET_IDR2(u16)            SET_IDR0(u16)
#define SET_IDR3(u16)            SET_IDR1(u16)

#define SET_IDR4(u16)            SET_IDR0(u16)
#define SET_IDR5(u16)            SET_IDR1(u16)

#define SET_IDR6(u16)            SET_IDR0(u16)
#define SET_IDR7(u16)            SET_IDR1(u16)

#define GET_IDR0(u16)            ((uint16_t) ((u16) << 3))
#define GET_IDR1(u16)            ((((u16)&(ID_RTR))==(ID_RTR)) ? (uint16_t) ((((u16) >> 5)&0x0007)|MSCAN_MESS_ID_RTR) : (uint16_t)(((u16) >> 5)&0x0007))

#define GET_IDR2(u16)            GET_IDR0(u16)
#define GET_IDR3(u16)            GET_IDR1(u16)

#define GET_IDR4(u16)            GET_IDR0(u16)
#define GET_IDR5(u16)            GET_IDR1(u16)

#define GET_IDR6(u16)            GET_IDR0(u16)
#define GET_IDR7(u16)            GET_IDR1(u16)

#define SET_IDMR0(u16)           ((uint8_t)((u16) >> 3))
#define SET_IDMR1(u16)           (MSCAN_MESS_ID_HAS_RTR(u16) ? ((uint8_t) (((((u16) & 0x0007) << 5)|((uint8_t)(ID_RTR)))|0x0007)) : ((uint8_t)((((u16) & 0x0007) << 5))|0x0007))

#define SET_IDMR2(u16)           SET_IDMR0(u16)
#define SET_IDMR3(u16)           SET_IDMR1(u16)

#define SET_IDMR4(u16)           SET_IDMR0(u16)
#define SET_IDMR5(u16)           SET_IDMR1(u16)

#define SET_IDMR6(u16)           SET_IDMR0(u16)
#define SET_IDMR7(u16)           SET_IDMR1(u16)

#define GET_IDMR0(u16)           ((uint16_t)((u16) << 3))
#define GET_IDMR1(u16)           ((((u16)&(ID_RTR))==(ID_RTR)) ? (uint16_t) ((((u16) >> 5)&0x0007)|MSCAN_MESS_ID_RTR) : (uint16_t)(((u16) >> 5)&0x0007))

#define GET_IDMR2(u16)           GET_IDMR0(u16)
#define GET_IDMR3(u16)           GET_IDMR1(u16)

#define GET_IDMR4(u16)           GET_IDMR0(u16)
#define GET_IDMR5(u16)           GET_IDMR1(u16)

#define GET_IDMR6(u16)           GET_IDMR0(u16)
#define GET_IDMR7(u16)           GET_IDMR1(u16)

#define NO_OF_MSCAN_RX_BUFF 	 20
#define MSCAN_MESSAGE_SIZE(size) (((size)%CPU_ALIGNMENT) ? (((size) + CPU_ALIGNMENT)-((size) + CPU_ALIGNMENT)%CPU_ALIGNMENT) : (size))

#define TX_BUFFER_0              0
#define TX_BUFFER_1              1
#define TX_BUFFER_2              2

#define RX_BUFFER_0              0
#define RX_BUFFER_1              1
#define RX_BUFFER_2              2
#define RX_BUFFER_3              3

#define NO_OF_MSCAN_TX_BUFF      20
#define RING_BUFFER_EMPTY(rbuff) ((((rbuff)->head) == ((rbuff)->tail)) ? TRUE : FALSE)
#define RING_BUFFER_FULL(rbuff)  ((((rbuff)->head) == ((rbuff)->tail)) ? TRUE : FALSE)


typedef struct _mscan_handle
  {
  uint8_t mscan_channel;
  void (*toucan_callback)(int16_t);
  } mscan_handle;

struct ring_buf
    {
    struct can_message * volatile buf_ptr;
    struct can_message * volatile head_ptr;
    struct can_message * volatile tail_ptr;
    };

struct mpc5200_rx_cntrl
  {
  struct can_message can_rx_message[MSCAN_RX_BUFF_NUM];
  };

struct mscan_channel_info
  {
  volatile struct mpc5200_mscan *regs;
  uint32_t   int_rx_err;
  rtems_id   rx_qid;
  uint32_t   rx_qname;
  rtems_id   tx_rb_sid;
  uint32_t   tx_rb_sname;
  uint8_t    id_extended;
  uint8_t    mode;
  uint8_t    tx_buf_no;
  struct ring_buf tx_ring_buf;
  };

extern void CanInterrupt_A(int16_t);
extern void CanInterrupt_B(int16_t);

/*MSCAN driver internal functions */
void mscan_hardware_initialize(rtems_device_major_number, uint32_t, void *);
void mpc5200_mscan_int_enable(volatile struct mpc5200_mscan *);
void mpc5200_mscan_int_disable(volatile struct mpc5200_mscan *);
void mpc5200_mscan_enter_sleep_mode(volatile struct mpc5200_mscan *);
void mpc5200_mscan_exit_sleep_mode(volatile struct mpc5200_mscan *);
void mpc5200_mscan_enter_init_mode(volatile struct mpc5200_mscan *);
void mpc5200_mscan_exit_init_mode(volatile struct mpc5200_mscan *);
void mpc5200_mscan_wait_sync(volatile struct mpc5200_mscan *);
void mpc5200_mscan_perform_init_mode_settings(volatile struct mpc5200_mscan *);
void mpc5200_mscan_perform_normal_mode_settings(volatile struct mpc5200_mscan *);
rtems_status_code mpc5200_mscan_set_mode(rtems_device_minor_number, uint8_t);
rtems_status_code mscan_channel_initialize(rtems_device_major_number, rtems_device_minor_number);
uint8_t prescaler_calculation(uint32_t, uint32_t, uint8_t *);
void mpc5200_mscan_perform_bit_time_settings(volatile struct mpc5200_mscan *, uint32_t, uint32_t);


#ifdef __cplusplus
}
#endif

#endif /* __MSCAN_H__ */
