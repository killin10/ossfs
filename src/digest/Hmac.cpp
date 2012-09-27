/*
 * @file Hmac.cpp
 * @brief Hash-based Message Authentication Code.
 *
 * @version 1.0
 * @date Tue Sep 25 17:35:18 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "digest/Hmac.h"

#include <string>

#include <openssl/hmac.h>
#include <openssl/sha.h>

namespace ossfs
{


const unsigned int Hmac::DIGEST_LENGTH = SHA_DIGEST_LENGTH;
const unsigned int Hmac::HEX_DIGEST_LENGTH = SHA_DIGEST_LENGTH * 2;

std::string
Hmac::hmac(const std::string &key, const std::string &data)
{
    Hmac hmac;

    if (!hmac.init(key)) {
        return "";
    }

    if (!hmac.update(data)) {
        return "";
    }

    if (!hmac.final()) {
        return "";
    }

    return hmac.digestHex();
}

Hmac::Hmac()
{
    _md = new unsigned char[DIGEST_LENGTH];

    HMAC_CTX_init(&_ctx);
}

Hmac::~Hmac()
{
    HMAC_CTX_cleanup(&_ctx);

    delete [] _md;
    _md = NULL;
}

bool
Hmac::init(const std::string &key)
{
    int rt = 0;

    rt = HMAC_Init(&_ctx, key.c_str(), key.length(), EVP_sha1());

    // 1 for success
    if (1 != rt) {
        return false;
    }

    return true;
}

bool
Hmac::update(const std::string &data)
{
    int rt = 0;

    rt = HMAC_Update(
             &_ctx, (const unsigned char *) data.c_str(),
             data.length()
         );

    if (1 != rt) {
        return false;
    }

    return true;
}

bool
Hmac::final()
{
    int rt = 0;

    unsigned int mdLen = DIGEST_LENGTH;

    rt = HMAC_Final(&_ctx, _md, &mdLen);

    if (1 != rt) {
        return false;
    }

    return true;
}

std::string
Hmac::digest() const
{
    return std::string((char *) _md);
}

std::string
Hmac::digestHex() const
{
    // one more byte for null
    char md[HEX_DIGEST_LENGTH + 1];

    for (int i = 0; i < DIGEST_LENGTH; ++i) {
        // size is 3, one byte for null
        snprintf(md + i * 2, 3, "%02x", _md[i]);
        //sprintf(md + i * 2, "%02x", _md[i]);
    }

    return std::string(md, HEX_DIGEST_LENGTH);
}


}  // namespace ossfs

