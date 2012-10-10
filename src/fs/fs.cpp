/*
 * @file fs.cpp
 * @brief  fuse hooks
 *
 * @version 1.0
 * @date Wed Oct 10 09:34:46 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "fs/fs.h"

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#include <string>
#include <map>
#include <list>

#include "http/http.h"
#include "oss/OssProxy.h"
#include "oss/OssMacros.h"

#include "log/log.h"
#include "util/util.h"

#define MOUNT_POINT     "/"

#define OSS_META_LINUX_MODE         "x-oss-meta-linux-mode"

#define BUCKET          "shfs"
#define HOST            "storage.aliyun.com"
#define ACCESS_ID       "ACSIOdXqRDLx7OaP"
#define ACCESS_KEY      "SS5bCvuE33"

namespace ossfs
{

bool
refer_to_dir(const std::string &path)
{
    if (path[path.length() - 1] == OSS_PATH_SEPARATOR_CHR) {
        return true;
    }

    return false;
}


int do_getattr(
    const std::string &object,
    struct stat *st
)
{
    std::string rc;
    std::map<std::string, std::string> metas;

    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    rc = proxy.headObject(BUCKET, object, &metas);

    if (OSS_SUCCESS == rc) {
        st->st_uid = geteuid();
        st->st_gid = getegid();

        std::map<std::string, std::string>::const_iterator it =
            metas.find(OSS_META_LINUX_MODE);

        if (refer_to_dir(object)) {
            // directory
            st->st_nlink = 2;

            if (metas.end() == it) {
                st->st_mode = S_IFDIR | 0775;

            } else {
                st->st_mode = util::conv<mode_t, std::string>(it->second);
            }

        } else {
            // regular

            st->st_nlink = 1;

            if (metas.end() == it) {
                st->st_mode = S_IFREG | 0664;

            } else {
                st->st_mode = util::conv<mode_t, std::string>(it->second);
            }

            std::map<std::string, std::string>::const_iterator rit =
                metas.find(HTTP_CONTENT_LENGTH);

            if (metas.end() != rit) {
                st->st_size = util::conv<off_t, std::string>(rit->second);
            }
        }

        std::map<std::string, std::string>::const_iterator tit =
            metas.find(HTTP_LAST_MODIFIED);

        if (metas.end() != tit) {
            struct tm t;

            char *rp = strptime(
                           tit->second.c_str(),
                           "%a, %d %b %Y %T GMT",
                           &t
                       );

            if (NULL != rp) {
                //time_t gmt = mktime(&t);
                //localtime_r(&gmt, &t);
                st->st_mtime = mktime(&t);
            }
        }

        return 0;
    }

    if (OSS_FAILED == rc) {
        return -ENETUNREACH;
    }

    if (OSS_NOT_FOUND == rc) {
        return -ENOENT;
    }

    return 0;
}


int
ossfs_getattr(const char *path, struct stat *st)
{
    std::string spath = path;

    memset(st, 0, sizeof(struct stat));

    if (spath == MOUNT_POINT) {
        st->st_mode = S_IFDIR | 0775;
        st->st_nlink = 2;
        return 0;
    }

    std::string object = spath.substr(1);

    int rv = 0;

    rv = do_getattr(object, st);

    if (-ENOENT == rv && !refer_to_dir(object)) {
        return do_getattr(object + OSS_PATH_SEPARATOR_STR, st);
    }

    return rv;
}

int
ossfs_mkdir(const char *path, mode_t mode)
{
    std::string spath = path;
    std::string object = spath.substr(1);

    if (!refer_to_dir(object)) {
        object += OSS_PATH_SEPARATOR_STR;
    }

    std::map<std::string, std::string> metas;
    metas.insert(
        std::pair<std::string, std::string>(
            OSS_META_LINUX_MODE,
            util::conv<std::string, mode_t>(mode | S_IFDIR))
    );

    std::string rc;

    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    rc = proxy.putObject(BUCKET, object, "", metas);

    if (OSS_SUCCESS != rc) {
        return -ENETUNREACH;
    }

    return 0;
}

int
ossfs_unlink(const char *path)
{
    std::string spath = path;
    std::string object = spath.substr(1);

    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    std::string rc;
    rc = proxy.deleteObject(BUCKET, object);

    if (OSS_SUCCESS != rc) {
        return -ENETUNREACH;
    }

    return 0;
}

int
ossfs_rmdir(const char *path)
{
    std::string spath = path;
    std::string object = spath.substr(1);

    if (!refer_to_dir(object)) {
        object += OSS_PATH_SEPARATOR_STR;
    }

    std::string prefix = object;

    std::string rc;
    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    std::list<std::string> entries;

    rc = proxy.listObjects(BUCKET, prefix, OSS_PATH_SEPARATOR_STR, &entries);

    if (OSS_SUCCESS != rc) {
        return -ENETUNREACH;
    }

    if (entries.empty()) {
        return -ENOENT;

    } else if (entries.size() != 1) {
        return -ENOTEMPTY;
    }

    rc = proxy.deleteObject(BUCKET, object);

    if (OSS_SUCCESS != rc) {
        return -ENETUNREACH;
    }

    return 0;
}

int
ossfs_rename(const char *oldpath, const char *newpath)
{
    std::string src = std::string(oldpath).substr(1);
    std::string dest = std::string(newpath).substr(1);

    if (!refer_to_dir(src)) {
        src += OSS_PATH_SEPARATOR_STR;
    }

    if (!refer_to_dir(dest)) {
        dest += OSS_PATH_SEPARATOR_STR;
    }

    std::string rc;

    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    rc = proxy.copyObject(BUCKET, src, dest);

    if (OSS_SUCCESS != rc) {
        return -ENETUNREACH;
    }

    rc = proxy.deleteObject(BUCKET, src);

    if (OSS_SUCCESS != rc) {
        // ignore intentionally
        //return -ENETUNREACH;
    }

    return 0;
}

int
ossfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
              off_t offset, struct fuse_file_info *fi)
{
    (void) offset;
    (void) fi;

    std::string spath = path;

    std::string prefix = spath.substr(1);

    if (!prefix.empty() && !refer_to_dir(prefix)) {
        prefix += OSS_PATH_SEPARATOR_STR;
    }

    std::list<std::string> entries;

    std::string rc;
    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    rc = proxy.listObjects(BUCKET, prefix, OSS_PATH_SEPARATOR_STR, &entries);

    if (OSS_SUCCESS != rc) {
        return -ENETUNREACH;
    }


    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    std::string entry;

    if (spath == MOUNT_POINT) {
        for (std::list<std::string>::iterator it = entries.begin();
             it != entries.end(); ++it) {
            if (!refer_to_dir(*it)
                && it->find(OSS_PATH_SEPARATOR_STR) != std::string::npos) {
                continue;
            }

            if (refer_to_dir(*it)) {
                entry = it->substr(0, it->length() - 1);

            } else {
                entry = *it;
            }

            filler(buf, entry.c_str(), NULL, 0);
        }

    } else {
        for (std::list<std::string>::iterator it = entries.begin();
             it != entries.end(); ++it) {
            if (*it == prefix) {
                continue;
            }

            entry = it->substr(prefix.length());

            if (refer_to_dir(entry)) {
                entry = entry.substr(0, entry.length() - 1);
            }

            filler(buf, entry.c_str(), NULL, 0);
        }
    }

    return 0;
}

/*
int
ossfs_open(const char *path, struct fuse_file_info *fi)
{
    std::string spath = path;
    std::string object = spath.substr(1);

    std::string rc;
    std::map<std::string, std::string> metas;

    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    rc = proxy.headObject(BUCKET, object, &metas);

    if (OSS_SUCCESS == rc) {
        struct oss_file_info *info = new oss_file_info();

        std::map<std::string, std::string>::const_iterator it =
            metas.find(OSS_META_LINUX_MODE);

        if (metas.end() == it) {
            info->fi_mode = S_IFREG | 0664;

        } else {
            info->fi_mode = util::conv<mode_t, std::string>(it->second);
        }

        std::map<std::string, std::string>::const_iterator rit =
            metas.find(HTTP_CONTENT_LENGTH);

        if (metas.end() != rit) {
            info->fi_size = util::conv<off_t, std::string>(rit->second);
        }

        fi->fh = (uint64_t) info;
    }

    if (OSS_FAILED == rc) {
        return -ENETUNREACH;
    }

    if (OSS_NOT_FOUND == rc) {
        return -ENOENT;
    }

    return 0;
}
*/

