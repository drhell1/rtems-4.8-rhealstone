## $Id$

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../../../testsuites/automake/compile.am

include $(top_srcdir)/ada.am

noinst_PROGRAMS = sp25
sp25_SOURCES = sp25.adb config.h sptest.adb sptest.ads
sp25_SOURCES += ../../support/init.c

sp25$(EXEEXT): sp25.adb init.$(OBJEXT)
	$(GNATCOMPILE) -margs -a $< -o $@

scndir = $(rtems_ada_testsdir)
dist_scn_DATA = sp25.scn

include $(top_srcdir)/../../../testsuites/automake/local.am
