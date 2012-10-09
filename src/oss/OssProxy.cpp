/*
 * @file OssProxy.cpp
 * @brief proxy all operations with Aliyun OSS
 *
 * @version 1.0
 * @date Tue Oct  9 11:52:38 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "oss/OssProxy.h"

#include <string>
#include <list>

#include "http/http.h"
#include "oss/OssMacros.h"
#include "oss/OssRequest.h"
#include "oss/OssResponse.h"

#include "log/log.h"
#include "xml/xml.h"


namespace ossfs
{


OssProxy::OssProxy()
{

}

OssProxy::OssProxy(
    const std::string &host,
    const std::string &id,
    const std::string &key
)
{
    _host = host;
    _accessId = id;
    _accessKey = key;
}

OssProxy::~OssProxy()
{

}

std::string
OssProxy::listObjects(
    const std::string &bucket,
    const std::string &prefix,
    const std::string &delimiter,
    std::list<std::string> *objects
)
{
    if (NULL == objects) {
        FATAL_LOG("objects, null pointer");
        return OSS_FAILED;
    }

    OssRequest req;

    req.setMethod(HttpRequest::GET);
    req.setHost(_host);
    req.setURI(OSS_PATH_SEPARATOR_STR + bucket);

    if (!prefix.empty()) {
        req.setParameter(OSS_PARAM_PREFIX, prefix);
    }

    if (!delimiter.empty()) {
        req.setParameter(OSS_PARAM_DELIMITER, delimiter);
    }

    req.setContentLength(0);

    if (!req.sign(_accessId, _accessKey)) {
        ERROR_LOG("sign request error");
        return OSS_FAILED;
    }

    HttpConnection conn(_host);

    int rv = 0;
    rv = conn.connect();

    if (-1 == rv) {
        ERROR_LOG("connect to %s failed", _host.c_str());
        return OSS_FAILED;
    }

    rv = conn.sendRequest(req);

    if (-1 == rv) {
        ERROR_LOG("send request error");
        return OSS_FAILED;
    }

    OssResponse res;

    rv = conn.recvResponse(&res);

    if (-1 == rv) {
        ERROR_LOG("recv response error");
        return OSS_FAILED;
    }

    if (HttpResponse::SC_OK != res.getStatusCode()) {
        ERROR_LOG("list objects error, \n%s", res.getBody().c_str());
        return OSS_FAILED;
    }

    Xml x;

    XmlNode *root = NULL;
    root = x.loadMemory(res.getBody().c_str(), res.getBody().length());

    if (NULL == root) {
        ERROR_LOG("parse xml from buffer error");
        return OSS_FAILED;
    }

    std::list<XmlNode *> nodes;

    bool rf = false;
    rf = x.getNodesByXPath("/ListBucketResult/Contents/Key", &nodes);

    if (!rf) {
        ERROR_LOG("query object keys from xml error");
        return OSS_FAILED;
    }

    for (std::list<XmlNode *>::iterator it = nodes.begin();
         it != nodes.end(); ++it) {
        objects->push_back(x.getNodeValue(*it));
    }

    conn.close();

    return OSS_SUCCESS;
}



}  // namespace ossfs


