/*
 *  NOTE:  The structure of the routines is identical to that of POSIX
 *         Message_queues to leave the option of having unnamed message
 *         queues at a future date.  They are currently not part of the
 *         POSIX standard but unnamed message_queues are.  This is also
 *         the reason for the apparently unnecessary tracking of
 *         the process_shared attribute.  [In addition to the fact that
 *         it would be trivial to add pshared to the mq_attr structure
 *         and have process private message queues.]
 *
 *         This code ignores the O_RDONLY/O_WRONLY/O_RDWR flag at open
 *         time.
 *
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include <pthread.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>

#include <rtems/system.h>
#include <rtems/score/watchdog.h>
#include <rtems/score/wkspace.h>
#include <rtems/seterr.h>
#include <rtems/posix/mqueue.h>
#include <rtems/posix/time.h>

/* pure ANSI mode does not have this prototype */
size_t strnlen(const char *, size_t);

/*PAGE
 *
 *  _POSIX_Message_queue_Create_support
 *
 *  This routine does the actual creation and initialization of
 *  a poxix message queue.
 */

int _POSIX_Message_queue_Create_support(
  const char                    *name_arg,
  int                            pshared,
  struct mq_attr                *attr_ptr,
  POSIX_Message_queue_Control  **message_queue
)
{
  POSIX_Message_queue_Control   *the_mq;
  CORE_message_queue_Attributes *the_mq_attr;
  struct mq_attr                 attr;
  char                          *name;
  size_t                         n;

  n = strnlen( name_arg, NAME_MAX );
  if ( n > NAME_MAX )
    return ENAMETOOLONG;

  _Thread_Disable_dispatch();

  /*
   *  There is no real basis for the default values.  They will work
   *  but were not compared against any existing implementation for
   *  compatibility.  See README.mqueue for an example program we
   *  think will print out the defaults.  Report anything you find with it.
   */

  if ( attr_ptr == NULL ) {
    attr.mq_maxmsg  = 10;
    attr.mq_msgsize = 16;
  } else {
    if ( attr_ptr->mq_maxmsg <= 0 ){
      _Thread_Enable_dispatch();
      rtems_set_errno_and_return_minus_one( EINVAL );
    }

    if ( attr_ptr->mq_msgsize <= 0 ){
      _Thread_Enable_dispatch();
      rtems_set_errno_and_return_minus_one( EINVAL );
    }

    attr = *attr_ptr;
  }

#if 0 && defined(RTEMS_MULTIPROCESSING)
  if ( pshared == PTHREAD_PROCESS_SHARED &&
       !( _Objects_MP_Allocate_and_open( &_POSIX_Message_queue_Information, 0,
                            the_mq->Object.id, FALSE ) ) ) {
    _POSIX_Message_queue_Free( the_mq );
    _Thread_Enable_dispatch();
    rtems_set_errno_and_return_minus_one( ENFILE );
  }
#endif

  the_mq = _POSIX_Message_queue_Allocate();
  if ( !the_mq ) {
    _Thread_Enable_dispatch();
    rtems_set_errno_and_return_minus_one( ENFILE );
  }

  the_mq->process_shared  = pshared;
  the_mq->named = TRUE;
  the_mq->open_count = 1;
  the_mq->linked = TRUE;

  /*
   * Make a copy of the user's string for name just in case it was
   * dynamically constructed.
   */

  name = _Workspace_Allocate(n);
  if (!name) {
    _POSIX_Message_queue_Free( the_mq );
    _Thread_Enable_dispatch();
    rtems_set_errno_and_return_minus_one( ENOMEM );
  }
  strcpy( name, name_arg );

  /* XXX
   *
   *  Note that thread blocking discipline should be based on the
   *  current scheduling policy.
   */

  the_mq_attr = &the_mq->Message_queue.Attributes;
  the_mq_attr->discipline = CORE_MESSAGE_QUEUE_DISCIPLINES_FIFO;

  if ( ! _CORE_message_queue_Initialize(
           &the_mq->Message_queue,
           the_mq_attr,
           attr.mq_maxmsg,
           attr.mq_msgsize
      ) ) {

#if 0 && defined(RTEMS_MULTIPROCESSING)
    if ( pshared == PTHREAD_PROCESS_SHARED )
      _Objects_MP_Close( &_POSIX_Message_queue_Information, the_mq->Object.id );
#endif

    _POSIX_Message_queue_Free( the_mq );
    _Workspace_Free(name);
    _Thread_Enable_dispatch();
    rtems_set_errno_and_return_minus_one( ENOSPC );
  }

  _Objects_Open(
    &_POSIX_Message_queue_Information,
    &the_mq->Object,
    (char *) name
  );

  *message_queue = the_mq;

#if 0 && defined(RTEMS_MULTIPROCESSING)
  if ( pshared == PTHREAD_PROCESS_SHARED )
    _POSIX_Message_queue_MP_Send_process_packet(
      POSIX_MESSAGE_QUEUE_MP_ANNOUNCE_CREATE,
      the_mq->Object.id,
      (char *) name,
      0                          /* Not used */
    );
#endif

  _Thread_Enable_dispatch();
  return 0;
}
