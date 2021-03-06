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
| this file contains definitions for the mpc5200 hw registers     |
\*===============================================================*/

#ifndef __MPC5200_h__
#define __MPC5200_h__

/* Additional Harpo Core SPR definitions (603le only) */
#define	CSRR0	58		/* Critical Interrupt SRR0 */
#define	CSRR1	59		/* Critical Interrupt SRR1 */
#define	SPRG4   276		/* Special Purpose Register 4 */
#define	SPRG5   277		/* Special Purpose Register 5 */
#define	SPRG6   278		/* Special Purpose Register 6 */
#define	SPRG7   279		/* Special Purpose Register 7 */
#define	IBAT4U	560		/* Instruction BAT #0 Upper/Lower */
#define	IBAT4L	561
#define	IBAT5U	562		/* Instruction BAT #1 Upper/Lower */
#define	IBAT5L	563
#define	IBAT6U	564		/* Instruction BAT #2 Upper/Lower */
#define	IBAT6L	565
#define	IBAT7U	566		/* Instruction BAT #3 Upper/Lower */
#define	IBAT7L	567
#define	DBAT4U	568		/* Data BAT #0 Upper/Lower */
#define	DBAT4L	569
#define	DBAT5U	570		/* Data BAT #1 Upper/Lower */
#define	DBAT5L	571
#define	DBAT6U	572		/* Data BAT #2 Upper/Lower */
#define	DBAT6L	573
#define	DBAT7U	574		/* Data BAT #3 Upper/Lower */
#define	DBAT7L	575
#define	DABR2	1000		/* Data Address Breakpoint #2 */
#define	DBCR	1001		/* Data Address Breakpoint Control */
#define	IBCR	1002		/* Instruction Breakpoint Control */
#define	HID1	1009		/* Hardware Implementation 1 */
#define	HID2	1011		/* Hardware Implementation 2 */
#define	DABR	1013		/* Data Address Breakpoint */
#define	IABR2	1018		/* Instruction Breakpoint #2 */

/* 
 * Initial post-reset location of MGT5100 module base address register (MBAR) 
 */
#define	MBAR_RESET 	    0x80000000

/* 
 * Location and size of onchip SRAM (relative to MBAR)
 */
#define ONCHIP_SRAM_OFFSET  0x8000
#define ONCHIP_SRAM_SIZE    0x4000

#ifndef ASM
#include <rtems.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MPC5200_CAN_NO                               2
#define MPC5200_PSC_NO                               6
  /* XXX: there are only 6 PSCs, but PSC6 has an extra register gap
   *      from PSC5, therefore we instantiate seven(!) PSC register sets
   */
#define MPC5200_PSC_REG_SETS                         7

#define MPC5200_GPT_NO                               8
#define MPC5200_SLT_NO                               2

/*
 * Bit fields for FEC interrupts, ievent and imask above.
 */
#define FEC_INTR_HBERR		0x80000000	/* heartbeat error				*/
#define FEC_INTR_BABR		0x40000000	/* babbling receive error		*/
#define FEC_INTR_BABT		0x20000000	/* babbling transmit error		*/
#define FEC_INTR_GRA		0x10000000	/* graceful stop complete		*/
#define FEC_INTR_TFINT		0x08000000	/* transmit frame interrupt		*/
/*							0x04000000	reserved						*/
/*							0x02000000	reserved						*/
/*							0x01000000	reserved						*/
#define FEC_INTR_MII		0x00800000	/* MII interrupt				*/
/*							0x00400000	reserved						*/
#define FEC_INTR_LATE_COL	0x00200000	/* late collision				*/
#define FEC_INTR_COL_RETRY	0x00100000	/* collision retry limit		*/
#define FEC_INTR_XFIFO_UN	0x00080000	/* transmit FIFO error			*/
#define FEC_INTR_XFIFO_ERR	0x00040000	/* transmit FIFO error			*/
#define FEC_INTR_RFIFO_ERR	0x00020000	/* receive FIFO error			*/
/*							0x00010000	reserved						*/
/*							0x0000ffff	reserved						*/
#define FEC_INTR_HBEEN		FEC_INTR_HBERR
#define FEC_INTR_BREN		FEC_INTR_BABR
#define FEC_INTR_BTEN		FEC_INTR_BABT
#define FEC_INTR_GRAEN		FEC_INTR_GRA
#define FEC_INTR_TFINTEN	FEC_INTR_TFINT
#define FEC_INTR_MIIEN		FEC_INTR_MII
#define FEC_INTR_LCEN		FEC_INTR_LATE_COL
#define FEC_INTR_CRLEN		FEC_INTR_COL_RETRY
#define FEC_INTR_XFUNEN		FEC_INTR_XFIFO_UN
#define FEC_INTR_XFERREN	FEC_INTR_XFIFO_ERR
#define FEC_INTR_RFERREN	FEC_INTR_RFIFO_ERR
#define FEC_INTR_CLEAR_ALL	0xffffffff	/* clear all interrupt events	*/
#define FEC_INTR_MASK_ALL	0x00000000	/* mask all interrupt events	*/

/*
 * Bit fields for FEC ethernet control, ecntrl above.
 */
#define FEC_ECNTRL_TAG		0xf0000000	/* TBUS tag bits				*/
/*							0x08000000	reserved						*/
#define FEC_ECNTRL_TESTMD	0x04000000	/* test mode					*/
/*							0x03fffff8	reserved						*/
#define FEC_ECNTRL_OE		0x00000004	/* FEC output enable			*/
#define FEC_ECNTRL_EN		0x00000002	/* ethernet enable				*/
#define FEC_ECNTRL_RESET	0x00000001	/* ethernet controller reset	*/

/*
 * Bit fields for FEC receive control, r_cntrl above.
 */
/*							0xf1000000	reserved						*/
#define FEC_RCNTRL_MAX_FL	0x07ff0000	/* maximum frame length			*/
#define FEC_RCNTRL_MAX_FL_SHIFT 16
/*							0x0000ffc0	reserved						*/
#define FEC_RCNTRL_FCE		0x00000020	/* flow control enable			*/
#define FEC_RCNTRL_BC_REJ	0x00000010	/* broadcast frame reject		*/
#define FEC_RCNTRL_PROM		0x00000008	/* promiscuous mode				*/
#define FEC_RCNTRL_MII_MODE	0x00000004	/* select 18-wire (MII) mode	*/
#define FEC_RCNTRL_DRT		0x00000002	/* disable receive on transmit	*/
#define FEC_RCNTRL_LOOP		0x00000001	/* internal loopback			*/

/*
 * Bit fields for FEC transmit control, x_cntrl above.
 */
/*							0xffffffe0	reserved						*/
#define FEC_XCNTRL_RFC_PAUS 0x00000010	/* FDX flow control pause rx	*/
#define FEC_XCNTRL_TFC_PAUS	0x00000008	/* assert a PAUSE frame			*/
#define FEC_XCNTRL_FDEN		0x00000004	/* full duplex enable			*/
#define FEC_XCNTRL_HBC		0x00000002	/* heartbeat control			*/
#define FEC_XCNTRL_GTS		0x00000001	/* graceful transmit stop		*/

/*
 * Bit fields for FEC transmit status, x_status above.
 */
/*							0xfc000000	reserved						*/
#define FEC_XSTAT_DEF		0x02000000	/* defer						*/
#define FEC_XSTAT_HB		0x01000000	/* heartbeat error				*/
#define FEC_XSTAT_LC		0x00800000	/* late collision				*/
#define FEC_XSTAT_RL		0x00400000	/* retry limit					*/
#define FEC_XSTAT_RC		0x003c0000	/* retry count					*/
#define FEC_XSTAT_UN		0x00020000	/* underrun						*/
#define FEX_XSTAT_CSL		0x00010000	/* carrier sense lost			*/
/*							0x0000ffff	reserved						*/