int
ossfs_open(const char *path, struct fuse_file_info *fi)
{
    std::string spath = path;
    std::string object = spath.substr(1);

    struct oss_file_info *info = NULL;

    std::string rc;
    std::map<std::string, std::string> metas;

    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    rc = proxy.headObject(BUCKET, object, &metas);

    if (OSS_SUCCESS == rc) {
        info = new oss_file_info();

        std::map<std::string, std::string>::const_iterator it =
            metas.find(OSS_META_LINUX_MODE);

        if (metas.end() == it) {
            info->fi_mode = S_IFREG | 0664;

        } else {
            info->fi_mode = util::conv<mode_t, std::string>(it->second);
        }

        std::map<std::string, std::string>::const_iterator rit =
            metas.find(HTTP_CONTENT_LENGTH);

        if (metas.end() != rit) {
            info->fi_size = util::conv<off_t, std::string>(rit->second);
        }

        fi->fh = (uint64_t) info;

        int readn = 0;

        for (off_t offset = 0; offset < info->fi_size;) {
            struct oss_file_block *blk = new oss_file_block();

            info->fi_data.insert(
                std::pair<off_t, struct oss_file_block *>(offset, blk)
            );

            blk->fb_buf = new char[OSS_FILE_BLOCK_SIZE];
            blk->fb_len = OSS_FILE_BLOCK_SIZE;

            memset(blk->fb_buf, 0, blk->fb_len);

            readn = do_read(object, blk->fb_buf, blk->fb_len,
                            offset, info->fi_size);

            if (readn < 0) {
                ERROR_LOG("read file data error whilst openning it");

                delete info;
                info = NULL;
                fi->fh = 0;

                return readn;
            }

            blk->fb_size = readn;

            offset += readn;
        }
    }

    if (OSS_FAILED == rc) {
        return -ENETUNREACH;
    }

    if (OSS_NOT_FOUND == rc && !(fi->flags & O_CREAT)) {
        return -ENOENT;
    }

    if (OSS_NOT_FOUND == rc && (fi->flags & O_CREAT)) {
        struct oss_file_info *info = new oss_file_info();
        info->fi_mode = S_IFREG | 0664;
        fi->fh = (uint64_t) info;
    }

    return 0;
}

