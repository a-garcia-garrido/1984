#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([recognize1984], [1984], [txema.gonz@gmail.com])
AM_INIT_AUTOMAKE([-Werror foreign])
AC_CONFIG_SRCDIR([recognizer.cpp])
AC_CONFIG_HEADERS([config.h])

AC_LANG(C++)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([opencv_contrib], [createEigenFaceRecognizer])
AC_CHECK_LIB([opencv_core], [Algorithm])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
