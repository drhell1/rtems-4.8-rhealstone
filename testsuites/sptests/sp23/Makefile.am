##
## $Id$
##

MANAGERS = io dual_ported_memory semaphore clock

rtems_tests_PROGRAMS = sp23.exe
sp23_exe_SOURCES = init.c task1.c system.h

dist_rtems_tests_DATA = sp23.scn
dist_rtems_tests_DATA += sp23.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

sp23_exe_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(sp23_exe_OBJECTS) $(sp23_exe_LDADD)
LINK_LIBS = $(sp23_exe_LDLIBS)

sp23.exe$(EXEEXT): $(sp23_exe_OBJECTS) $(sp23_exe_DEPENDENCIES)
	@rm -f sp23.exe$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