int
do_read(const std::string &object, char *buf, size_t size, off_t offset,
        size_t file_size)
{
    std::map<std::string, std::string> headers;

    off_t end = (offset + size > file_size) ?
                (file_size - 1) : (offset + size - 1);

    std::string range = "bytes="
                        + util::conv<std::string, off_t>(offset)
                        + "-"
                        + util::conv<std::string, off_t>(end);

    headers.insert(
        std::pair<std::string, std::string>(HTTP_RANGE, range)
    );

    std::string rc;
    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    rc = proxy.getObject(BUCKET, object, buf, size, headers);

    if (OSS_SUCCESS != rc) {
        return -ENETUNREACH;
    }

    return size;
}

int
do_read_from_buffer(struct oss_file_info *info, char *buf,
                    size_t size, off_t offset)
{
    // find the first block

    std::map<off_t, struct oss_file_block *>::iterator it =
        info->fi_data.lower_bound(offset);

    if (offset != it->first) {
        --it;
    }

    // read data

    int readn = 0;
    int toread = 0;
    int inblk_off = offset % OSS_FILE_BLOCK_SIZE;

    for (char *buf_idx = buf; buf_idx < buf + size;) {
        if (it->second->fb_size - inblk_off < size - readn) {
            toread = it->second->fb_size - inblk_off;

        } else {
            toread = size - readn;
        }

        memcpy(buf_idx, it->second->fb_buf + inblk_off, toread);

        buf_idx += toread;
        readn += toread;

        inblk_off += toread;

        if (inblk_off >= OSS_FILE_BLOCK_SIZE) {
            inblk_off = 0;
            ++it;
        }
    }

    return size;
}

int
ossfs_read(const char *path, char *buf, size_t size, off_t offset,
           struct fuse_file_info *fi)
{
    std::string spath = path;
    std::string object = spath.substr(1);

    struct oss_file_info *info = (struct oss_file_info *) fi->fh;

    return do_read_from_buffer(info, buf, size, offset);
}


