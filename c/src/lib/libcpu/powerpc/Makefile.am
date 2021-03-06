##
## $Id$
##

ACLOCAL_AMFLAGS = -I ../../../aclocal

include $(top_srcdir)/../../../automake/compile.am

include_rtems_powerpcdir = $(includedir)/rtems/powerpc
include_rtems_powerpc_HEADERS = rtems/powerpc/cache.h \
    rtems/powerpc/debugmod.h rtems/powerpc/powerpc.h

include_rtems_scoredir = $(includedir)/rtems/score
include_libcpudir = $(includedir)/libcpu

include_libcpu_HEADERS =

EXTRA_DIST = old-exceptions/TODO old-exceptions/README
EXTRA_DIST += old-exceptions/irq_stub.S old-exceptions/ppccache.c
if OLD_EXCEPTIONS
include_rtems_score_HEADERS = old-exceptions/rtems/score/ppc_offs.h

noinst_PROGRAMS = old-exceptions/rtems-cpu.rel
old_exceptions_rtems_cpu_rel_SOURCES = old-exceptions/cpu.c \
    old-exceptions/cpu_asm.S old-exceptions/rtems/score/ppc_offs.h
old_exceptions_rtems_cpu_rel_CPPFLAGS = $(AM_CPPFLAGS) \
    -I$(srcdir)/old-exceptions
old_exceptions_rtems_cpu_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
else
noinst_PROGRAMS = new-exceptions/rtems-cpu.rel
new_exceptions_rtems_cpu_rel_SOURCES = new-exceptions/cpu.c \
    new-exceptions/cpu_asm.S
new_exceptions_rtems_cpu_rel_CPPFLAGS = $(AM_CPPFLAGS)
new_exceptions_rtems_cpu_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)


if !mpc5xx
include_libcpu_HEADERS += new-exceptions/raw_exception.h
noinst_PROGRAMS += new-exceptions/raw_exception.rel
new_exceptions_raw_exception_rel_SOURCES = new-exceptions/raw_exception.c \
    new-exceptions/asm_utils.S
new_exceptions_raw_exception_rel_CPPFLAGS = $(AM_CPPFLAGS)
new_exceptions_raw_exception_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

endif

## shared/include
if shared
include_libcpu_HEADERS += shared/include/io.h shared/include/mmu.h shared/include/page.h \
    shared/include/byteorder.h shared/include/pgtable.h

noinst_PROGRAMS += shared/cpuIdent.rel
shared_cpuIdent_rel_SOURCES = shared/include/cpuIdent.c shared/include/cpuIdent.h
shared_cpuIdent_rel_CPPFLAGS = $(AM_CPPFLAGS)
shared_cpuIdent_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

include_libcpu_HEADERS += shared/include/cpuIdent.h

## shared/cache
noinst_PROGRAMS += shared/cache.rel
shared_cache_rel_SOURCES = shared/src/cache.c shared/src/cache_.h \
    ../shared/src/cache_aligned_malloc.c ../shared/src/cache_manager.c \
    ../shared/include/cache.h
shared_cache_rel_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/shared/src
shared_cache_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

include_libcpu_HEADERS += ../shared/include/cache.h

## shared/stack
noinst_PROGRAMS += shared/stack.rel
shared_stack_rel_SOURCES = shared/src/stack.c shared/include/spr.h shared/src/stackTrace.h
shared_stack_rel_CPPFLAGS = $(AM_CPPFLAGS)
shared_stack_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

include_libcpu_HEADERS += shared/include/spr.h
include_libcpu_HEADERS += shared/src/stackTrace.h
endif

EXTRA_DIST += ppc403/README ppc403/vectors/README
if ppc403
## ppc403/clock
noinst_PROGRAMS += ppc403/clock.rel
ppc403_clock_rel_SOURCES = ppc403/clock/clock.c
ppc403_clock_rel_CPPFLAGS = $(AM_CPPFLAGS)
ppc403_clock_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## ppc403/console
noinst_PROGRAMS += ppc403/console.rel
if ppc405
ppc403_console_rel_SOURCES = ppc403/console/console405.c
else
ppc403_console_rel_SOURCES = ppc403/console/console.c
endif
ppc403_console_rel_CPPFLAGS = $(AM_CPPFLAGS)
ppc403_console_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

if OLD_EXCEPTIONS
## ppc403/ictrl
include_HEADERS = ppc403/ictrl/ictrl.h
else
include_HEADERS = 
shared_cpuIdent_rel_SOURCES = shared/include/cpuIdent.c 
shared_cpuIdent_rel_CPPFLAGS = $(AM_CPPFLAGS)
shared_cpuIdent_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

endif

if OLD_EXCEPTIONS
noinst_PROGRAMS += ppc403/ictrl.rel
ppc403_ictrl_rel_SOURCES = ppc403/ictrl/ictrl.c ppc403/ictrl/ictrl.h
ppc403_ictrl_rel_CPPFLAGS = $(AM_CPPFLAGS)
ppc403_ictrl_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

