/*
 * @file Base64Test.cpp
 * @brief
 *
 * @version 1.0
 * @date Thu Sep 27 22:04:25 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "codec/Base64.h"

#include <string>
#include <iostream>

int
main(int argc, char *argv[])
{
    std::string data = "abc\n";

    std::string encode = ossfs::Base64::encode(data);

    std::cout << encode << std::endl;
    std::cout << encode.length() << std::endl;

    std::string decode = ossfs::Base64::decode(encode);

    std::cout << decode << std::endl;

    return 0;
}
