/*
 * @file OssAuth.cpp
 * @brief
 *
 * @version 1.0
 * @date Fri Sep 28 21:31:08 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "digest/MD5.h"
#include "digest/Hmac.h"
#include "codec/Base64.h"

#include <string>
#include <iostream>


int
main(int argc, char *argv[])
{
    std::string key = "OtxrzxIsfpFjA7SwPzILwy8Bw21TLhquhboDYROV";
    std::string data = "PUT\nc8fdb181845a4ca6b8fec737b3581d76\ntext/html\nThu, 17 Nov 2005 18:49:58 GMT\nx-oss-magic:abracadabra\nx-oss-meta-author:foo@bar.com\n/quotes/nelson";

    std::string hmac = ossfs::Hmac::hmac(key, data);

    std::cout << hmac << std::endl;

    std::string base64 = ossfs::Base64::encode(hmac);

    std::cout << base64 << std::endl;

    return 0;
}

