/*
 * @file TestOss.cpp
 * @brief
 *
 * @version 1.0
 * @date Mon Oct  8 17:12:31 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "http/http.h"
#include "oss/OssRequest.h"
#include "xml/Xml.h"

#include <stdio.h>

#include <string>
#include <iostream>

#define ACCESS_ID       "ACSIOdXqRDLx7OaP"
#define ACCESS_KEY      "SS5bCvuE33"

using namespace ossfs;

int main()
{
    std::string host = "storage.aliyun.com";
    std::string uri = "/";

    OssRequest req;
    req.setMethod(HttpRequest::GET);
    req.setURI(uri);
    req.sign(ACCESS_ID, ACCESS_KEY);

    HttpConnection conn;

    int rv = 0;

    rv = conn.connect(host);

    if (-1 == rv) {
        fprintf(stderr, "connect error\n");
        return 1;
    }

    rv = conn.sendRequest(req);

    if (-1 == rv) {
        fprintf(stderr, "send request error\n");
        return 1;
    }

    HttpResponse res;
    rv = conn.recvResponse(&res);

    if (-1 == rv) {
        fprintf(stderr, "recv response error\n");
        return 1;
    }

    std::cout << res.getVersion() << " "
              << res.getStatusCode() << " "
              << res.getReasonPhrase() << std::endl;

    std::cout << res.getBody() << std::endl;

    conn.close();

    return 0;
}


