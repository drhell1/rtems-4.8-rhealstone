##
## $Id$
##

MANAGERS = io semaphore

rtems_tests_PROGRAMS = tm04.exe
tm04_exe_SOURCES = task1.c system.h ../include/timesys.h

dist_rtems_tests_DATA = tm04.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

tm04_exe_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

OPERATION_COUNT = @OPERATION_COUNT@
AM_CPPFLAGS += -I$(top_srcdir)/include -DOPERATION_COUNT=$(OPERATION_COUNT)
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(tm04_exe_OBJECTS) $(tm04_exe_LDADD)
LINK_LIBS = $(tm04_exe_LDLIBS)

tm04.exe$(EXEEXT): $(tm04_exe_OBJECTS) $(tm04_exe_DEPENDENCIES)
	@rm -f tm04.exe$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
