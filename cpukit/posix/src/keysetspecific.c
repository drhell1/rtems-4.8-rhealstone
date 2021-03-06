/*
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <string.h>

#include <rtems/system.h>
#include <rtems/score/thread.h>
#include <rtems/score/wkspace.h>
#include <rtems/posix/key.h>

/*PAGE
 *
 *  17.1.2 Thread-Specific Data Management, P1003.1c/Draft 10, p. 165
 */

int pthread_setspecific(
  pthread_key_t  key,
  const void    *value
)
{
  register POSIX_Keys_Control *the_key;
  uint32_t                     api;
  uint32_t                     index;
  Objects_Locations            location;

  the_key = _POSIX_Keys_Get( key, &location );
  switch ( location ) {
    case OBJECTS_ERROR:
    case OBJECTS_REMOTE:   /* should never happen */
      return EINVAL;
    case OBJECTS_LOCAL:
      api   = _Objects_Get_API( _Thread_Executing->Object.id );
      index = _Objects_Get_index( _Thread_Executing->Object.id );
      the_key->Values[ api ][ index ] = (void *) value;
      _Thread_Enable_dispatch();
      return 0;
  }
  return POSIX_BOTTOM_REACHED();
}
