/*
 * @file fs.h
 * @brief fuse file system hooks
 *
 * @version 1.0
 * @date Wed Oct 10 01:15:15 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef fs_fs_H_
#define fs_fs_H_

#include <fuse.h>

namespace ossfs
{


int ossfs_getattr(const char *path, struct stat *st);

int ossfs_mkdir(const char *path, mode_t mode);

int ossfs_unlink(const char *path);

int ossfs_rmdir(const char *path);

int ossfs_rename(const char *oldpath, const char *newpath);

int ossfs_chmod(const char *path, mode_t mode);


}  // namespace ossfs


#endif  // fs_fs_H_


