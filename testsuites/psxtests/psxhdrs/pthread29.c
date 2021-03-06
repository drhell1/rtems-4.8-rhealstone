/*
 *  This test file is used to verify that the header files associated with
 *  invoking this function are correct.
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

#include <pthread.h>

#ifndef _POSIX_THREADS
#error "rtems is supposed to have pthread_setcancelstate"
#endif

void init_routine( void )
{
}

void test( void )
{
  int         state;
  int         oldstate;
  int         result;

  state = PTHREAD_CANCEL_ENABLE;
  state = PTHREAD_CANCEL_DISABLE;

  result = pthread_setcancelstate( state, &oldstate );
}