/*
 * Bit fields for FEC transmit FIFO watermark, x_wmrk above.
 */
#define FEC_XWMRK_64		0x00000000	/*   64 bytes written to TxFIFO	*/
#define FEC_XWMRK_128		0x00000001	/*  128 bytes written to TxFIFO	*/
#define FEC_XWMRK_192		0x00000002	/*  192 bytes written to TxFIFO	*/
#define FEC_XWMRK_256		0x00000003	/*  256 bytes written to TxFIFO	*/
#define FEC_XWMRK_320		0x00000004	/*  320 bytes written to TxFIFO	*/
#define FEC_XWMRK_384		0x00000005	/*  384 bytes written to TxFIFO	*/
#define FEC_XWMRK_448		0x00000006	/*  448 bytes written to TxFIFO	*/
#define FEC_XWMRK_512		0x00000007	/*  512 bytes written to TxFIFO	*/
#define FEC_XWMRK_576		0x00000008	/*  576 bytes written to TxFIFO	*/
#define FEC_XWMRK_640		0x00000009	/*  640 bytes written to TxFIFO	*/
#define FEC_XWMRK_704		0x0000000a	/*  704 bytes written to TxFIFO	*/
#define FEC_XWMRK_768		0x0000000b	/*  768 bytes written to TxFIFO	*/
#define FEC_XWMRK_832		0x0000000c	/*  832 bytes written to TxFIFO	*/
#define FEC_XWMRK_896		0x0000000d	/*  896 bytes written to TxFIFO	*/
#define FEC_XWMRK_960		0x0000000e	/*  960 bytes written to TxFIFO	*/
#define FEC_XWMRK_1024		0x0000000f	/* 1024 bytes written to TxFIFO	*/

/*
 * Bit fields for FEC transmit finite state machine.
 */
/*							0xfc000000	reserved						*/
#define FEC_FSM_CRC			0x02000000	/* append CRC (typical use)		*/
#define FEC_FSM_ENFSM		0x01000000	/* enable CRC FSM (typical use)	*/
/*							0x00ffffff	reserved						*/

/*
 * Bit fields for FEC FIFOs, rfifo_status, rfifo_cntrl, tfifo_status
 * and tfifo_cntrl.
 */
#define FEC_FIFO_STAT_IP	0x80000000	/* illegal pointer, sticky		*/
/*							0x70000000	reserved						*/
#define FEC_FIFO_STAT_FRAME	0x0f000000	/* frame indicator				*/
#define FEC_FIFO_STAT_FAE	0x00800000	/* frame accept error			*/
#define FEC_FIFO_STAT_RXW	0x00400000	/* receive wait condition		*/
#define FEC_FIFO_STAT_UF	0x00200000	/* underflow					*/
#define FEC_FIFO_STAT_OF	0x00100000	/* overflow						*/
#define FEC_FIFO_STAT_FR	0x00080000	/* frame ready, read-only		*/
#define FEC_FIFO_STAT_FULL	0x00040000	/* full alarm, read-only		*/
#define FEC_FIFO_STAT_ALARM	0x00020000	/* fifo alarm					*/
#define FEC_FIFO_STAT_EMPTY	0x00010000	/* empty, read-only				*/
/*							0x0000ffff	reserved						*/
#define FEC_FIFO_STAT_ERROR	( FEC_FIFO_STAT_IP	\
							| FEC_FIFO_STAT_FAE	\
							| FEC_FIFO_STAT_RXW	\
							| FEC_FIFO_STAT_UF	\
							| FEC_FIFO_STAT_OF	\
							)

/*								0x80000000	reserved						*/
#define FEC_FIFO_CNTRL_WCTL		0x40000000	/* write control				*/
#define FEC_FIFO_CNTRL_WFR		0x20000000	/* write frame					*/
/*								0x10000000	reserved						*/
#define FEC_FIFO_CNTRL_FRAME	0x08000000	/* frame mode enable	*/
#define FEC_FIFO_CNTRL_GR		0x07000000	/* last transfer granularity	*/
#define FEC_FIFO_CNTRL_GR_SHIFT	24
#define FEC_FIFO_CNTRL_IP_MASK	0x00800000	/* illegal pointer mask			*/
#define FEC_FIFO_CNTRL_FAE_MASK	0x00400000	/* frame accept mask			*/
#define FEC_FIFO_CNTRL_RXW_MASK	0x00200000	/* receive wait mask			*/
#define FEC_FIFO_CNTRL_UF_MASK	0x00100000	/* underflow mask				*/
#define FEC_FIFO_CNTRL_OF_MASK	0x00080000	/* overflow mask				*/
/*								0x0007ffff	reserved						*/