## ppc403/timer
noinst_PROGRAMS += ppc403/timer.rel
ppc403_timer_rel_SOURCES = ppc403/timer/timer.c
ppc403_timer_rel_CPPFLAGS = $(AM_CPPFLAGS)
ppc403_timer_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## ppc403/tty_drv
if ppc405
include_HEADERS += ppc403/tty_drv/tty_drv.h

noinst_PROGRAMS += ppc403/tty_drv.rel
ppc403_tty_drv_rel_SOURCES = ppc403/tty_drv/tty_drv.c ppc403/tty_drv/tty_drv.h
ppc403_tty_drv_rel_CPPFLAGS = $(AM_CPPFLAGS)
ppc403_tty_drv_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

if OLD_EXCEPTIONS
## ppc403/vectors
noinst_PROGRAMS += ppc403/vectors.rel
ppc403_vectors_rel_SOURCES = ppc403/vectors/vectors.S ppc403/vectors/align_h.S
ppc403_vectors_rel_CPPFLAGS = $(AM_CPPFLAGS)
ppc403_vectors_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif
endif

EXTRA_DIST += mpc5xx/README
if mpc5xx
include_mpc5xxdir = $(includedir)/mpc5xx

include_HEADERS = mpc5xx/include/mpc5xx.h

## mpc5xx/clock
noinst_PROGRAMS += mpc5xx/clock.rel
mpc5xx_clock_rel_SOURCES = mpc5xx/clock/clock.c
mpc5xx_clock_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc5xx_clock_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc5xx/console-generic
include_mpc5xx_HEADERS = mpc5xx/include/console.h

noinst_PROGRAMS += mpc5xx/console-generic.rel
mpc5xx_console_generic_rel_SOURCES = mpc5xx/console-generic/console-generic.c
mpc5xx_console_generic_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc5xx_console_generic_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc5xx/exceptions
include_libcpu_HEADERS += mpc5xx/exceptions/raw_exception.h

noinst_PROGRAMS += mpc5xx/exceptions.rel
mpc5xx_exceptions_rel_SOURCES = mpc5xx/exceptions/raw_exception.c
mpc5xx_exceptions_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc5xx_exceptions_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc5xx/irq
include_libcpu_HEADERS += mpc5xx/irq/irq.h

noinst_PROGRAMS += mpc5xx/irq.rel
mpc5xx_irq_rel_SOURCES = mpc5xx/irq/irq.c mpc5xx/irq/irq_init.c mpc5xx/irq/irq_asm.S
mpc5xx_irq_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc5xx_irq_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc5xx/timer
noinst_PROGRAMS += mpc5xx/timer.rel
mpc5xx_timer_rel_SOURCES = mpc5xx/timer/timer.c
mpc5xx_timer_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc5xx_timer_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc5xx/vectors
include_libcpu_HEADERS += mpc5xx/vectors/vectors.h

noinst_PROGRAMS += mpc5xx/vectors.rel
mpc5xx_vectors_rel_SOURCES = mpc5xx/vectors/vectors_init.c mpc5xx/vectors/vectors.S
mpc5xx_vectors_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc5xx_vectors_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

if mpc505
## mpc505/ictrl
include_HEADERS = mpc505/ictrl/ictrl.h

noinst_PROGRAMS += mpc505/ictrl.rel
mpc505_ictrl_rel_SOURCES = mpc505/ictrl/ictrl.c
mpc505_ictrl_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc505_ictrl_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc505/timer
noinst_PROGRAMS += mpc505/timer.rel
mpc505_timer_rel_SOURCES = mpc505/timer/timer.c
mpc505_timer_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc505_timer_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc505/vector
noinst_PROGRAMS += mpc505/vectors.rel
mpc505_vectors_rel_SOURCES = mpc505/vectors/vectors.S
mpc505_vectors_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc505_vectors_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

if mpc6xx

## mpc6xx/mmu
include_libcpu_HEADERS += mpc6xx/mmu/bat.h mpc6xx/mmu/pte121.h

noinst_PROGRAMS += mpc6xx/mmu.rel
mpc6xx_mmu_rel_SOURCES = mpc6xx/mmu/bat.c mpc6xx/mmu/bat.h \
    mpc6xx/mmu/pte121.c mpc6xx/mmu/pte121.h \
    mpc6xx/mmu/mmuAsm.S
mpc6xx_mmu_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc6xx_mmu_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc6xx/clock
include_libcpu_HEADERS += mpc6xx/clock/c_clock.h

noinst_PROGRAMS += mpc6xx/clock.rel
mpc6xx_clock_rel_SOURCES = mpc6xx/clock/c_clock.c mpc6xx/clock/c_clock.h
mpc6xx_clock_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc6xx_clock_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc6xx/timer
noinst_PROGRAMS += mpc6xx/timer.rel
mpc6xx_timer_rel_SOURCES = mpc6xx/timer/timer.c
mpc6xx_timer_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc6xx_timer_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

