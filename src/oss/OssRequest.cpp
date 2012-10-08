/*
 * @file OssRequest.cpp
 * @brief Aliyun OSS request.
 *
 * @version 1.0
 * @date Tue Oct  9 00:51:09 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "oss/OssRequest.h"

#include <time.h>

#include <string>

#include "http/HttpMacros.h"
#include "http/HttpRequest.h"
#include "oss/OssMacros.h"
#include "codec/Base64.h"
#include "digest/Hmac.h"

#include "log/log.h"
#include "util/util.h"

#define GMT_STR_LEN         30


#define ACCESS_ID       "ACSIOdXqRDLx7OaP"
#define ACCESS_KEY      "SS5bCvuE33"

namespace ossfs
{


OssRequest::OssRequest()
{
    // set Date header

    time_t t = time(NULL);

    if (-1 == t) {
        ERROR_LOG("time error, %s", strerror(errno));
        t = 0;
    }

    struct tm ttm;

    //if (NULL == localtime_r(&t, &ttm)) {
        //ERROR_LOG("localtime_r error, %s", strerror(errno));
    //}

    if (NULL == gmtime_r(&t, &ttm)) {
        ERROR_LOG("gmtime_r error, %s", strerror(errno));
    }

    char buf[GMT_STR_LEN];

    int rv = 0;

    rv = strftime(
             buf,
             GMT_STR_LEN,
             "%a, %d %b %Y %T GMT",
             &ttm
         );

    if (0 == rv) {
        ERROR_LOG("strftime error, %s", strerror(errno));
    }

    setHeader(HTTP_DATE, buf);

    // init Content-Length

    setContentLength(0);

    // init host

    setHost("storage.aliyun.com");
}

OssRequest::~OssRequest()
{

}

bool
OssRequest::sign()
{
    std::string tosign = _method + "\n"
                         + "\n"
                         + "\n"
                         + getHeader(HTTP_DATE) + "\n";

    std::string headers;

    for (std::map<std::string, std::string>::iterator it = _headers.begin();
         it != _headers.end(); ++it) {
        if (0 == it->first.find(OSS_HTTP_HEADER_PREFIX)) {
            headers += it->first
                       + HTTP_NAME_VALUE_SEPARATOR_STR
                       + it->second
                       + "\n";
        }
    }

    std::string resources = _uri;

    if (!_params.empty()) {
        resources += HTTP_PARAM_LEADER_STR;
    }

    for (std::map<std::string, std::string>::iterator it = _params.begin();
         it != _params.end();) {
        if (it->second.empty()) {
            resources += it->first;

        } else {
            resources += it->first
                         + HTTP_PARAM_NV_SEPARATOR_STR
                         + it->second;
        }

        if (it++ != _params.end()) {
            resources += HTTP_PARAM_SEPARATOR_STR;
        }
    }

    tosign += headers + resources;

    std::string signd =
        util::trim(Base64::encode(Hmac::hmac(ACCESS_KEY, tosign)));

    setHeader(
        HTTP_AUTHORIZATION,
        std::string("OSS ") + ACCESS_ID + ":" + signd
    );

    return true;
}



}  // namespace ossfs


