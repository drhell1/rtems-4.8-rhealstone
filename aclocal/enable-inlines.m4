dnl $Id$

AC_DEFUN(RTEMS_ENABLE_INLINES,
[AC_ARG_ENABLE(rtems-inlines,
[  --enable-rtems-inlines               enable RTEMS inline functions]
[                                       (use macros)],
[case "${enableval}" in
  yes) RTEMS_USE_MACROS=no ;;
  no) RTEMS_USE_MACROS=yes ;;
  *)  AC_MSG_ERROR(bad value ${enableval} for disable-rtems-inlines option) ;;
esac],[RTEMS_USE_MACROS=no])
])
