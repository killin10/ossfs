/*
 * @file TestListObjects.cpp
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

    std::string rv = proxy.putObject("shfs", "docs/", "");

    if (rv != OSS_SUCCESS) {
        std::cerr << "error!" << std::endl;
        return 1;
    }

    std::map<std::string, std::string> metas;

    metas.insert(
        std::pair<std::string, std::string>("x-oss-meta-linux-mod", "644")
    );

    rv = proxy.putObject("shfs", "docs/readme.txt", "hello world", metas);

    if (rv != OSS_SUCCESS) {
        std::cerr << "error!" << std::endl;
        return 1;
    }



    return 0;
}


