/*
 * @file MD5.cpp
 * @brief MD5 digest algorithm
 *
 * @version 1.0
 * @date Sun Sep 23 16:41:10 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "digest/MD5.h"

#include <openssl/md5.h>

namespace ossfs
{

const int MD5::DIGEST_LENGTH = MD5_DIGEST_LENGTH;
const int MD5::HEX_DIGEST_LENGTH = DIGEST_LENGTH * 2;

MD5::MD5()
{
    _md = new unsigned char[DIGEST_LENGTH];
}

MD5::~MD5()
{
    delete [] _md;
    _md = NULL;
}

bool
MD5::init()
{
    int rt = 0;

    rt = MD5_Init(&_ctx);

    // 1 for success
    if (1 != rt) {
        return false;
    }

    return true;
}

bool
MD5::update(const std::string &data)
{
    int rt = 0;

    rt = MD5_Update(&_ctx, data.c_str(), data.length());

    if (1 != rt) {
        return false;
    }

    return true;
}

bool
MD5::final()
{
    int rt = 0;

    rt = MD5_Final(_md, &_ctx);

    if (1 != rt) {
        return false;
    }

    return true;
}

std::string
MD5::digest() const
{
    return std::string((char *) _md);
}

std::string 
MD5::digestHex() const
{

}


}  // namespace ossfs


