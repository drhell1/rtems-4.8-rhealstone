/*
 *  POSIX RWLock Manager -- Attempt to Obtain a Write Lock on a RWLock Instance
 *
 *  COPYRIGHT (c) 1989-2006.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <pthread.h>
#include <errno.h>

#include <rtems/system.h>
#include <rtems/posix/rwlock.h>
#include <rtems/posix/time.h>

/*
 *  pthread_rwlock_timedwrlock
 *
 *  This directive attempts to obtain a write only lock on an rwlock instance.
 *
 *  Input parameters:
 *    rwlock          - pointer to rwlock id
 *
 *  Output parameters:
 *    0          - if successful
 *    error code - if unsuccessful
 */

int pthread_rwlock_timedwrlock(
  pthread_rwlock_t      *rwlock,
  const struct timespec *abstime
)
{
  POSIX_RWLock_Control                        *the_rwlock;
  Objects_Locations                            location;
  Watchdog_Interval                            ticks;
  boolean                                      do_wait;
  POSIX_Absolute_timeout_conversion_results_t  status;
  
  if ( !rwlock )
    return EINVAL;

  /*
   *  POSIX requires that blocking calls with timeouts that take
   *  an absolute timeout must ignore issues with the absolute
   *  time provided if the operation would otherwise succeed.
   *  So we check the abstime provided, and hold on to whether it
   *  is valid or not.  If it isn't correct and in the future,
   *  then we do a polling operation and convert the UNSATISFIED
   *  status into the appropriate error.
   */
  status = _POSIX_Absolute_timeout_to_ticks( abstime, &ticks );
  switch (status) {
    case POSIX_ABSOLUTE_TIMEOUT_INVALID:
    case POSIX_ABSOLUTE_TIMEOUT_IS_IN_PAST:
    case POSIX_ABSOLUTE_TIMEOUT_IS_NOW:
      do_wait = FALSE;
      break;
    case POSIX_ABSOLUTE_TIMEOUT_IS_IN_FUTURE:
      do_wait = TRUE;
      break;
  }

  the_rwlock = _POSIX_RWLock_Get( rwlock, &location );
  switch ( location ) {

    case OBJECTS_REMOTE:
    case OBJECTS_ERROR:
      return EINVAL;

    case OBJECTS_LOCAL:

      _CORE_RWLock_Obtain_for_writing(
	&the_rwlock->RWLock,
	*rwlock,
	do_wait,
	ticks,
	NULL
      );

      _Thread_Enable_dispatch();
      if ( !do_wait &&
           (_Thread_Executing->Wait.return_code == CORE_RWLOCK_UNAVAILABLE) ) {
	switch (status) {
	  case POSIX_ABSOLUTE_TIMEOUT_INVALID:
	    return EINVAL;
	  case POSIX_ABSOLUTE_TIMEOUT_IS_IN_PAST:
	  case POSIX_ABSOLUTE_TIMEOUT_IS_NOW:
	    return ETIMEDOUT;
	  case POSIX_ABSOLUTE_TIMEOUT_IS_IN_FUTURE:
	    break;
	}
      }

      return _POSIX_RWLock_Translate_core_RWLock_return_code(
        (CORE_RWLock_Status) _Thread_Executing->Wait.return_code
      );
  }

  return POSIX_BOTTOM_REACHED();
}
