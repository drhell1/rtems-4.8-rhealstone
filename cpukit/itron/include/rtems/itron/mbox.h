/**
 * @file rtems/itron/mbox.h
 */

/*
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_ITRON_MBOX_H
#define _RTEMS_ITRON_MBOX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/itron/object.h>
#include <rtems/score/coremsg.h>

/*
 *  The following defines the control block used to manage each mailbox.
 */

typedef struct {
  ITRON_Objects_Control       Object;
  uint32_t                    count;
  boolean                     do_message_priority;
  CORE_message_queue_Control  message_queue;
}   ITRON_Mailbox_Control;

/*
 *  The following defines the information control block used to manage
 *  this class of objects.
 */

ITRON_EXTERN Objects_Information  _ITRON_Mailbox_Information;

/*
 *  _ITRON_Mailbox_Manager_initialization
 *
 *  DESCRIPTION:
 *
 *  This routine performs the initialization necessary for this manager.
 */

void _ITRON_Mailbox_Manager_initialization(
  uint32_t   maximum_mailboxes
);

/*
 *  _ITRON_Mailbox_Translate_core_message_queue_return_code
 *
 *  DESCRIPTION:
 *
 *  This routine translates a core message queue object status
 *  into the appropriate ITRON status code.
 */

ER _ITRON_Mailbox_Translate_core_message_queue_return_code(
  CORE_message_queue_Status status
);

#include <rtems/itron/mbox.inl>

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
