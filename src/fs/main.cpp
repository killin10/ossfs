/*
 * @file main.cpp
 * @brief
 *
 * @version 1.0
 * @date Wed Oct 10 14:19:24 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#define FUSE_USE_VERSION 26

#include <fuse.h>

#include "fs/fs.h"

using namespace ossfs;

static struct fuse_operations oss_oper = {0};

int
main(int argc, char *argv[])
{
    {
        oss_oper.getattr = ossfs_getattr;
        oss_oper.readdir = ossfs_readdir;
        oss_oper.mkdir = ossfs_mkdir;
        oss_oper.rmdir = ossfs_rmdir;
        oss_oper.unlink = ossfs_unlink;
        oss_oper.rename = ossfs_rename;
        oss_oper.open = ossfs_open;
        oss_oper.read = ossfs_read;
        oss_oper.write = ossfs_write;
        oss_oper.release = ossfs_release;
        oss_oper.create = ossfs_create;
    }

    return fuse_main(argc, argv, &oss_oper, NULL);
}
