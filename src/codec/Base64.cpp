/*
 * @file Base64.cpp
 * @brief
 *
 * @version 1.0
 * @date Thu Sep 27 15:07:07 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "codec/Base64.h"

#include <stdio.h>
#include <inttypes.h>

#include <string>

#include <openssl/bio.h>
#include <openssl/buffer.h>

namespace ossfs
{

Base64::Base64()
{

}

Base64::~Base64()
{

}

std::string
Base64::encode(const std::string &data)
{
    BIO *bmem = NULL;
    BIO *b64 = NULL;

    BUF_MEM *bptr = NULL;

    b64 = BIO_new(BIO_f_base64());

    if (NULL == b64) {
        fprintf(stderr, "BIO_new error\n");
        return "";
    }

    bmem = BIO_new(BIO_s_mem());

    if (NULL == bmem) {
        fprintf(stderr, "BIO_new error\n");
        return "";
    }

    b64 = BIO_push(b64, bmem);

    int writen = 0;

    writen = BIO_write(b64, data.c_str(), data.length());  //encode

    if (data.length() != writen) {
        fprintf(stderr,
                "BIO_write error, return value is %" PRIu32 "\n",
                writen);
        BIO_free_all(b64);
        return "";
    }

    int rv = 0;

    rv = BIO_flush(b64);

    // 1 for success
    if (1 != rv) {
        fprintf(stderr, "BIO_flush error\n");
        BIO_free_all(b64);
        return "";
    }

    BIO_get_mem_ptr(b64, &bptr);

    std::string encoded(bptr->data, bptr->length);

    BIO_free_all(b64);

    return encoded;
}

std::string
Base64::decode(const std::string &data)
{
    int len = 0;
    BIO *b64 = NULL;
    BIO *bmem = NULL;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new_mem_buf(const_cast<char *>(data.c_str()), data.length());

    bmem = BIO_push(b64, bmem);

    std::string decoded;
    char de[512];

    len = BIO_read(bmem, de, 512);

    decoded.append(de, len);

    BIO_free_all(bmem);

    return decoded;
}


}  // namespace ossfs

