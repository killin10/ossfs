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
#include <set>

#include "http/HttpMacros.h"
#include "http/HttpRequest.h"
#include "oss/OssMacros.h"
#include "codec/Base64.h"
#include "digest/Hmac.h"

#include "log/log.h"
#include "util/util.h"

#define GMT_STR_LEN         30


namespace ossfs
{

static std::set<std::string>::value_type signResourcesInit[] = {
    std::set<std::string>::value_type(OSS_RESOURCE_ACL),
    std::set<std::string>::value_type(OSS_RESOURCE_GROUP),
    std::set<std::string>::value_type(OSS_RESOURCE_UPLOAD_ID),
    std::set<std::string>::value_type(OSS_RESOURCE_PART_NUMBER),
    std::set<std::string>::value_type(OSS_RESOURCE_UPLOADS),
    std::set<std::string>::value_type(OSS_OVERRIDE_CONTENT_TYPE),
    std::set<std::string>::value_type(OSS_OVERRIDE_CONTENT_LANGUAGE),
    std::set<std::string>::value_type(OSS_OVERRIDE_EXPIRES),
    std::set<std::string>::value_type(OSS_OVERRIDE_CACHE_CONTROL),
    std::set<std::string>::value_type(OSS_OVERRIDE_CONTENT_DISPOSITION),
    std::set<std::string>::value_type(OSS_OVERRIDE_CONTENT_ENCODING)
};

std::set<std::string> OssRequest::_signResources(
    signResourcesInit,
    signResourcesInit + 11
);


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
OssRequest::sign(const std::string &id, const std::string &key)
{
    std::string tosign = _method + "\n"
                         + "\n"
                         + "\n"
                         + getHeader(HTTP_DATE) + "\n";

    std::string headers;

    for (std::map<std::string, std::string>::iterator it = _headers.begin();
         it != _headers.end(); ++it) {
        if (0 == it->first.find(OSS_HEADER_PREFIX)) {
            headers += it->first
                       + HTTP_NAME_VALUE_SEPARATOR_STR
                       + it->second
                       + "\n";
        }
    }

    std::string resources = _uri + HTTP_PARAM_LEADER_STR;

    for (std::map<std::string, std::string>::iterator it = _params.begin();
         it != _params.end();) {
        std::set<std::string>::iterator sit = _signResources.find(it->first);

        if (_signResources.end() == sit) {
            // do not need to be signed

            ++it;
            continue;
        }

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

    if (resources[resources.length() - 1] == HTTP_PARAM_NV_SEPARATOR_CHR) {
        resources = resources.substr(0, resources.length() - 1);
    }

    if (resources[resources.length() - 1] == HTTP_PARAM_LEADER_CHR) {
        resources = resources.substr(0, resources.length() - 1);
    }

    tosign += headers + resources;

    std::string signd =
        util::trim(Base64::encode(Hmac::hmac(key, tosign)));

    setHeader(
        HTTP_AUTHORIZATION,
        std::string("OSS ") + id + ":" + signd
    );

    return true;
}



}  // namespace ossfs


