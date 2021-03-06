##
## $Id$
##

ACLOCAL_AMFLAGS = -I ../../../../aclocal

# FIXME: We must not include *.cfg
include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg

CLEANFILES =

include $(top_srcdir)/../../../../automake/compile.am
include $(top_srcdir)/../../bsp.am

dist_project_lib_DATA = bsp_specs

include_HEADERS = include/bsp.h
include_HEADERS += include/tm27.h

nodist_include_HEADERS = include/bspopts.h
DISTCLEANFILES = include/bspopts.h

noinst_PROGRAMS =

SUBDIRS = . tools

include_bspdir = $(includedir)/bsp
include_bsp_HEADERS = ../../i386/shared/irq/irq.h \
    ../../i386/shared/irq/irq_asm.h

include_HEADERS += include/crt.h
nodist_include_HEADERS += ../../shared/include/coverhd.h

EXTRA_DIST = start/start.S
start.$(OBJEXT): start/start.S
	$(CPPASCOMPILE) -o $@ -c $<

project_lib_DATA = start.$(OBJEXT)

EXTRA_DIST += start/start16.S
start16.$(OBJEXT): start/start16.S
	$(CPPASCOMPILE) $(AM_CPPFLAGS) -DHEADERADDR=$(HEADERADDR) -o $@ -c $<

start16-elf32.$(OBJEXT): start16.$(OBJEXT)
	$(LD) -N -T $(top_srcdir)/startup/linkcmds -Ttext $(START16ADDR) -e start16 -nostdlib \
	  --oformat=elf32-i386 \
	-o $@ $<

start16.bin: start16-elf32.$(OBJEXT)
	$(OBJCOPY) -O binary $< $@
CLEANFILES += start16.bin

project_lib_DATA += start16.bin

dist_project_lib_DATA += startup/linkcmds

noinst_PROGRAMS += clock.rel
clock_rel_SOURCES = clock/ckinit.c clock/todcfg.c ../../shared/tod.c
clock_rel_CPPFLAGS = $(AM_CPPFLAGS)
clock_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

include_rtemsdir = $(includedir)/rtems
include_rtems_HEADERS = console/keyboard.h console/kd.h \
    console/serial_mouse.h console/ps2_drv.h console/fb_vga.h

noinst_PROGRAMS += console.rel
include_HEADERS += ../../i386/shared/comm/i386_io.h
console_rel_SOURCES = console/console.c console/inch.c console/outch.c \
    console/defkeymap.c console/fb_vga.c console/keyboard.c \
    console/mouse_parser.c console/pc_keyb.c console/ps2_mouse.c \
    console/serial_mouse.c console/vgainit.c console/vt.c console/videoAsm.S \
    ../../i386/shared/comm/uart.c ../../i386/shared/comm/tty_drv.c
console_rel_CPPFLAGS = $(AM_CPPFLAGS)
console_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

noinst_PROGRAMS += gdb.rel
gdb_rel_SOURCES = ../../i386/shared/comm/i386-stub.c \
    ../../i386/shared/comm/i386-stub-glue.c \
    ../../i386/shared/comm/gdb_glue.c
gdb_rel_CPPFLAGS = $(AM_CPPFLAGS)
gdb_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

noinst_PROGRAMS += gnat.rel
gnat_rel_SOURCES = ../../shared/gnatinstallhandler.c
gnat_rel_CPPFLAGS = $(AM_CPPFLAGS)
gnat_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

noinst_PROGRAMS += pci.rel
include_HEADERS += ../../i386/shared/pci/pcibios.h
pci_rel_SOURCES = ../../i386/shared/pci/pcibios.c ../../i386/shared/pci/pcibios.h
pci_rel_CPPFLAGS = $(AM_CPPFLAGS)
pci_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

noinst_PROGRAMS += startup.rel
include_HEADERS += ../../i386/shared/comm/uart.h
startup_rel_SOURCES = ../../shared/bsplibc.c ../../shared/bsppost.c \
    startup/bspstart.c startup/exit.c ../../i386/shared/irq/idt.c \
    ../../i386/shared/irq/irq.c ../../i386/shared/irq/irq_init.c \
    ../../shared/bootcard.c ../../shared/sbrk.c \
    startup/ldsegs.S ../../i386/shared/irq/irq_asm.S
startup_rel_CPPFLAGS = $(AM_CPPFLAGS)
startup_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

noinst_PROGRAMS += timer.rel
timer_rel_SOURCES = timer/timer.c timer/timerisr.S
timer_rel_CPPFLAGS = $(AM_CPPFLAGS)
timer_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

if HAS_NETWORKING
ne2000_CPPFLAGS = -D__INSIDE_RTEMS_BSD_TCPIP_STACK__
noinst_PROGRAMS += ne2000.rel
ne2000_rel_SOURCES = ne2000/ne2000.c
ne2000_rel_CPPFLAGS = $(AM_CPPFLAGS) $(ne2000_CPPFLAGS)
ne2000_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

if HAS_NETWORKING
# This driver needs to be reworked for the BSD stack.
# We only install wd80x3.h if HAS_NETWORKING was defined
include_HEADERS += include/wd80x3.h

wd8003_CPPFLAGS = -D__INSIDE_RTEMS_BSD_TCPIP_STACK__
noinst_PROGRAMS += wd8003.rel
wd8003_rel_SOURCES = wd8003/wd8003.c include/wd80x3.h
wd8003_rel_CPPFLAGS = $(AM_CPPFLAGS) $(wd8003_CPPFLAGS)
wd8003_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

if HAS_NETWORKING
3c509_CPPFLAGS = -D__INSIDE_RTEMS_BSD_TCPIP_STACK__
noinst_PROGRAMS += 3c509.rel
3c509_rel_SOURCES = 3c509/3c509.c 3c509/3c509.h 3c509/elink.c 3c509/elink.h
3c509_rel_CPPFLAGS = $(AM_CPPFLAGS) $(3c509_CPPFLAGS)
3c509_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

noinst_PROGRAMS += ide.rel
ide_rel_SOURCES = ide/idecfg.c ide/ide.c
ide_rel_CPPFLAGS = $(AM_CPPFLAGS)
ide_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

noinst_LIBRARIES = libbsp.a
libbsp_a_SOURCES =
libbsp_a_LIBADD = startup.rel clock.rel console.rel timer.rel ide.rel \
    gdb.rel gnat.rel pci.rel
# We only build the Network library if HAS_NETWORKING was defined
# dec21140 is supported via libchip
if HAS_NETWORKING
libbsp_a_LIBADD += ne2000.rel wd8003.rel 3c509.rel
endif
libbsp_a_LIBADD += ../../../libcpu/@RTEMS_CPU@/cache.rel \
    ../../../libcpu/@RTEMS_CPU@/page.rel \
    ../../../libcpu/@RTEMS_CPU@/score.rel

EXTRA_DIST += HOWTO README.dec21140 STATUS times_i486dx times_p5

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../../automake/local.am