int
do_write_to_buffer(struct oss_file_info *info, const char *buf,
                   size_t size, off_t offset)
{
    // find the first block

    std::map<off_t, struct oss_file_block *>::iterator it =
        info->fi_data.lower_bound(offset);

    if (info->fi_data.end() == it) {
        struct oss_file_block *nblk = new oss_file_block();

        info->fi_data.insert(
            std::pair<off_t, struct oss_file_block *>(offset, nblk)
        );

        nblk->fb_buf = new char[OSS_FILE_BLOCK_SIZE];
        nblk->fb_len = OSS_FILE_BLOCK_SIZE;

        memset(nblk->fb_buf, 0, nblk->fb_len);

        it = info->fi_data.lower_bound(offset);

    } else if (offset != it->first) {
        --it;
    }

    // write data

    int writen = 0;
    int towrite = 0;
    int inblk_off = offset % OSS_FILE_BLOCK_SIZE;

    for (const char *buf_idx = buf; buf_idx < buf + size;) {
        struct oss_file_block *blk = it->second;

        if (blk->fb_len - inblk_off < size - writen) {
            towrite = blk->fb_len - inblk_off;

        } else {
            towrite = size - writen;
        }

        memcpy(blk->fb_buf + inblk_off, buf_idx, towrite);

        buf_idx += towrite;
        writen += towrite;

        inblk_off += towrite;

        if (inblk_off > blk->fb_size) {
            blk->fb_size = inblk_off;
        }

        blk->fb_dirty = true;

        if (inblk_off >= OSS_FILE_BLOCK_SIZE) {
            inblk_off = 0;
            ++it;
        }

        if (info->fi_data.end() == it) {
            struct oss_file_block *nblk = new oss_file_block();

            info->fi_data.insert(
                std::pair<off_t, struct oss_file_block *>(offset + writen, nblk)
            );

            nblk->fb_buf = new char[OSS_FILE_BLOCK_SIZE];
            nblk->fb_len = OSS_FILE_BLOCK_SIZE;

            memset(nblk->fb_buf, 0, nblk->fb_len);

            it = info->fi_data.lower_bound(offset + writen);
        }
    }

    // dirty flag

    info->fi_dirty = true;

    // update file size

    if (offset + size > info->fi_size) {
        info->fi_size = offset + size;
        INFO_LOG("%d", info->fi_size);
    }

    return size;

}

int
ossfs_write(const char *path, const char *buf, size_t size,
            off_t offset, struct fuse_file_info *fi)
{
    std::string spath = path;
    std::string object = spath.substr(1);

    struct oss_file_info *info = (struct oss_file_info *) fi->fh;

    return do_write_to_buffer(info, buf, size, offset);
}

int
ossfs_release(const char *path, struct fuse_file_info *fi)
{
    struct oss_file_info *info = (struct oss_file_info *) fi->fh;

    if (!info->fi_dirty) {
        delete info;

        info = NULL;
        fi->fh = 0;

        return 0;
    }

    // put object

    char *buf = new char[info->fi_size];
    char *buf_idx = buf;

    for (std::map<off_t, struct oss_file_block *>::iterator it =
             info->fi_data.begin(); it != info->fi_data.end();) {
        memcpy(buf_idx, it->second->fb_buf, it->second->fb_size);
        buf_idx += it->second->fb_size;

        delete it->second;
        info->fi_data.erase(it++);
    }

    std::string spath = path;
    std::string object = spath.substr(1);

    std::map<std::string, std::string> metas;
    metas.insert(
        std::pair<std::string, std::string>(
            OSS_META_LINUX_MODE,
            util::conv<std::string, mode_t>(info->fi_mode))
    );

    std::string rc;

    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    INFO_LOG("info->fi_size %d", info->fi_size);
    rc = proxy.putObject(BUCKET, object, buf, info->fi_size, metas);

    delete [] buf;
    buf = NULL;

    delete info;
    info = NULL;

    if (OSS_SUCCESS != rc) {
        return -ENETUNREACH;
    }

    return 0;
}

int
ossfs_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    std::string spath = path;
    std::string object = spath.substr(1);

    std::map<std::string, std::string> metas;
    metas.insert(
        std::pair<std::string, std::string>(
            OSS_META_LINUX_MODE,
            util::conv<std::string, mode_t>(mode))
    );

    std::string rc;

    OssProxy proxy(HOST, ACCESS_ID, ACCESS_KEY);

    rc = proxy.putObject(BUCKET, object, "", metas);

    if (OSS_SUCCESS != rc) {
        return -ENETUNREACH;
    }

    struct oss_file_info *info = new oss_file_info();

    info->fi_mode = mode;

    fi->fh = (uint64_t) info;

    return 0;
}

int
ossfs_chmod(const char *path, mode_t mode)
{
    return 0;
}


}  // namespace ossfs


