## Process this file with autoconf to produce a configure script.
## 
## $Id$

AC_PREREQ(2.60)
AC_INIT([rtems-c-src-lib-libbsp-unix-posix],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([bsp_specs])
RTEMS_TOP(../../../../../..)

RTEMS_CANONICAL_TARGET_CPU
AM_INIT_AUTOMAKE([no-define nostdinc foreign 1.10])
RTEMS_BSP_CONFIGURE

RTEMS_ENABLE_CXX

RTEMS_PROG_CC_FOR_TARGET([-ansi -fasm])
RTEMS_PROG_CXX_FOR_TARGET

RTEMS_CANONICALIZE_TOOLS
RTEMS_PROG_CCAS
RTEMS_CHECK_MULTIPROCESSING(RTEMS_BSP)

RTEMS_CHECK_CXX

RTEMS_CONFIG_BUILD_SUBDIRS(tools)

AM_CONDITIONAL(HAS_CXX,test "$HAS_CPLUSPLUS" = "yes")

## bsp-specific options
RTEMS_BSPOPTS_SET([WORKSPACE_MB],[*],[2])
RTEMS_BSPOPTS_HELP([WORKSPACE_MB],
[The BSP's workspace RAM in MB.])

RTEMS_BSPOPTS_SET([HEAPSPACE_MB],[*],[1])
RTEMS_BSPOPTS_HELP([HEAPSPACE_MB],
[The BSP's heapspace RAM in MB.])

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
