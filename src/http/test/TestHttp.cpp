/*
 * @file TestHttp.cpp
 * @brief
 *
 * @version 1.0
 * @date Mon Oct  8 17:12:31 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "http/http.h"

#include <stdio.h>

#include <string>
#include <iostream>

using namespace ossfs;

int main()
{
    std::string host = "storage.aliyun.com";
    std::string uri = "/";

    HttpRequest req;
    req.setMethod(HttpRequest::GET);
    req.setURI(uri);

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

    std::cout << res.getVersion() << '\t'
              << res.getStatusCode() << '\t'
              << res.getReasonPhrase() << std::endl;

    std::cout << res.getBody() << std::endl;

    conn.close();

    return 0;
}


