#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([ossfs], [0.1], [shiwei2012@gmail.com])
AC_CONFIG_SRCDIR([include/codec/Base64.h])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE(ossfs, 0.1)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# enable debug or not                                                            
AC_ARG_ENABLE(debug, AS_HELP_STRING([--enable-debug], [enable debug mode(default=no)]),
                [],                                                              
                [enable_debug=no])                                               
AS_IF([test "x$enable_debug" = "xyes"], [CXXFLAGS="-g2 -O0 -DDEBUG -Wall"],         
      [test "x$enable_debug" = "xno"], [CXXFLAGS="-O2 -Wall"],                   
      [])                     

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lfuse':
AC_CHECK_LIB([fuse], [fuse_main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [pthread_create])
# FIXME: Replace `main' with a function in `-lrt':
AC_CHECK_LIB([rt], [clock_gettime])
# FIXME: Replace `main' with a function in `-lssl':
AC_CHECK_LIB([ssl], [SHA1_Init])
# FIXME: Replace `main' with a function in `-lxml2':
AC_CHECK_LIB([xml2], [xmlNewDoc])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h netdb.h netinet/in.h string.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT64_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MKTIME
AC_CHECK_FUNCS([clock_gettime gettimeofday localtime_r memset socket strerror])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/codec/Makefile
                 src/digest/Makefile
                 src/log/Makefile
                 src/net/Makefile
                 src/sys/Makefile
                 src/util/Makefile
                 src/xml/Makefile
                 src/http/Makefile
                 src/oss/Makefile
                 src/fs/Makefile])
AC_OUTPUT
