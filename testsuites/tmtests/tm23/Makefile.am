##
## $Id$
##

MANAGERS = io event timer semaphore

rtems_tests_PROGRAMS = tm23.exe
tm23_exe_SOURCES = task1.c system.h ../include/timesys.h

dist_rtems_tests_DATA = tm23.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

tm23_exe_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

OPERATION_COUNT = @OPERATION_COUNT@
AM_CPPFLAGS += -I$(top_srcdir)/include -DOPERATION_COUNT=$(OPERATION_COUNT)
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(tm23_exe_OBJECTS) $(tm23_exe_LDADD)
LINK_LIBS = $(tm23_exe_LDLIBS)

tm23.exe$(EXEEXT): $(tm23_exe_OBJECTS) $(tm23_exe_DEPENDENCIES)
	@rm -f tm23.exe$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
