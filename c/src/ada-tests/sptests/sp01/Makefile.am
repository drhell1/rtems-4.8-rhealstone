## $Id$

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../../../testsuites/automake/compile.am

include $(top_srcdir)/ada.am

noinst_PROGRAMS = sp01
sp01_SOURCES = sp01.adb config.h sptest.adb sptest.ads
sp01_SOURCES += ../../support/init.c

sp01$(EXEEXT): sp01.adb init.$(OBJEXT)
	$(GNATCOMPILE) -margs -a $< -o $@

scndir = $(rtems_ada_testsdir)
dist_scn_DATA = sp01.scn

include $(top_srcdir)/../../../testsuites/automake/local.am
