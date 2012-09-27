/*
 * @file Base64.h
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


class Base64
{
public:
    Base64();

    ~Base64();

    static std::string encode(const std::string &data);

    static std::string decode(const std::string &data);
};


}


#endif  // digest_Base64_H_

