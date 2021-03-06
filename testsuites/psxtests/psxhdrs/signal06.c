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

#include <signal.h>

void test( void )
{
  int              signal_number;
  struct sigaction act;
  struct sigaction oact;
  int              result;

  signal_number = SIGALRM;

  /*
   *  Really should not reference sa_handler and sa_signction simultaneously.
   */

  act.sa_handler = SIG_DFL;
  act.sa_handler = SIG_IGN;
  act.sa_mask  = 0;
  act.sa_flags = SA_NOCLDSTOP;
  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = NULL;

  result = sigaction( signal_number, &act, &oact );
}
