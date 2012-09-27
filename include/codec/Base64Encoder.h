/*
 * @file Base64Encoder.h
 * @brief Base64 algorithm.
 *
 * @version 1.0
 * @date Tue Sep 25 20:51:44 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef digest_Base64_H_
#define digest_Base64_H_

#include <string>

#include <openssl/evp.h>


namespace ossfs
{


class Base64Encoder
{
public:
    Base64Encoder();

    ~Base64Encoder();

    static std::string encode(const std::string &data);

    bool init();

    bool update(const std::string &data);

    bool final();

private:
    EVP_CIPHER_CTX _ctx;
};


}


#endif  // digest_Base64_H_

