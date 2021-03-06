--
--  TMTEST / BODY
--
--  DESCRIPTION:
--
--  This package is the implementation of Test 22 of the RTEMS
--  Timing Test Suite.
--
--  DEPENDENCIES: 
--
--  
--
--  COPYRIGHT (c) 1989-1997.
--  On-Line Applications Research Corporation (OAR).
--
--  The license and distribution terms for this file may in
--  the file LICENSE in this distribution or at
--  http://www.rtems.com/license/LICENSE.
--
--  $Id$
--

with INTERFACES; use INTERFACES;
with RTEMS;
with RTEMS_CALLING_OVERHEAD;
with TEST_SUPPORT;
with TEXT_IO;
with TIME_TEST_SUPPORT;
with UNSIGNED32_IO;

package body TMTEST is

--PAGE
-- 
--  INIT
--

   procedure INIT (
      ARGUMENT : in     RTEMS.TASK_ARGUMENT
   ) is
      ID     : RTEMS.ID;
      STATUS : RTEMS.STATUS_CODES;
   begin

      TEXT_IO.NEW_LINE( 2 );
      TEXT_IO.PUT_LINE( "*** TIME TEST 22 ***" );

      RTEMS.MESSAGE_QUEUE_CREATE( 
         RTEMS.BUILD_NAME( 'M', 'Q', '1', ' ' ),
         100,
         16,
         RTEMS.DEFAULT_ATTRIBUTES,
         TMTEST.MESSAGE_QUEUE_ID,
         STATUS
      );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "MESSAGE_QUEUE_CREATE" );

      RTEMS.TASK_CREATE( 
         RTEMS.BUILD_NAME( 'L', 'O', 'W', ' ' ), 
         10,
         2048, 
         RTEMS.NO_PREEMPT,
         RTEMS.DEFAULT_ATTRIBUTES,
         ID,
         STATUS
      );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_CREATE LOW" );

      RTEMS.TASK_START( ID, TMTEST.LOW_TASK'ACCESS, 0, STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_START LOW" );

      RTEMS.TASK_CREATE( 
         RTEMS.BUILD_NAME( 'P', 'R', 'M', 'T' ),
         11,
         2048, 
         RTEMS.DEFAULT_MODES,
         RTEMS.DEFAULT_ATTRIBUTES,
         ID,
         STATUS
      );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_CREATE PREEMPT" );

      RTEMS.TASK_START( ID, TMTEST.PREEMPT_TASK'ACCESS, 0, STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_START PREEMPT" );

      RTEMS.TASK_DELETE( RTEMS.SELF, STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_DELETE OF SELF" );

   end INIT;

--PAGE
-- 
--  HIGH_TASK
--

   procedure HIGH_TASK (
      ARGUMENT : in     RTEMS.TASK_ARGUMENT
   ) is
      BUFFER         : TMTEST.BUFFER;
      BUFFER_POINTER : RTEMS.ADDRESS;
      COUNT          : RTEMS.UNSIGNED32;
      STATUS         : RTEMS.STATUS_CODES;
   begin

      BUFFER_POINTER := BUFFER'ADDRESS;

      TIMER_DRIVER.INITIALIZE;
         RTEMS.MESSAGE_QUEUE_BROADCAST(
            TMTEST.MESSAGE_QUEUE_ID,
            BUFFER_POINTER,
            16,
            COUNT,
            STATUS 
         );
      TMTEST.END_TIME := TIMER_DRIVER.READ_TIMER;

      TIME_TEST_SUPPORT.PUT_TIME( 
         "MESSAGE_QUEUE_BROADCAST (readying)", 
         TMTEST.END_TIME, 
         1,
         0,
         RTEMS_CALLING_OVERHEAD.MESSAGE_QUEUE_BROADCAST
      );

      RTEMS.TASK_SUSPEND( RTEMS.SELF, STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_SUSPEND" );

   end HIGH_TASK;

--PAGE
-- 
--  LOW_TASK
--

   procedure LOW_TASK (
      ARGUMENT : in     RTEMS.TASK_ARGUMENT
   ) is
      ID             : RTEMS.ID;
      BUFFER         : TMTEST.BUFFER;
      BUFFER_POINTER : RTEMS.ADDRESS;
      OVERHEAD       : RTEMS.UNSIGNED32;
      COUNT          : RTEMS.UNSIGNED32;
      MESSAGE_SIZE   : RTEMS.UNSIGNED32;
      STATUS         : RTEMS.STATUS_CODES;
   begin

      BUFFER_POINTER := BUFFER'ADDRESS;

      RTEMS.TASK_CREATE( 
         RTEMS.BUILD_NAME( 'H', 'I', 'G', 'H' ), 
         5,
         2048, 
         RTEMS.NO_PREEMPT,
         RTEMS.DEFAULT_ATTRIBUTES,
         ID,
         STATUS
      );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_CREATE HIGH" );

      RTEMS.TASK_START( ID, TMTEST.HIGH_TASK'ACCESS, 0, STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_START HIGH" );

      RTEMS.MESSAGE_QUEUE_RECEIVE(
         TMTEST.MESSAGE_QUEUE_ID,
         BUFFER_POINTER,
         RTEMS.DEFAULT_MODES,
         RTEMS.NO_TIMEOUT,
         MESSAGE_SIZE,
         STATUS
      );

      TIMER_DRIVER.INITIALIZE;
         for INDEX in 1 .. TIME_TEST_SUPPORT.OPERATION_COUNT
         loop
            TIMER_DRIVER.EMPTY_FUNCTION;
         end loop;
      OVERHEAD := TIMER_DRIVER.READ_TIMER;

      TIMER_DRIVER.INITIALIZE;
         for INDEX in 1 .. TIME_TEST_SUPPORT.OPERATION_COUNT
         loop
            RTEMS.MESSAGE_QUEUE_BROADCAST(
               TMTEST.MESSAGE_QUEUE_ID,
               BUFFER_POINTER,
               16,
               COUNT,
               STATUS 
            );
         end loop;
      TMTEST.END_TIME := TIMER_DRIVER.READ_TIMER;

      TIME_TEST_SUPPORT.PUT_TIME( 
         "MESSAGE_QUEUE_BROADCAST (no waiting tasks)",
         TMTEST.END_TIME, 
         TIME_TEST_SUPPORT.OPERATION_COUNT, 
         OVERHEAD,
         RTEMS_CALLING_OVERHEAD.MESSAGE_QUEUE_BROADCAST
      );

      RTEMS.MESSAGE_QUEUE_RECEIVE(
         TMTEST.MESSAGE_QUEUE_ID,
         BUFFER_POINTER,
         RTEMS.DEFAULT_MODES,
         RTEMS.NO_TIMEOUT,
         MESSAGE_SIZE,
         STATUS
      );

      -- should go to PREEMPT_TASK here

      TMTEST.END_TIME := TIMER_DRIVER.READ_TIMER;

      TIME_TEST_SUPPORT.PUT_TIME( 
         "MESSAGE_QUEUE_BROADCAST (preempt)",
         TMTEST.END_TIME, 
         1,
         0,
         RTEMS_CALLING_OVERHEAD.MESSAGE_QUEUE_BROADCAST
      );

      RTEMS.SHUTDOWN_EXECUTIVE( 0 );

   end LOW_TASK;

--PAGE
-- 
--  LOW_TASK
--

   procedure PREEMPT_TASK (
      ARGUMENT : in     RTEMS.TASK_ARGUMENT
   ) is
      BUFFER         : TMTEST.BUFFER;
      BUFFER_POINTER : RTEMS.ADDRESS;
      COUNT          : RTEMS.UNSIGNED32;
      STATUS         : RTEMS.STATUS_CODES;
   begin

      BUFFER_POINTER := BUFFER'ADDRESS;

      TIMER_DRIVER.INITIALIZE;
         RTEMS.MESSAGE_QUEUE_BROADCAST(
            TMTEST.MESSAGE_QUEUE_ID,
            BUFFER_POINTER,
            16,
            COUNT,
            STATUS 
         );

      -- should be preempted by LOW_TASK

   end PREEMPT_TASK;

end TMTEST;
