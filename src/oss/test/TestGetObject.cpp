/*
 * @file TestGetObject.cpp
 * @brief
 *
 * @version 1.0
 * @date Mon Oct  8 17:12:31 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "http/http.h"
#include "oss/OssProxy.h"
#include "oss/OssMacros.h"
#include "xml/Xml.h"

#include <stdio.h>
#include <string.h>

#include <string>
#include <list>
#include <map>
#include <iostream>

#define ACCESS_ID       "ACSIOdXqRDLx7OaP"
#define ACCESS_KEY      "SS5bCvuE33"

using namespace ossfs;

int main()
{
    std::string host = "storage.aliyun.com";

    OssProxy proxy(host, ACCESS_ID, ACCESS_KEY);

    char *buf = new char[30];
    memset(buf, 0, 30);

    std::string rv = proxy.getObject("shfs", "docs/readme.txt", buf, 30);

    if (rv != OSS_SUCCESS) {
        std::cerr << "error!" << std::endl;
        return 1;
    }

    std::cout << buf << std::endl;

    std::map<std::string, std::string> headers;

    headers.insert(std::pair<std::string, std::string>("Range", "bytes=0-4"));

    memset(buf, 0, 30);

    rv = proxy.getObject("shfs", "docs/readme.txt", buf, 30, headers);

    if (rv != OSS_SUCCESS) {
        std::cerr << "error!" << std::endl;
        return 1;
    }

    std::cout << buf << std::endl;

    return 0;
}


