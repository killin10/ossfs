bin_PROGRAMS = ossfs

ossfs_SOURCES = src/fs/main.cpp

ossfs_LDADD = src/libossfs.la

AM_CXXFLAGS = -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS  \
			  -D_FILE_OFFSET_BITS=64
export AM_CXXFLAGS

GLOBAL_INCLUDES = -I/usr/include/libxml2
export GLOBAL_INCLUDES

INCLUDES = $(GLOBAL_INCLUDES) -I$(top_srcdir)/include

SUBDIRS = src
