##
## $Id$
##

include $(top_srcdir)/automake/multilib.am
include $(top_srcdir)/automake/compile.am

if !UNIX
noinst_LIBRARIES = libblock.a
libblock_a_SOURCES = src/bdbuf.c src/blkdev.c src/diskdevs.c src/ramdisk.c \
    src/ide_part_table.c src/show_bdbuf.c \
    include/rtems/bdbuf.h include/rtems/blkdev.h \
    include/rtems/diskdevs.h include/rtems/ramdisk.h \
    include/rtems/ide_part_table.h
endif

include $(top_srcdir)/automake/local.am
