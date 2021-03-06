## Process this file with autoconf to produce a configure script.
## 
## $Id$

AC_PREREQ(2.61)
AC_INIT([rtems-cpukit],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([score])
RTEMS_TOP([..],[])

RTEMS_CANONICAL_TARGET_CPU

AM_INIT_AUTOMAKE([no-define nostdinc subdir-objects foreign 1.10])
AM_MAINTAINER_MODE

RTEMS_ENABLE_MULTILIB
RTEMS_ENABLE_MULTIPROCESSING
RTEMS_ENABLE_POSIX
RTEMS_ENABLE_ITRON
RTEMS_ENABLE_RTEMS_DEBUG
RTEMS_ENABLE_NETWORKING

RTEMS_ENV_RTEMSCPU
RTEMS_CHECK_RTEMS_DEBUG

# Is this a supported CPU?
AC_MSG_CHECKING([if cpu $RTEMS_CPU is supported])
if test -d "$srcdir/score/cpu/$RTEMS_CPU"; then
  AC_MSG_RESULT(yes)
else
  AC_MSG_ERROR(no)
fi

RTEMS_PROG_CC_FOR_TARGET([-fasm])
RTEMS_PROG_CCAS
RTEMS_CANONICALIZE_TOOLS
AM_PROG_CC_C_O
AC_PROG_RANLIB

RTEMS_CHECK_NEWLIB

# HACK: We should use a feature-based configuration.
AS_IF([test x"${RTEMS_CPU}" = x"unix"],[
# HACK: silently accept --enable-unixlib
  test -n "${enable_unixlib}" || enable_unixlib="yes"
])

# BSD-isms, used throughout the sources
# Not really used by this configure script
# FIXME: They should be eliminated if possible.
AC_CHECK_FUNCS([strsep strcasecmp snprintf])
AC_CHECK_FUNCS([strdup strndup strncasecmp])
AC_CHECK_FUNCS([bcopy bcmp])
AC_CHECK_FUNCS([isascii fileno])

## Check if the installed toolchain has these headers
AC_CHECK_HEADER([tar.h])

## BSD-ism, should not be used in RTEMS, 
## nevertheless it still is.
AC_CHECK_HEADER([sys/errno.h],[],
  [AC_MSG_ERROR([Missing required header sys/errno.h])])

## if libc provides stdint.h, use it.
AS_IF([test x"${ac_cv_header_stdint_h}" = xyes],
[RTEMS_USES_STDINT_H=yes],
[RTEMS_USES_STDINT_H=no])

## error out if libc doesn't at least provide inttypes.h
AS_IF([test x"${ac_cv_header_inttypes_h}" != xyes],
[AC_MSG_ERROR([Required header inttypes.h not found])])

AC_CHECK_TYPES([ uint8_t,  int8_t])
AC_CHECK_TYPES([uint16_t, int16_t])
AC_CHECK_TYPES([uint32_t, int32_t])
AC_CHECK_TYPES([uint64_t, int64_t])
AC_CHECK_TYPES([uintmax_t, intmax_t])
AC_CHECK_TYPES([uintptr_t, intptr_t])

AC_CACHE_CHECK([if PRIxPTR works],
[rtems_cv_PRIxPTR],[
  AS_IF([test x"$GCC" = xyes],[
    save_CFLAGS=$CFLAGS
    CFLAGS=-Werror])

  AC_COMPILE_IFELSE([
    AC_LANG_PROGRAM([
      #include <inttypes.h>
      #include <stdio.h>
    ],[
      void *ptr;
      printf("%" PRIxPTR "\n", (intptr_t) ptr);
    ])],
    [rtems_cv_PRIxPTR=yes],
    [rtems_cv_PRIxPTR=no])

  AS_IF([test x"$GCC" = xyes],[
    CFLAGS=$save_CFLAGS])
])

# These are conditionally defined by the toolchain
# FIXME: we should either conditionally compile those parts in
# RTEMS depending on them, or abort - For now, simply check.
AC_CHECK_HEADER([pthread.h],[
  AC_CHECK_TYPES([pthread_rwlock_t])
  AC_CHECK_TYPES([pthread_barrier_t])
  AC_CHECK_TYPES([pthread_spinlock_t])
])

RTEMS_CHECK_MULTIPROCESSING
RTEMS_CHECK_POSIX_API
RTEMS_CHECK_ITRON_API
RTEMS_CHECK_NETWORKING

AS_IF([test x"${RTEMS_USE_NEWLIB}" = xyes],
[RTEMS_USES_TAR_H=yes],
[RTEMS_USES_TAR_H=$ac_cv_header_tar_h])

AS_IF([test x"${RTEMS_CPU}" = x"unix"],[
## FIXME: This check is doubtful
AS_IF([test "$HAS_MP" = "yes"],
  [RTEMS_CHECK_SYSV_UNIX])

## The code fragment below had been used in tools/cpu/unix/gensize.c.
AC_CHECK_SIZEOF([CPU_CONTEXT],[],[
#include <stdio.h>
#include <setjmp.h>

typedef struct {
  jmp_buf     regs;
  int         isr_level;
} CPU_CONTEXT;
])
])

rtems_major=`echo _RTEMS_VERSION | sed "s/\..*//"`
rtems_minor=`echo _RTEMS_VERSION | sed "s/[[0-9]][[0-9]]*\.//;s/\..*//"`
rtems_revision=`echo _RTEMS_VERSION | sed "s/[[0-9]][[0-9]]*\.//;s/[[0-9]][[0-9]]*\.//;s/\..*//"`

cat >>cpuopts.tmp <<\_ACEOF
/**
 * @file rtems/score/cpuopts.h
 */
/* target cpu dependent options file */
/* automatically generated -- DO NOT EDIT!! */
#ifndef _RTEMS_SCORE_CPUOPTS_H
#define _RTEMS_SCORE_CPUOPTS_H
_ACEOF

RTEMS_CPUOPT([RTEMS_DEBUG],
  [test x"${enable_rtems_debug}" = x"yes"],
  [1],
  [if RTEMS_DEBUG is enabled])

RTEMS_CPUOPT([RTEMS_ITRON_API],
  [test x"$rtems_cv_HAS_ITRON_API" = x"yes"],
  [1],
  [if itron api is supported])

RTEMS_CPUOPT([RTEMS_MULTIPROCESSING],
  [test x"$enable_multiprocessing" = xyes],
  [1],
  [if multiprocessing is enabled])

RTEMS_CPUOPT([RTEMS_NEWLIB],
  [test x"$RTEMS_USE_NEWLIB" = xyes],
  [1],
  [if using newlib])

RTEMS_CPUOPT([RTEMS_POSIX_API],
  [test x"$rtems_cv_HAS_POSIX_API" = xyes],
  [1],
  [if posix api is supported])

RTEMS_CPUOPT([RTEMS_NETWORKING],
  [test x"$rtems_cv_HAS_NETWORKING" = xyes],
  [1],
  [if networking is enabled])

RTEMS_CPUOPT([RTEMS_UNIX],
  [test x"$RTEMS_CPU" = xunix],
  [1],
  [to indicate RTEMS unix])

RTEMS_CPUOPT([RTEMS_UNIXLIB],
  [test x"${enable_unixlib}" = xyes],
  [1],
  [to indicate RTEMS using RTEMS's unixlib])

RTEMS_CPUOPT([RTEMS_USES_STDINT_H],
  [test x"${RTEMS_USES_STDINT_H}" = x"yes"],
  [1],
  [if RTEMS uses stdint.h])

RTEMS_CPUOPT([RTEMS_USES_TAR_H],
  [test x"${RTEMS_USES_TAR_H}" = x"yes"],
  [1],
  [if RTEMS uses tar.h])

RTEMS_CPUOPT([RTEMS_VERSION],
  [true],
  ["]_RTEMS_VERSION["],
  [RTEMS version string])

RTEMS_CPUOPT([SIZEOF_CPU_CONTEXT],
  [test x"$RTEMS_CPU" = x"unix"],
  [$ac_cv_sizeof_CPU_CONTEXT],
  [The size of a 'CPU_CONTEXT', as computed by sizeof])

RTEMS_CPUOPT([__RTEMS_USE_TICKS_CPU_USAGE_STATISTICS__],
  [test x"${USE_TICKS_FOR_CPU_USAGE_STATISTICS}" = x"1"],
  [1],
  [disable nanosecond granularity for cpu usage statistics]
)

RTEMS_CPUOPT([__RTEMS_USE_TICKS_RATE_MONOTONIC_STATISTICS__],
  [test x"${USE_TICKS_FOR_RATE_MONOTONIC_STATISTICS}" = x"1"],
  [1],
  [disable nanosecond granularity for period statistics]
)

RTEMS_CPUOPT([__RTEMS_MAJOR__],
  [true],
  [$rtems_major],
  [major version portion of an RTEMS release])

RTEMS_CPUOPT([__RTEMS_MINOR__],
  [true],
  [$rtems_minor],
  [minor version portion of an RTEMS release])

RTEMS_CPUOPT([__RTEMS_REVISION__],
  [true],
  [$rtems_revision],
  [revision version portion of an RTEMS release])

cat >>cpuopts.tmp <<\_ACEOF

#endif /* _RTEMS_SCORE_CPUOPTS_H */
_ACEOF

AS_MKDIR_P(score/include/rtems/score)
AS_IF([test -f score/include/rtems/score/cpuopts.h],
[
  AS_IF([cmp -s score/include/rtems/score/cpuopts.h cpuopts.tmp 2>/dev/null],
  [ 
    AC_MSG_NOTICE([score/include/rtems/score/cpuopts.h is unchanged])
    rm -f cpuopts.tmp
  ],[
    AC_MSG_NOTICE([creating score/include/rtems/score/cpuopts.h])
    rm -f score/include/rtems/score/cpuopts.h
    mv cpuopts.tmp score/include/rtems/score/cpuopts.h
  ])
],[
    AC_MSG_NOTICE([creating score/include/rtems/score/cpuopts.h])
    rm -f score/include/rtems/score/cpuopts.h
    mv cpuopts.tmp score/include/rtems/score/cpuopts.h
])

AC_ENABLE_MULTILIB([Makefile],[..])

# libmisc/shell/* wants to assign file descriptors to stdio file descriptors.
AC_MSG_CHECKING([for assignable stdio])
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM(
    [#include <stdio.h>], 
    [stdin = fopen("/tmp", "r")])],
  [HAVE_ASSIGNABLE_STDIO=yes],
  [HAVE_ASSIGNABLE_STDIO=no])
AC_MSG_RESULT([$HAVE_ASSIGNABLE_STDIO])

# libmisc/serdbg exploits weak symbols
RTEMS_CHECK_GCC_WEAK

AC_CHECK_HEADERS([sys/cdefs.h],[NEED_SYS_CDEFS_H=no],[NEED_SYS_CDEFS_H=yes])
AC_CHECK_HEADERS([sys/queue.h],[NEED_SYS_QUEUE_H=no],[NEED_SYS_QUEUE_H=yes])

# FIXME: These checks are only in here to provide
# configuration-time diagnostics and are not really used.
AC_CHECK_DECLS([_POSIX_LOGIN_NAME_MAX],,,[#include <limits.h>])
AC_CHECK_DECLS([CHAR_BIT],,,[#include <limits.h>])

## BSD-ism, excluded from POSIX, but available on most platforms
AC_CHECK_DECLS([sbrk],,,[#include <unistd.h>])

## Check if libc provides BSD's strlcpy/strlcat
AC_CHECK_FUNCS(strlcpy strlcat)


# ... far too many conditionals ...
AM_CONDITIONAL(LIBRPC,[test x"$rtems_cv_HAS_NETWORKING" = x"yes"])
AM_CONDITIONAL(UNIX,[test x"${RTEMS_CPU}" = x"unix"])
AM_CONDITIONAL(NEWLIB,test x"$RTEMS_USE_NEWLIB" = x"yes")

AM_CONDITIONAL(HAS_MP,test x"$enable_multiprocessing" = x"yes" )

AM_CONDITIONAL(HAS_PTHREADS,test x"$rtems_cv_HAS_POSIX_API" = x"yes")
AM_CONDITIONAL(LIBPOSIX,test x"${RTEMS_CPU}" != x"unix")
AM_CONDITIONAL(LIBITRON,test x"$rtems_cv_HAS_ITRON_API" = x"yes")
AM_CONDITIONAL(LIBNETWORKING,test x"$rtems_cv_HAS_NETWORKING" = x"yes")

AM_CONDITIONAL([NEED_SYS_CDEFS_H],[test x"$NEED_SYS_CDEFS_H" = x"yes"])
AM_CONDITIONAL([NEED_SYS_QUEUE_H],[test x"$NEED_SYS_QUEUE_H" = x"yes"])

AM_CONDITIONAL([LIBSHELL],[test x"$HAVE_ASSIGNABLE_STDIO" = x"yes"])
AM_CONDITIONAL([LIBSERDBG],[test x"$rtems_cv_cc_attribute_weak" = x"yes"])

AM_CONDITIONAL([LIBDOSFS],[dnl
test x"${RTEMS_CPU}" != x"unix" \
&& test x"$ac_cv_type_uint8_t" = xyes \
&& test x"$ac_cv_type_uint16_t" = xyes])

AC_CONFIG_HEADER(config.h)

RTEMS_AMPOLISH3

# Explicitly list all Makefiles here
AC_CONFIG_FILES([
Makefile
rtems/Makefile
sapi/Makefile
score/Makefile
score/cpu/Makefile
score/cpu/arm/Makefile
score/cpu/bfin/Makefile
score/cpu/h8300/Makefile
score/cpu/i386/Makefile
score/cpu/m68k/Makefile
score/cpu/mips/Makefile
score/cpu/powerpc/Makefile
score/cpu/sh/Makefile
score/cpu/sparc/Makefile
score/cpu/unix/Makefile
score/cpu/no_cpu/Makefile
posix/Makefile
itron/Makefile
libblock/Makefile
libfs/Makefile
libcsupport/Makefile
libnetworking/Makefile
librpc/Makefile
libmisc/Makefile
libi2c/Makefile
libmd/Makefile
zlib/Makefile
httpd/Makefile
ftpd/Makefile
telnetd/Makefile
pppd/Makefile
shttpd/Makefile
wrapup/Makefile])

AC_CONFIG_COMMANDS([preinstall-stamp],
[test -z "$with_multisubdir" && ${MAKE} preinstall-stamp],
[MAKE=${MAKE}
with_multisubdir="$with_multisubdir"])

AC_OUTPUT
