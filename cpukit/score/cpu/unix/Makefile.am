##
## $Id$
##

include $(top_srcdir)/automake/compile.am

AM_CPPFLAGS += -DCPU_SYNC_IO

include_rtemsdir = $(includedir)/rtems
include_rtems_HEADERS = rtems/asm.h

include_rtems_scoredir = $(includedir)/rtems/score
include_rtems_score_HEADERS = rtems/score/types.h rtems/score/cpu.h \
    rtems/score/unix.h

noinst_LIBRARIES = libscorecpu.a
libscorecpu_a_SOURCES = cpu.c
libscorecpu_a_CPPFLAGS = $(AM_CPPFLAGS)

include $(srcdir)/preinstall.am
include $(top_srcdir)/automake/local.am