EXTRA_DIST += mpc8xx/README
if mpc8xx
include_mpc8xxdir = $(includedir)/mpc8xx

include_HEADERS = mpc8xx/include/mpc8xx.h

## mpc8xx/clock
noinst_PROGRAMS += mpc8xx/clock.rel
mpc8xx_clock_rel_SOURCES = mpc8xx/clock/clock.c
mpc8xx_clock_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc8xx_clock_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc8xx/console-generic
include_mpc8xx_HEADERS = mpc8xx/include/console.h

noinst_PROGRAMS += mpc8xx/console-generic.rel
mpc8xx_console_generic_rel_SOURCES = mpc8xx/console-generic/console-generic.c
mpc8xx_console_generic_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc8xx_console_generic_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc8xx/cpm
include_mpc8xx_HEADERS += mpc8xx/include/cpm.h

noinst_PROGRAMS += mpc8xx/cpm.rel
mpc8xx_cpm_rel_SOURCES = mpc8xx/cpm/cp.c mpc8xx/cpm/dpram.c
mpc8xx_cpm_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc8xx_cpm_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc8xx/mmu
include_mpc8xx_HEADERS += mpc8xx/include/mmu.h

noinst_PROGRAMS += mpc8xx/mmu.rel
mpc8xx_mmu_rel_SOURCES = mpc8xx/mmu/mmu.c
mpc8xx_mmu_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc8xx_mmu_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc8xx/timer
noinst_PROGRAMS += mpc8xx/timer.rel
mpc8xx_timer_rel_SOURCES = mpc8xx/timer/timer.c
mpc8xx_timer_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc8xx_timer_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

EXTRA_DIST += mpc8260/README
if mpc8260
include_mpc8260dir = $(includedir)/mpc8260

include_HEADERS = mpc8260/include/mpc8260.h

## mpc8260/console-generic
include_mpc8260_HEADERS = mpc8260/include/console.h

noinst_PROGRAMS += mpc8260/console-generic.rel
mpc8260_console_generic_rel_SOURCES = mpc8260/console-generic/console-generic.c \
    mpc8260/include/console.h
mpc8260_console_generic_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc8260_console_generic_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc8260/clock
noinst_PROGRAMS += mpc8260/clock.rel
mpc8260_clock_rel_SOURCES = mpc8260/clock/clock.c
mpc8260_clock_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc8260_clock_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc8260/cpm
include_mpc8260_HEADERS += mpc8260/include/cpm.h

noinst_PROGRAMS += mpc8260/cpm.rel
mpc8260_cpm_rel_SOURCES = mpc8260/cpm/cp.c mpc8260/cpm/dpram.c mpc8260/cpm/brg.c \
    mpc8260/include/cpm.h
mpc8260_cpm_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc8260_cpm_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc8260/mmu
include_mpc8260_HEADERS += mpc8260/include/mmu.h

noinst_PROGRAMS += mpc8260/mmu.rel
mpc8260_mmu_rel_SOURCES = mpc8260/mmu/mmu.c \
                          mpc8260/include/mmu.h
mpc8260_mmu_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc8260_mmu_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

## mpc8260/timer
noinst_PROGRAMS += mpc8260/timer.rel
mpc8260_timer_rel_SOURCES = mpc8260/timer/timer.c
mpc8260_timer_rel_CPPFLAGS = $(AM_CPPFLAGS)
mpc8260_timer_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

if mpc83xx
include_mpc83xxdir = $(includedir)/mpc83xx
include_mpc83xx_HEADERS  = mpc83xx/include/mpc83xx.h
include_mpc83xx_HEADERS += mpc83xx/network/tsec.h

## mpc83xx/network
if HAS_NETWORKING
noinst_PROGRAMS += mpc83xx/tsec.rel
mpc83xx_tsec_rel_SOURCES   = mpc83xx/network/tsec.c
mpc83xx_tsec_rel_CPPFLAGS  = $(AM_CPPFLAGS) 
mpc83xx_tsec_rel_CPPFLAGS += -D__INSIDE_RTEMS_BSD_TCPIP_STACK__  -D__BSD_VISIBLE
mpc83xx_tsec_rel_LDFLAGS   = $(RTEMS_RELLDFLAGS)
endif
## mpc83xx/i2c
include_mpc83xx_HEADERS += mpc83xx/i2c/mpc83xx_i2cdrv.h
noinst_PROGRAMS += mpc83xx/i2c.rel
mpc83xx_i2c_rel_SOURCES   = mpc83xx/i2c/mpc83xx_i2cdrv.c \
                            mpc83xx/i2c/mpc83xx_i2cdrv.h
mpc83xx_i2c_rel_CPPFLAGS  = $(AM_CPPFLAGS) 
mpc83xx_i2c_rel_LDFLAGS   = $(RTEMS_RELLDFLAGS)

endif

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../automake/local.am