/*
*************************************************************************
*                 MPC5x00 internal register memory map                  *
*************************************************************************
*/
typedef struct mpc5200_
	{
	/*
	 * memory map registers (MBAR + 0)
	 */
	volatile uint8_t		mm[0x80];

	/*
	 * arbiter registers (processor bus) (MBAR + 0x80)
	 */
	volatile uint8_t		arb[0x80];

	/*
	 * SDRAM memory controller registers (MBAR + 0x100)
	 */
	volatile uint8_t		mc[0x100];

	/*
	 * clock distribution module registers (MBAR + 0x200)
	 */
	volatile uint8_t		cdm[0x100];

	/*
	 * chip selct controller registers(MBAR + 0x300)
	 */
	volatile uint8_t		csc[0x100];

	/*
	 * SmartComm timer registers (MBAR + 0x400)
	 */
	volatile uint8_t		sct[0x100];

	/*
	 * interrupt controller registers (MBAR + 0x500)
	 */
    volatile uint32_t    per_mask;			/* + 0x00 */
	volatile uint32_t    per_pri_1;			/* + 0x04 */
	volatile uint32_t    per_pri_2;			/* + 0x08 */
	volatile uint32_t    per_pri_3;			/* + 0x0C */
	volatile uint32_t    ext_en_type;		/* + 0x10 */
	volatile uint32_t    crit_pri_main_mask;/* + 0x14 */
	volatile uint32_t    main_pri_1;        /* + 0x18 */
	volatile uint32_t    main_pri_2;		/* + 0x1C */
	volatile uint32_t    res1;				/* + 0x20 */
	volatile uint32_t    pmce;				/* + 0x24 */
	volatile uint32_t    csa;				/* + 0x28 */
	volatile uint32_t    msa;				/* + 0x2C */
	volatile uint32_t    psa;				/* + 0x30 */
	volatile uint32_t    res2;				/* + 0x34 */
	volatile uint32_t    psa_be;			/* + 0x38 */
	volatile uint8_t     res3[0xC4];		/* + 0x3C */

	/*
	 * general pupose timer registers (MBAR + 0x600/+0x610/+0x620/+0x630/+0x640/+0x650/+0x660/+0x670)
	 */
  struct mpc5200_gpt
    {
	volatile uint32_t	 emsel;     /* + 0x00 */
	volatile uint32_t    count_in;  /* + 0x04 */
	volatile uint32_t    pwm_conf;  /* + 0x08 */
	volatile uint32_t    status;    /* + 0x0C */
    } gpt[MPC5200_GPT_NO];

#define GPT_STATUS_RESET           0x0000000F
#define GPT_STATUS_TEXP            (1 << 3)
#define GPT_STATUS_PIN             (1 << 8)
#define GPT_EMSEL_GPIO_DIR         (2 << 4)
#define GPT_EMSEL_GPIO_OUT         (1 << 4)
#define GPT_EMSEL_GPIO_OUT_HIGH    (3 << 4)
#define GPT_EMSEL_TIMER_MS_GPIO    (4 << 0)
#define GPT_EMSEL_GPIO_IN          (0 << 0)
#define GPT_EMSEL_CE               (1 << 12)
#define GPT_EMSEL_ST_CONT          (1 << 10)
#define GPT_EMSEL_INTEN            (1 << 8)
#define GPT_EMSEL_WDEN				  (1 << 15)

#define GPT0                       0
#define GPT1                       1
#define GPT2                       2
#define GPT3                       3
#define GPT4                       4
#define GPT5                       5
#define GPT6                       6
#define GPT7                       7

	volatile uint8_t	 gpt_res[0x80];

	/*
	 * slice time registers (MBAR + 0x700/+0x710)
	 */
  struct mpc5200_slt
    {
	volatile uint32_t	 tcr;       /* + 0x00 */
	volatile uint32_t	 cntrl;     /* + 0x04 */
	volatile uint32_t	 cvr;       /* + 0x08 */
	volatile uint32_t	 tsr;       /* + 0x0C */
    } slt[MPC5200_SLT_NO];

    volatile uint8_t	 slt_res[0xE0];

	/*
	 * real time clock registers (MBAR + 0x800)
	 */
	volatile uint8_t		rtc[0x100];


    /*
     * MSCAN registers (MBAR + 0x900 /+0x980)
     */
  struct mpc5200_mscan
    {
	volatile uint8_t		ctl0;		/* + 0x0 */
	volatile uint8_t		ctl1;		/* + 0x1 */
	volatile uint8_t		res1;		/* + 0x2 */
	volatile uint8_t		res2;		/* + 0x3 */
	volatile uint8_t		btr0;		/* + 0x4 */
	volatile uint8_t		btr1;		/* + 0x5 */
	volatile uint8_t		res3;		/* + 0x6 */
	volatile uint8_t		res4;		/* + 0x7 */
	volatile uint8_t		rflg;		/* + 0x8 */
	volatile uint8_t		rier;		/* + 0x9 */
	volatile uint8_t		res5;		/* + 0xA */
	volatile uint8_t		res6;		/* + 0xB */
	volatile uint8_t		tflg;		/* + 0xC */
	volatile uint8_t		tier;		/* + 0xD */
	volatile uint8_t		res7;		/* + 0xE */
	volatile uint8_t		res8;		/* + 0xF */
	volatile uint8_t		tarq;		/* + 0x10 */
	volatile uint8_t		taak;		/* + 0x11 */
	volatile uint8_t		res9;		/* + 0x12 */
	volatile uint8_t		res10;		/* + 0x13 */
	volatile uint8_t		bsel;		/* + 0x14 */
	volatile uint8_t		idac;		/* + 0x15 */
	volatile uint8_t		res11;		/* + 0x16 */
	volatile uint8_t		res12;		/* + 0x17 */
	volatile uint8_t		res13;		/* + 0x18 */
	volatile uint8_t		res14;		/* + 0x19 */
	volatile uint8_t		res15;		/* + 0x1A */
	volatile uint8_t		res16;		/* + 0x1B */
	volatile uint8_t		rxerr;		/* + 0x1C */
	volatile uint8_t		txerr;		/* + 0x1D */
	volatile uint8_t		res17;		/* + 0x1E */
	volatile uint8_t		res18;		/* + 0x1F */
	volatile uint8_t		idar0;		/* + 0x20 */
	volatile uint8_t		idar1;		/* + 0x21 */
	volatile uint8_t		res19;		/* + 0x22 */
	volatile uint8_t		res20;		/* + 0x23 */
	volatile uint8_t		idar2;		/* + 0x24 */
	volatile uint8_t		idar3;		/* + 0x25 */
	volatile uint8_t		res21;		/* + 0x26 */
	volatile uint8_t		res22;		/* + 0x27 */
	volatile uint8_t		idmr0;		/* + 0x28 */
	volatile uint8_t		idmr1;		/* + 0x29 */
	volatile uint8_t		res23;		/* + 0x2A */
	volatile uint8_t		res24;		/* + 0x2B */
	volatile uint8_t		idmr2;		/* + 0x2C */
	volatile uint8_t		idmr3;		/* + 0x2D */
	volatile uint8_t		res25;		/* + 0x2E */
	volatile uint8_t		res26;		/* + 0x2F */
	volatile uint8_t		idar4;		/* + 0x30 */
	volatile uint8_t		idar5;		/* + 0x31 */
	volatile uint8_t		res27;		/* + 0x32 */
	volatile uint8_t		res28;		/* + 0x33 */
	volatile uint8_t		idar6;		/* + 0x34 */
	volatile uint8_t		idar7;		/* + 0x35 */
	volatile uint8_t		res29;		/* + 0x36 */
	volatile uint8_t		res30;		/* + 0x37 */
	volatile uint8_t		idmr4;		/* + 0x38 */
	volatile uint8_t		idmr5;		/* + 0x39 */
	volatile uint8_t		res31;		/* + 0x3A */
	volatile uint8_t		res32;		/* + 0x3B */
	volatile uint8_t		idmr6;		/* + 0x3C */
	volatile uint8_t		idmr7;		/* + 0x3D */
	volatile uint8_t		res33;		/* + 0x3E */
	volatile uint8_t		res34;		/* + 0x3F */
	volatile uint8_t		rxidr0;	    /* + 0x40 */
	volatile uint8_t		rxidr1;	    /* + 0x41 */
	volatile uint8_t		res35;		/* + 0x42 */
	volatile uint8_t		res36;		/* + 0x43 */
	volatile uint8_t		rxidr2;	    /* + 0x44 */
	volatile uint8_t		rxidr3;	    /* + 0x45 */
	volatile uint8_t		res37;		/* + 0x46 */
	volatile uint8_t		res38;		/* + 0x47 */
	volatile uint8_t		rxdsr0;	    /* + 0x48 */
	volatile uint8_t		rxdsr1;	    /* + 0x49 */
	volatile uint8_t		res39;		/* + 0x4A */
	volatile uint8_t		res40;		/* + 0x4B */
	volatile uint8_t		rxdsr2;	    /* + 0x4C */
	volatile uint8_t		rxdsr3;	    /* + 0x4D */
	volatile uint8_t		res41;		/* + 0x4E */
	volatile uint8_t		res42;		/* + 0x4F */
	volatile uint8_t		rxdsr4;	    /* + 0x50 */
	volatile uint8_t		rxdsr5;	    /* + 0x51 */
	volatile uint8_t		res43;		/* + 0x52 */
	volatile uint8_t		res44;		/* + 0x53 */
	volatile uint8_t		rxdsr6;	    /* + 0x54 */
	volatile uint8_t		rxdsr7;	    /* + 0x55 */
	volatile uint8_t		res45;		/* + 0x56 */
	volatile uint8_t		res46;		/* + 0x57 */
	volatile uint8_t		rxdlr;		/* + 0x58 */
	volatile uint8_t		res47;		/* + 0x59 */
	volatile uint8_t		res48;		/* + 0x5A */
	volatile uint8_t		res49;		/* + 0x5B */
	volatile uint8_t		rxtimh;	    /* + 0x5C */
	volatile uint8_t		rxtiml;	    /* + 0x5D */
	volatile uint8_t		res50;		/* + 0x5E */
	volatile uint8_t		res51;		/* + 0x5F */
	volatile uint8_t		txidr0;	    /* + 0x60 */
	volatile uint8_t		txidr1;	    /* + 0x61 */
	volatile uint8_t		res52;		/* + 0x62 */
	volatile uint8_t		res53;		/* + 0x63 */
	volatile uint8_t		txidr2;	    /* + 0x64 */
	volatile uint8_t		txidr3;	    /* + 0x65 */
	volatile uint8_t		res54;		/* + 0x66 */
	volatile uint8_t		res55;		/* + 0x67 */
	volatile uint8_t		txdsr0;	    /* + 0x68 */
	volatile uint8_t		txdsr1;	    /* + 0x69 */
	volatile uint8_t		res56;		/* + 0x6A */
	volatile uint8_t		res57;		/* + 0x6B */
	volatile uint8_t		txdsr2;	    /* + 0x6C */
	volatile uint8_t		txdsr3;	    /* + 0x6D */
	volatile uint8_t		res58;		/* + 0x6E */
	volatile uint8_t		res59;		/* + 0x6F */
	volatile uint8_t		txdsr4;	    /* + 0x70 */
	volatile uint8_t		txdsr5;	    /* + 0x71 */
	volatile uint8_t		res60;		/* + 0x72 */
	volatile uint8_t		res61;		/* + 0x73 */
	volatile uint8_t		txdsr6;	    /* + 0x74 */
	volatile uint8_t		txdsr7;	    /* + 0x75 */
	volatile uint8_t		res62;		/* + 0x76 */
	volatile uint8_t		res63;		/* + 0x77 */
	volatile uint8_t		txdlr;		/* + 0x78 */
	volatile uint8_t		txtbpr;	    /* + 0x79 */
	volatile uint8_t		res64;		/* + 0x7A */
	volatile uint8_t		res65;		/* + 0x7B */
	volatile uint8_t		txtimh;	    /* + 0x7C */
	volatile uint8_t		txtiml;	    /* + 0x7D */
	volatile uint8_t		res66;		/* + 0x7E */
	volatile uint8_t		res67;		/* + 0x7F */
    } mscan[MPC5200_CAN_NO];

	volatile uint8_t		res[0x100];

	/*
	 * GPIO standard registers (MBAR + 0xB00)
	 */
    volatile uint32_t gpiopcr;	    /* + 0x00 */
    volatile uint32_t gpiosen;	    /* + 0x04 */
    volatile uint32_t gpiosod;	    /* + 0x08 */
    volatile uint32_t gpiosdd;	    /* + 0x0C */
    volatile uint32_t gpiosdo;	    /* + 0x10 */
    volatile uint32_t gpiosdi;	    /* + 0x14 */
    volatile uint32_t gpiooe;	    /* + 0x18 */
    volatile uint32_t gpioodo;	    /* + 0x1C */
    volatile uint32_t gpiosie;	    /* + 0x20 */
    volatile uint32_t gpiosiod;	    /* + 0x24 */
    volatile uint32_t gpiosidd;	    /* + 0x28 */
    volatile uint32_t gpiosido;	    /* + 0x2C */
    volatile uint32_t gpiosiie;	    /* + 0x30 */
    volatile uint32_t gpiosiit;	    /* + 0x34 */
    volatile uint32_t gpiosime;	    /* + 0x38 */
    volatile uint32_t gpiosist;	    /* + 0x3C */
    volatile uint8_t  res4[0xC0];

	/*
	 * GPIO wakeup registers (MBAR + 0xC00)
	 */
	volatile uint32_t gpiowe;	    /* + 0x00 */
	volatile uint32_t gpiowod;	    /* + 0x04 */
	volatile uint32_t gpiowdd;	    /* + 0x08 */
	volatile uint32_t gpiowdo;	    /* + 0x0C */
	volatile uint32_t gpiowue;	    /* + 0x10 */
	volatile uint32_t gpiowsie;	    /* + 0x14 */
	volatile uint32_t gpiowt;	    /* + 0x18 */
	volatile uint32_t gpiowme;	    /* + 0x1C */
	volatile uint32_t gpiowi;	    /* + 0x20 */
	volatile uint32_t gpiows;	    /* + 0x24 */
	volatile uint8_t  gpiow_res[0xD8];

	/*
	 * PPC PCI registers (MBAR + 0xD00)
	 */
	volatile uint8_t		ppci[0x100];

	/*
	 * consumer infrared registers (MBAR + 0xE00)
	 */
	volatile uint8_t		ir[0x100];

	/*
	 * serial peripheral interface registers (MBAR + 0xF00)
	 */
	volatile uint8_t		spi[0x100];

	/*
	 * universal serial bus registers (MBAR + 0x1000)
	 */
	volatile uint8_t		usb[0x200];

	/*
	 * SmartComm DMA registers (MBAR + 0x1200)
	 */
	volatile uint32_t taskBar;			/* + 0x00 sdTpb */
	volatile uint32_t currentPointer;	/* + 0x04 sdMdeComplex */
	volatile uint32_t endPointer;		/* + 0x08 sdMdeComplex */
	volatile uint32_t variablePointer;	/* + 0x0c sdMdeComplex */

	/*
	 * The following are Priority Task Decoder (ptd) regs in sdma/rtl_v/sdPtd.v.
	 * The ptd register map below is from the smartcomm spec, table 3-2, page 3-54.
	 * The spec shows the ptd map as 20 words, but sdPtd.v has only implemented 19.
	 * The word commented out below is the one which is not implemented.
	 */

	/*  volatile uint8_t  IntVect; */ /*
	 * + 0xXX sdPtd read only
	 */

	/*  volatile uint8_t  res0[3]; */ /*
	 * + 0xXX sdPtd read only
	 */
	volatile uint8_t IntVect1;	    /* + 0x10 sdPtd */
	volatile uint8_t IntVect2;	    /* + 0x11 sdPtd */
	volatile uint16_t PtdCntrl;	    /* + 0x12 sdPtd */

	volatile uint32_t IntPend;	    /* + 0x14 sdPtd */
	volatile uint32_t IntMask;	    /* + 0x18 sdPtd */

	volatile uint32_t TCR01;		    /* + 0x1c sdPtd */
	volatile uint32_t TCR23;		    /* + 0x20 sdPtd */
	volatile uint32_t TCR45;		    /* + 0x24 sdPtd */
	volatile uint32_t TCR67;		    /* + 0x28 sdPtd */
	volatile uint32_t TCR89;		    /* + 0x2c sdPtd */
	volatile uint32_t TCRAB;		    /* + 0x30 sdPtd */
	volatile uint32_t TCRCD;		    /* + 0x34 sdPtd */
	volatile uint32_t TCREF;		    /* + 0x38 sdPtd */

	volatile uint8_t IPR0;		    /* + 0x3c sdPtd */
	volatile uint8_t IPR1;		    /* + 0x3d sdPtd */
	volatile uint8_t IPR2;		    /* + 0x3e sdPtd */
	volatile uint8_t IPR3;		    /* + 0x3f sdPtd */
	volatile uint8_t IPR4;		    /* + 0x40 sdPtd */
	volatile uint8_t IPR5;		    /* + 0x41 sdPtd */
	volatile uint8_t IPR6;		    /* + 0x42 sdPtd */
	volatile uint8_t IPR7;		    /* + 0x43 sdPtd */
	volatile uint8_t IPR8;		    /* + 0x44 sdPtd */
	volatile uint8_t IPR9;		    /* + 0x45 sdPtd */
	volatile uint8_t IPR10;		    /* + 0x46 sdPtd */
	volatile uint8_t IPR11;		    /* + 0x47 sdPtd */
	volatile uint8_t IPR12;		    /* + 0x48 sdPtd */
	volatile uint8_t IPR13;		    /* + 0x49 sdPtd */
	volatile uint8_t IPR14;		    /* + 0x4a sdPtd */
	volatile uint8_t IPR15;		    /* + 0x4b sdPtd */
	volatile uint8_t IPR16;		    /* + 0x4c sdPtd */
	volatile uint8_t IPR17;		    /* + 0x4d sdPtd */
	volatile uint8_t IPR18;		    /* + 0x4e sdPtd */
	volatile uint8_t IPR19;		    /* + 0x4f sdPtd */
	volatile uint8_t IPR20;		    /* + 0x50 sdPtd */
	volatile uint8_t IPR21;		    /* + 0x51 sdPtd */
	volatile uint8_t IPR22;		    /* + 0x52 sdPtd */
	volatile uint8_t IPR23;		    /* + 0x53 sdPtd */
	volatile uint8_t IPR24;		    /* + 0x54 sdPtd */
	volatile uint8_t IPR25;		    /* + 0x55 sdPtd */
	volatile uint8_t IPR26;		    /* + 0x56 sdPtd */
	volatile uint8_t IPR27;		    /* + 0x57 sdPtd */
	volatile uint8_t IPR28;		    /* + 0x58 sdPtd */
	volatile uint8_t IPR29;		    /* + 0x59 sdPtd */
	volatile uint8_t IPR30;		    /* + 0x5a sdPtd */
	volatile uint8_t IPR31;		    /* + 0x5b sdPtd */

	volatile uint32_t res5;		    /* reserved */
	volatile uint32_t res6;		    /* reserved */
	volatile uint32_t res7;		    /* reserved */
	volatile uint32_t MDEDebug;	    /* + 0x68 sdMdeComplex */
	volatile uint32_t ADSDebug;	    /* + 0x6c sdAdsTop */
	volatile uint32_t Value1;	    /* + 0x70 sdDbg */
	volatile uint32_t Value2;	    /* + 0x74 sdDbg */
	volatile uint32_t Control;	    /* + 0x78 sdDbg */
	volatile uint32_t Status;	    /* + 0x7c sdDbg */
	volatile uint32_t EU00;		    /* + 0x80 sdMac macer reg */
	volatile uint32_t EU01;		    /* + 0x84 sdMac macemr reg */
	volatile uint32_t EU02;		    /* + 0x88 unused */
	volatile uint32_t EU03;		    /* + 0x8c unused */
	volatile uint32_t EU04;		    /* + 0x90 unused */
	volatile uint32_t EU05;		    /* + 0x94 unused */
	volatile uint32_t EU06;		    /* + 0x98 unused */
	volatile uint32_t EU07;		    /* + 0x9c unused */
	volatile uint32_t EU10;		    /* + 0xa0 unused */
	volatile uint32_t EU11;		    /* + 0xa4 unused */
	volatile uint32_t EU12;		    /* + 0xa8 unused */
	volatile uint32_t EU13;		    /* + 0xac unused */
	volatile uint32_t EU14;		    /* + 0xb0 unused */
	volatile uint32_t EU15;		    /* + 0xb4 unused */
	volatile uint32_t EU16;		    /* + 0xb8 unused */
	volatile uint32_t EU17;		    /* + 0xbc unused */
	volatile uint32_t EU20;		    /* + 0xc0 unused */
	volatile uint32_t EU21;		    /* + 0xc4 unused */
	volatile uint32_t EU22;		    /* + 0xc8 unused */
	volatile uint32_t EU23;		    /* + 0xcc unused */
	volatile uint32_t EU24;		    /* + 0xd0 unused */
	volatile uint32_t EU25;		    /* + 0xd4 unused */
	volatile uint32_t EU26;		    /* + 0xd8 unused */
	volatile uint32_t EU27;		    /* + 0xdc unused */
	volatile uint32_t EU30;		    /* + 0xe0 unused */
	volatile uint32_t EU31;		    /* + 0xe4 unused */
	volatile uint32_t EU32;		    /* + 0xe8 unused */
	volatile uint32_t EU33;		    /* + 0xec unused */
	volatile uint32_t EU34;		    /* + 0xf0 unused */
	volatile uint32_t EU35;		    /* + 0xf4 unused */
	volatile uint32_t EU36;		    /* + 0xf8 unused */
	volatile uint32_t EU37;		    /* + 0xfc unused */
#if 0
	volatile uint32_t res8[0x340];
#else
	volatile uint8_t res_1300[0xc00];

	volatile uint32_t reserved0;			/* MBAR_XLB_ARB + 0x0000 reserved */
	volatile uint32_t reserved1;			/* MBAR_XLB_ARB + 0x0004 reserved */
	volatile uint32_t reserved2;			/* MBAR_XLB_ARB + 0x0008 reserved */
	volatile uint32_t reserved3;			/* MBAR_XLB_ARB + 0x000c reserved */
	volatile uint32_t reserved4;			/* MBAR_XLB_ARB + 0x0010 reserved */
	volatile uint32_t reserved5;			/* MBAR_XLB_ARB + 0x0014 reserved */
	volatile uint32_t reserved6;			/* MBAR_XLB_ARB + 0x0018 reserved */
	volatile uint32_t reserved7;			/* MBAR_XLB_ARB + 0x001c reserved */
	volatile uint32_t reserved8;			/* MBAR_XLB_ARB + 0x0020 reserved */
	volatile uint32_t reserved9;			/* MBAR_XLB_ARB + 0x0024 reserved */
	volatile uint32_t reserved10;			/* MBAR_XLB_ARB + 0x0028 reserved */
	volatile uint32_t reserved11;			/* MBAR_XLB_ARB + 0x002c reserved */
	volatile uint32_t reserved12;			/* MBAR_XLB_ARB + 0x0030 reserved */
	volatile uint32_t reserved13;			/* MBAR_XLB_ARB + 0x0034 reserved */
	volatile uint32_t reserved14;			/* MBAR_XLB_ARB + 0x0038 reserved */
	volatile uint32_t reserved15;			/* MBAR_XLB_ARB + 0x003c reserved */

	volatile uint32_t config;				/* MBAR_XLB_ARB + 0x0040 */
	volatile uint32_t version;			/* MBAR_XLB_ARB + 0x0044 read only = 0x0001 */
	volatile uint32_t xlb_status;			/* MBAR_XLB_ARB + 0x0048 */
	volatile uint32_t int_enable;			/* MBAR_XLB_ARB + 0x004c */
	volatile uint32_t add_capture;		/* MBAR_XLB_ARB + 0x0050 read only */
	volatile uint32_t bus_sig_capture;	/* MBAR_XLB_ARB + 0x0054 read only */
	volatile uint32_t add_time_out;		/* MBAR_XLB_ARB + 0x0058 */
	volatile uint32_t data_time_out;		/* MBAR_XLB_ARB + 0x005c */
	volatile uint32_t bus_time_out;		/* MBAR_XLB_ARB + 0x0060 */
	volatile uint32_t priority_enable;	/* MBAR_XLB_ARB + 0x0064 */
	volatile uint32_t priority;			/* MBAR_XLB_ARB + 0x0068 */
	volatile uint32_t arb_base_addr2;		/* MBAR_XLB_ARB + 0x006c */
	volatile uint32_t snoop_window;		/* MBAR_XLB_ARB + 0x0070 */

	volatile uint32_t reserved16;			/* MBAR_XLB_ARB + 0x0074 reserved */
	volatile uint32_t reserved17;			/* MBAR_XLB_ARB + 0x0078 reserved */
	volatile uint32_t reserved18;			/* MBAR_XLB_ARB + 0x007c reserved */

	volatile uint32_t control;			/* MBAR_XLB_ARB + 0x0080 */
	volatile uint32_t init_total_count;	/* MBAR_XLB_ARB + 0x0084 */
	volatile uint32_t int_total_count;	/* MBAR_XLB_ARB + 0x0088 */

	volatile uint32_t reserved19;			/* MBAR_XLB_ARB + 0x008c reserved */

	volatile uint32_t lower_address;		/* MBAR_XLB_ARB + 0x0090 */
	volatile uint32_t higher_address;		/* MBAR_XLB_ARB + 0x0094 */
	volatile uint32_t int_window_count;	/* MBAR_XLB_ARB + 0x0098 */
	volatile uint32_t window_ter_count;	/* MBAR_XLB_ARB + 0x009c */
	  volatile uint8_t  res_0x1fa0[0x60];


#endif
    /*
     * programmable serial controller 1 (MBAR + 0x2000)
     */

  struct mpc5200_psc
    {
    volatile uint8_t  mr;            /* +0x00 */
    volatile uint8_t  res1[3];
    volatile uint16_t sr_csr;        /* +0x04 */
    volatile uint16_t res2[1];
    volatile uint16_t cr;            /* +0x08 */
    volatile uint16_t res3[1];
    volatile uint32_t rb_tb;         /* +0x0c */
    volatile uint16_t ipcr_acr;      /* +0x10 */
    volatile uint16_t res4[1];
    volatile uint16_t isr_imr;       /* +0x14 */
#define ISR_TX_RDY      (1 << 8)
#define ISR_RX_RDY_FULL (1 << 9)
#define ISR_RB			(1 << 15)
#define ISR_FE          (1 << 14)
#define ISR_PE          (1 << 13)
#define ISR_OE          (1 << 12)
#define ISR_ERROR       (ISR_FE | ISR_PE | ISR_OE)

#define IMR_TX_RDY      (1 << 8)
#define IMR_RX_RDY_FULL (1 << 9)
    volatile uint16_t res5[1];
    volatile uint8_t  ctur;          /* +0x18 */
    volatile uint8_t  res6[3];
    volatile uint8_t  ctlr;          /* +0x1C */
    volatile uint8_t  res7[0x13];
    volatile uint8_t  ivr;           /* +0x30 */
    volatile uint8_t  res8[3];
    volatile uint8_t  ip;            /* +0x34 */
    volatile uint8_t  res9[3];
    volatile uint8_t  op1;           /* +0x38 */
    volatile uint8_t  res10[3];
    volatile uint8_t  op0;           /* +0x3C */
    volatile uint8_t  res11[3];
    volatile uint8_t  sicr;          /* +0x40 */
    volatile uint8_t  res12[0x17];
    volatile uint16_t rfnum;         /* +0x58 */
    volatile uint16_t res13[1];
    volatile uint16_t tfnum;         /* +0x5C */
	volatile uint16_t res14[1];
    volatile uint16_t rfdata;        /* +0x60 */
    volatile uint16_t res15[1];
    volatile uint16_t rfstat;        /* +0x64 */
    volatile uint16_t res16[1];
    volatile uint8_t  rfcntl;        /* +0x68 */
    volatile uint8_t  res17[5];
    volatile uint16_t rfalarm;       /* +0x6E */
    volatile uint8_t  res18[2];
    volatile uint16_t rfrptr;        /* +0x72 */
	volatile uint16_t res19[1];
	volatile uint16_t rfwptr;        /* +0x76 */
	volatile uint16_t res20[1];
	volatile uint16_t rflrfptr;      /* +0x7A */
	volatile uint16_t rflwfptr;      /* +0x7C */
	volatile uint16_t res21[1];
	volatile uint16_t tfdata;        /* +0x80 */
	volatile uint16_t res22[1];
    volatile uint16_t tfstat;        /* +0x84 */
	volatile uint16_t res23[1];
	volatile uint8_t  tfcntl;        /* +0x88 */
	volatile uint8_t  res24[5];
	volatile uint16_t tfalarm;       /* +0x8E */
	volatile uint8_t  res25[2];
	volatile uint16_t tfrptr;        /* +0x92 */
	volatile uint16_t res26[1];
	volatile uint16_t tfwptr;        /* +0x96 */
	volatile uint16_t res27[1];
	volatile uint16_t tflrfptr;      /* +0x96 */
	volatile uint16_t tflwfptr;      /* +0x9C */
	volatile uint16_t res28[1];      /* end at offset 0x9F */
    volatile uint8_t  res29[0x160];
    } psc[MPC5200_PSC_REG_SETS];
  /* XXX: there are only 6 PSCs, but PSC6 has an extra register gap
   *      from PSC5, therefore we instantiate seven(!) PSC register sets
   */

#define TX_FIFO_SIZE    256
#define RX_FIFO_SIZE    512


	volatile uint8_t	 irda[0x200];

	/*
	 * ethernet registers (MBAR + 0x3000)
	 */

	/*  Control and status Registers (offset 000-1FF) */

	volatile uint32_t fec_id;			/* + 0x000 */
	volatile uint32_t ievent;			/* + 0x004 */
	volatile uint32_t imask;				/* + 0x008 */

	volatile uint32_t res9[1];			/* + 0x00C */
	volatile uint32_t r_des_active;		/* + 0x010 */
	volatile uint32_t x_des_active;		/* + 0x014 */
	volatile uint32_t r_des_active_cl;	/* + 0x018 */
	volatile uint32_t x_des_active_cl;	/* + 0x01C */
	volatile uint32_t ivent_set;			/* + 0x020 */
	volatile uint32_t ecntrl;			/* + 0x024 */

	volatile uint32_t res10[6];			/* + 0x028-03C */
	volatile uint32_t mii_data;			/* + 0x040 */
	volatile uint32_t mii_speed;			/* + 0x044 */
	volatile uint32_t mii_status;		/* + 0x048 */

	volatile uint32_t res11[5];			/* + 0x04C-05C */
	volatile uint32_t mib_data;			/* + 0x060 */
	volatile uint32_t mib_control;		/* + 0x064 */

	volatile uint32_t res12[6];			/* + 0x068-7C */
	volatile uint32_t r_activate;		/* + 0x080 */
	volatile uint32_t r_cntrl;			/* + 0x084 */
	volatile uint32_t r_hash;			/* + 0x088 */
	volatile uint32_t r_data;			/* + 0x08C */
	volatile uint32_t ar_done;			/* + 0x090 */
	volatile uint32_t r_test;			/* + 0x094 */
	volatile uint32_t r_mib;				/* + 0x098 */
	volatile uint32_t r_da_low;			/* + 0x09C */
	volatile uint32_t r_da_high;			/* + 0x0A0 */

	volatile uint32_t res13[7];			/* + 0x0A4-0BC */
	volatile uint32_t x_activate;		/* + 0x0C0 */
	volatile uint32_t x_cntrl;			/* + 0x0C4 */
	volatile uint32_t backoff;			/* + 0x0C8 */
	volatile uint32_t x_data;			/* + 0x0CC */
	volatile uint32_t x_status;			/* + 0x0D0 */
	volatile uint32_t x_mib;				/* + 0x0D4 */
	volatile uint32_t x_test;			/* + 0x0D8 */
	volatile uint32_t fdxfc_da1;			/* + 0x0DC */
	volatile uint32_t fdxfc_da2;			/* + 0x0E0 */
	volatile uint32_t paddr1;			/* + 0x0E4 */
	volatile uint32_t paddr2;			/* + 0x0E8 */
	volatile uint32_t op_pause;			/* + 0x0EC */

	volatile uint32_t res14[4];			/* + 0x0F0-0FC */
	volatile uint32_t instr_reg;			/* + 0x100 */
	volatile uint32_t context_reg;		/* + 0x104 */
	volatile uint32_t test_cntrl;		/* + 0x108 */
	volatile uint32_t acc_reg;			/* + 0x10C */
	volatile uint32_t ones;				/* + 0x110 */
	volatile uint32_t zeros;				/* + 0x114 */
	volatile uint32_t iaddr1;			/* + 0x118 */
	volatile uint32_t iaddr2;			/* + 0x11C */
	volatile uint32_t gaddr1;			/* + 0x120 */
	volatile uint32_t gaddr2;			/* + 0x124 */
	volatile uint32_t random;			/* + 0x128 */
	volatile uint32_t rand1;				/* + 0x12C */
	volatile uint32_t tmp;				/* + 0x130 */

	volatile uint32_t res15[3];			/* + 0x134-13C */
	volatile uint32_t fifo_id;			/* + 0x140 */
	volatile uint32_t x_wmrk;			/* + 0x144 */
	volatile uint32_t fcntrl;			/* + 0x148 */
	volatile uint32_t r_bound;			/* + 0x14C */
	volatile uint32_t r_fstart;			/* + 0x150 */
	volatile uint32_t r_count;			/* + 0x154 */
	volatile uint32_t r_lag;				/* + 0x158 */
	volatile uint32_t r_read;			/* + 0x15C */
	volatile uint32_t r_write;			/* + 0x160 */
	volatile uint32_t x_count;			/* + 0x164 */
	volatile uint32_t x_lag;				/* + 0x168 */
	volatile uint32_t x_retry;			/* + 0x16C */
	volatile uint32_t x_write;			/* + 0x170 */
	volatile uint32_t x_read;			/* + 0x174 */

	volatile uint32_t res16[2];			/* + 0x178-17C */
	volatile uint32_t fm_cntrl;			/* + 0x180 */
	volatile uint32_t rfifo_data;		/* + 0x184 */
	volatile uint32_t rfifo_status;		/* + 0x188 */
	volatile uint32_t rfifo_cntrl;		/* + 0x18C */
	volatile uint32_t rfifo_lrf_ptr;		/* + 0x190 */
	volatile uint32_t rfifo_lwf_ptr;		/* + 0x194 */
	volatile uint32_t rfifo_alarm;		/* + 0x198 */
	volatile uint32_t rfifo_rdptr;		/* + 0x19C */
	volatile uint32_t rfifo_wrptr;		/* + 0x1A0 */
	volatile uint32_t tfifo_data;		/* + 0x1A4 */
	volatile uint32_t tfifo_status;		/* + 0x1A8 */
	volatile uint32_t tfifo_cntrl;		/* + 0x1AC */
	volatile uint32_t tfifo_lrf_ptr;		/* + 0x1B0 */
	volatile uint32_t tfifo_lwf_ptr;		/* + 0x1B4 */
	volatile uint32_t tfifo_alarm;		/* + 0x1B8 */
	volatile uint32_t tfifo_rdptr;		/* + 0x1BC */
	volatile uint32_t tfifo_wrptr;		/* + 0x1C0 */

	volatile uint32_t reset_cntrl;		/* + 0x1C4 */
	volatile uint32_t xmit_fsm;			/* + 0x1C8 */

	volatile uint32_t res17[3];			/* + 0x1CC-1D4 */
	volatile uint32_t rdes_data0;		/* + 0x1D8 */
	volatile uint32_t rdes_data1;		/* + 0x1DC */
	volatile uint32_t r_length;			/* + 0x1E0 */
	volatile uint32_t x_length;			/* + 0x1E4 */
	volatile uint32_t x_addr;			/* + 0x1E8 */
	volatile uint32_t cdes_data;			/* + 0x1EC */
	volatile uint32_t status;			/* + 0x1F0 */
	volatile uint32_t dma_control;		/* + 0x1F4 */
	volatile uint32_t des_cmnd;			/* + 0x1F8 */
	volatile uint32_t data;				/* + 0x1FC */

	volatile uint8_t  RES[0x600];


#if 0
	/* MIB COUNTERS (Offset 200-2FF) */

	volatile uint32_t rmon_t_drop;		/* + 0x200 */
	volatile uint32_t rmon_t_packets;	/* + 0x204 */
	volatile uint32_t rmon_t_bc_pkt;		/* + 0x208 */
	volatile uint32_t rmon_t_mc_pkt;		/* + 0x20C */
	volatile uint32_t rmon_t_crc_align;	/* + 0x210 */
	volatile uint32_t rmon_t_undersize;	/* + 0x214 */
	volatile uint32_t rmon_t_oversize;	/* + 0x218 */
	volatile uint32_t rmon_t_frag;		/* + 0x21C */
	volatile uint32_t rmon_t_jab;		/* + 0x220 */
	volatile uint32_t rmon_t_col;		/* + 0x224 */
	volatile uint32_t rmon_t_p64;		/* + 0x228 */
	volatile uint32_t rmon_t_p65to127;	/* + 0x22C */
	volatile uint32_t rmon_t_p128to255;	/* + 0x230 */
	volatile uint32_t rmon_t_p256to511;	/* + 0x234 */
	volatile uint32_t rmon_t_p512to1023;	/* + 0x238 */
	volatile uint32_t rmon_t_p1024to2047;/* + 0x23C */
	volatile uint32_t rmon_t_p_gte2048;	/* + 0x240 */
	volatile uint32_t rmon_t_octets;		/* + 0x244 */
	volatile uint32_t ieee_t_drop;		/* + 0x248 */
	volatile uint32_t ieee_t_frame_ok;	/* + 0x24C */
	volatile uint32_t ieee_t_1col;		/* + 0x250 */
	volatile uint32_t ieee_t_mcol;		/* + 0x254 */
	volatile uint32_t ieee_t_def;		/* + 0x258 */
	volatile uint32_t ieee_t_lcol;		/* + 0x25C */
	volatile uint32_t ieee_t_excol;		/* + 0x260 */
	volatile uint32_t ieee_t_macerr;		/* + 0x264 */
	volatile uint32_t ieee_t_cserr;		/* + 0x268 */
	volatile uint32_t ieee_t_sqe;		/* + 0x26C */
	volatile uint32_t t_fdxfc;			/* + 0x270 */
	volatile uint32_t ieee_t_octets_ok;	/* + 0x274 */

	volatile uint32_t res18[2];			/* + 0x278-27C */
	volatile uint32_t rmon_r_drop;		/* + 0x280 */
	volatile uint32_t rmon_r_packets;	/* + 0x284 */
	volatile uint32_t rmon_r_bc_pkt;		/* + 0x288 */
	volatile uint32_t rmon_r_mc_pkt;		/* + 0x28C */
	volatile uint32_t rmon_r_crc_align;	/* + 0x290 */
	volatile uint32_t rmon_r_undersize;	/* + 0x294 */
	volatile uint32_t rmon_r_oversize;	/* + 0x298 */
	volatile uint32_t rmon_r_frag;		/* + 0x29C */
	volatile uint32_t rmon_r_jab;		/* + 0x2A0 */

	volatile uint32_t rmon_r_resvd_0;	/* + 0x2A4 */

	volatile uint32_t rmon_r_p64;		/* + 0x2A8 */
	volatile uint32_t rmon_r_p65to127;	/* + 0x2AC */
	volatile uint32_t rmon_r_p128to255;	/* + 0x2B0 */
	volatile uint32_t rmon_r_p256to511;	/* + 0x2B4 */
	volatile uint32_t rmon_r_p512to1023;	/* + 0x2B8 */
	volatile uint32_t rmon_r_p1024to2047;/* + 0x2BC */
	volatile uint32_t rmon_r_p_gte2048;	/* + 0x2C0 */
	volatile uint32_t rmon_r_octets;		/* + 0x2C4 */
	volatile uint32_t ieee_r_drop;		/* + 0x2C8 */
	volatile uint32_t ieee_r_frame_ok;	/* + 0x2CC */
	volatile uint32_t ieee_r_crc;		/* + 0x2D0 */
	volatile uint32_t ieee_r_align;		/* + 0x2D4 */
	volatile uint32_t r_macerr;			/* + 0x2D8 */
	volatile uint32_t r_fdxfc;			/* + 0x2DC */
	volatile uint32_t ieee_r_octets_ok;	/* + 0x2E0 */

	volatile uint32_t res19[6];			/* + 0x2E4-2FC */

	volatile uint32_t res20[64];			/* + 0x300-3FF */

	volatile uint32_t res21[256];        /* + 0x400-800 */
#endif

	/*
	 * SmartComm DMA PCI registers (MBAR + 0x3800)
	 */
	volatile uint8_t		pci[0x200];

	/*
	 * advanced technology attachment registers (MBAR + 0x3A00)
	 */

	/* ATA host registers (offset 0x00-0x28) */
	volatile uint32_t	ata_hcfg;		/* + 0x00 */
	volatile uint32_t	ata_hsr;		/* + 0x04 */
	volatile uint32_t	ata_pio1;		/* + 0x08 */
	volatile uint32_t	ata_pio2;		/* + 0x0C */
	volatile uint32_t	ata_dma1;		/* + 0x10 */
	volatile uint32_t	ata_dma2;		/* + 0x14 */
	volatile uint32_t	ata_udma1;		/* + 0x18 */
	volatile uint32_t	ata_udma2;		/* + 0x1C */
	volatile uint32_t	ata_udma3;		/* + 0x20 */
	volatile uint32_t	ata_udma4;		/* + 0x24 */
	volatile uint32_t	ata_udma5;		/* + 0x28 */
	volatile uint32_t	ata_res1[4];	/* + 0x2C-0x3C */

	/* ATA FIFO registers (offset 0x3C-0x50) */
	volatile uint32_t	ata_rtfdwr;		/* + 0x3C */
	volatile uint32_t	ata_rtfsr;		/* + 0x40 */
	volatile uint32_t	ata_rtfcr;		/* + 0x44 */
	volatile uint32_t	ata_rtfar;		/* + 0x48 */
	volatile uint32_t	ata_rtfrpr;		/* + 0x4C */
	volatile uint32_t	ata_rtfwpr;		/* + 0x50 */
	volatile uint32_t	ata_res2[2];	/* + 0x54-0x5C */

    /* ATA drive registers (offset 0x5C-0x80) */
	  volatile uint32_t	ata_dctr_dasr;	/* + 0x5C */
	  volatile uint32_t	ata_ddr;		/* + 0x60 */
	  volatile uint32_t	ata_dfr_der;	/* + 0x64 */
	  volatile uint32_t	ata_dscr;		/* + 0x68 */
	  volatile uint32_t	ata_dsnr;		/* + 0x6C */
	  volatile uint32_t	ata_dclr;		/* + 0x70 */
	  volatile uint32_t	ata_dchr;		/* + 0x74 */
	  volatile uint32_t	ata_ddhr;		/* + 0x78 */
	  volatile uint32_t	ata_dcr_dsr;    /* + 0x7C */
	  volatile uint32_t	ata_res3[0xA0]; /* + 0x80-0x200 */

	/*
	 * inter-integrated circuit registers (MBAR + 0x3D00)
	 */
	  struct mpc5200_i2c_regs_s {
	    volatile uint8_t  madr;   /* i2c address reg.       +0x00 */
	    volatile uint8_t  res_1[3];
	    volatile uint8_t  mfdr;   /* i2c freq. divider reg. +0x04 */
	    volatile uint8_t  res_5[3];
	    volatile uint8_t  mcr;    /* i2c control reg.       +0x08 */
	    volatile uint8_t  res_9[3];

#define MPC5200_I2C_MCR_MEN    (1 << (7-0))
#define MPC5200_I2C_MCR_MIEN   (1 << (7-1))
#define MPC5200_I2C_MCR_MSTA   (1 << (7-2))
#define MPC5200_I2C_MCR_MTX    (1 << (7-3))
#define MPC5200_I2C_MCR_TXAK   (1 << (7-4))
#define MPC5200_I2C_MCR_RSTA   (1 << (7-5))

	    volatile uint8_t  msr;    /* i2c status reg.        +0x0C */
	    volatile uint8_t  res_d[3];
#define MPC5200_I2C_MSR_CF    (1 << (7-0))
#define MPC5200_I2C_MSR_MAAS  (1 << (7-1))
#define MPC5200_I2C_MSR_BB    (1 << (7-2))
#define MPC5200_I2C_MSR_MAL   (1 << (7-3))
#define MPC5200_I2C_MSR_SRW   (1 << (7-5))
#define MPC5200_I2C_MSR_MIF   (1 << (7-6))
#define MPC5200_I2C_MSR_RXAK  (1 << (7-7))
	    volatile uint8_t  mdr;    /* i2c data I/O reg.      +0x10 */
	    volatile uint8_t  res_11[3];
	    volatile uint8_t  res_14[12];  /* reserved          +0x14 */
	    volatile uint8_t  icr;   /* i2c irq ctrl reg.      +0x20 */
#define MPC5200_I2C_ICR_BNBE2  (1 << (7-0))
#define MPC5200_I2C_ICR_TE2    (1 << (7-1))
#define MPC5200_I2C_ICR_RE2    (1 << (7-2))
#define MPC5200_I2C_ICR_IE2    (1 << (7-3))
#define MPC5200_I2C_ICR_MASK2  (MPC5200_I2C_ICR_BNBE2|MPC5200_I2C_ICR_TE2\
                               |MPC5200_I2C_ICR_RE2|MPC5200_I2C_ICR_IE2)
#define MPC5200_I2C_ICR_BNBE1  (1 << (7-4))
#define MPC5200_I2C_ICR_TE1    (1 << (7-5))
#define MPC5200_I2C_ICR_RE1    (1 << (7-6))
#define MPC5200_I2C_ICR_IE1    (1 << (7-7))
#define MPC5200_I2C_ICR_MASK1  (MPC5200_I2C_ICR_BNBE1|MPC5200_I2C_ICR_TE1\
                               |MPC5200_I2C_ICR_RE1|MPC5200_I2C_ICR_IE1)
	    volatile uint8_t  res_21[3];
	    volatile uint32_t res_24[7];   /* reserved          +0x24 */
	  } i2c_regs[2];
	  volatile uint8_t		res_3d80[0x280];

	/*
	 * on-chip static RAM memory locations (MBAR + 0x4000)
	 */
	volatile uint8_t		sram_res0x4000[0x4000];
	volatile uint8_t		sram[0x4000];

	} mpc5200_t;

extern volatile mpc5200_t mpc5200;

#ifdef __cplusplus
}
#endif

#endif  /*ASM*/

#endif /* __MPC5200_h__ */
