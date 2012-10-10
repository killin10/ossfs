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

#include <map>
#include <string>

#define OSS_FILE_BLOCK_SIZE     (4 * 1024)

namespace ossfs
{

struct oss_file_block {
    char *fb_buf;
    size_t fb_len;  // buf len
    size_t fb_size;  // real data len
    bool fb_dirty;

    oss_file_block() {
        fb_buf = NULL;
        fb_len = 0;
        fb_size = 0;
        fb_dirty = false;
    }

    ~oss_file_block() {
        if (NULL != fb_buf) {
            delete [] fb_buf;
            fb_buf = NULL;
        }
    }
};

struct oss_file_info {
    mode_t fi_mode;
    off_t fi_size;
    bool fi_dirty;

    std::map<off_t, struct oss_file_block *> fi_data;

    oss_file_info() {
        fi_mode = 0;
        fi_size = 0;
        fi_dirty = false;
    }

    ~oss_file_info() {
        for (std::map<off_t, struct oss_file_block *>::iterator it =
                 fi_data.begin(); it != fi_data.end(); ++it) {
            delete it->second;
        }
    }
};

int ossfs_getattr(const char *path, struct stat *st);

int ossfs_mkdir(const char *path, mode_t mode);

int ossfs_unlink(const char *path);

int ossfs_rmdir(const char *path);

int ossfs_rename(const char *oldpath, const char *newpath);

int ossfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                  off_t offset, struct fuse_file_info *fi);

int ossfs_open(const char *path, struct fuse_file_info *fi);


int do_read(const std::string &object, char *buf, size_t size, off_t offset,
            size_t file_size);

int do_read_from_buffer(struct oss_file_info *info, char *buf,
                        size_t size, off_t offset);

int ossfs_read(const char *path, char *buf, size_t size, off_t offset,
               struct fuse_file_info *fi);

int do_write_to_buffer(struct oss_file_info *info, const char *buf,
                       size_t size, off_t offset);

int ossfs_write(const char *path, const char *buf, size_t size,
                off_t offset, struct fuse_file_info *fi);

int ossfs_release(const char *path, struct fuse_file_info *fi);

int ossfs_create(const char *path, mode_t mode, struct fuse_file_info *fi);

int ossfs_chmod(const char *path, mode_t mode);


}  // namespace ossfs


#endif  // fs_fs_H_


