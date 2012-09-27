/*
 * @file MD5Test.cpp
 * @brief A simple test for MD5.
 * 
 * @version 1.0
 * @date Tue Sep 25 16:52:34 2012
 * 
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "digest/MD5.h"

#include <string>
#include <iostream>

int
main(int argc, char *argv[]) 
{
    std::string data = "abcdefg";

    std::cout << ossfs::MD5::md5(data) << std::endl;

    return 0;
}

