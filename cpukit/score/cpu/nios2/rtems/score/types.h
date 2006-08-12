/**
 * @file rtems/score/types.h
 */

/*
 *  This include file contains type definitions pertaining to the 
 *  Altera Nios II processor family.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_TYPES_H
#define _RTEMS_SCORE_TYPES_H

#ifndef ASM

#include <rtems/stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  This section defines the basic types for this processor.
 */

typedef unsigned long long unsigned64; /* unsigned 64-bit integer */

typedef uint16_t Priority_Bit_map_control;

typedef signed long long signed64;     /* 64 bit signed integer */

typedef uint32_t boolean;     /* Boolean value   */

typedef float          single_precision;     /* single precision float */
typedef double         double_precision;     /* double precision float */

typedef void nios2_isr;
typedef void ( *nios2_isr_entry )( void );

#ifdef __cplusplus
}
#endif

#endif  /* !ASM */

#endif