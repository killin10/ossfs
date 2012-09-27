/*
 * @file HmacTest.cpp
 * @brief 
 * 
 * @version 1.0
 * @date Tue Sep 25 20:40:50 2012
 * 
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "digest/Hmac.h"

#include <string>
#include <iostream>

int
main(int argc, char *argv[]) 
{
    std::string data = "abcdefg";

    std::cout << ossfs::Hmac::hmac("sw", data) << std::endl;
    std::cout << ossfs::Hmac::hmac("ws", data) << std::endl;

    return 0;
}
