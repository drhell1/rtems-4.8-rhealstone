/*
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <pthread.h>
#include <errno.h>

#include <rtems/system.h>
#include <rtems/score/object.h>
#include <rtems/score/states.h>
#include <rtems/score/watchdog.h>
#include <rtems/posix/cond.h>
#include <rtems/posix/time.h>
#include <rtems/posix/mutex.h>

/*PAGE
 *
 *  Barrier Initialization Attributes
 */

int pthread_barrierattr_destroy(
  pthread_barrierattr_t *attr
)
{
  if ( !attr || attr->is_initialized == FALSE )
    return EINVAL;

  attr->is_initialized = FALSE;
  return 0;
}
