##
## $Id$
##

MANAGERS = io rate_monotonic semaphore

rtems_tests_PROGRAMS = tm29.exe
tm29_exe_SOURCES = task1.c system.h ../include/timesys.h

dist_rtems_tests_DATA = tm29.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

tm29_exe_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

OPERATION_COUNT = @OPERATION_COUNT@
AM_CPPFLAGS += -I$(top_srcdir)/include -DOPERATION_COUNT=$(OPERATION_COUNT)
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(tm29_exe_OBJECTS) $(tm29_exe_LDADD)
LINK_LIBS = $(tm29_exe_LDLIBS)

tm29.exe$(EXEEXT): $(tm29_exe_OBJECTS) $(tm29_exe_DEPENDENCIES)
	@rm -f tm29.exe$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
