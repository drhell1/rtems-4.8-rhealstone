/**
 * @file rtems/rtems/message.inl
 */

/*
 *  This include file contains the static inline implementation of all
 *  inlined routines in the Message Manager.
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

#ifndef _RTEMS_RTEMS_MESSAGE_INL
#define _RTEMS_RTEMS_MESSAGE_INL

#include <rtems/score/wkspace.h>

/*PAGE
 *
 *  _Message_queue_Is_null
 *
 *  DESCRIPTION:
 *
 *  This function places the_message at the rear of the outstanding
 *  messages on the_message_queue.
 */

RTEMS_INLINE_ROUTINE boolean _Message_queue_Is_null (
  Message_queue_Control *the_message_queue
)
{
  return ( the_message_queue == NULL  );
}


/*PAGE
 *
 *  _Message_queue_Free
 *
 *  DESCRIPTION:
 *
 *  This routine deallocates a message queue control block into
 *  the inactive chain of free message queue control blocks.
 */

RTEMS_INLINE_ROUTINE void _Message_queue_Free (
  Message_queue_Control *the_message_queue
)
{
  _Objects_Free( &_Message_queue_Information, &the_message_queue->Object );
}

/*PAGE
 *
 *  _Message_queue_Get
 *
 *  DESCRIPTION:
 *
 *  This function maps message queue IDs to message queue control
 *  blocks.  If ID corresponds to a local message queue, then it
 *  returns the_message_queue control pointer which maps to ID
 *  and location is set to OBJECTS_LOCAL.  If the message queue ID is
 *  global and resides on a remote node, then location is set
 *  to OBJECTS_REMOTE, and the_message_queue is undefined.
 *  Otherwise, location is set to OBJECTS_ERROR and
 *  the_message_queue is undefined.
 */

RTEMS_INLINE_ROUTINE Message_queue_Control *_Message_queue_Get (
  Objects_Id         id,
  Objects_Locations *location
)
{
  return (Message_queue_Control *)
     _Objects_Get( &_Message_queue_Information, id, location );
}

#endif
/* end of include file */
