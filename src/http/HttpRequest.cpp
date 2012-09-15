/*
 * @file HttpRequest.cpp
 * @brief http request data packet
 *
 * @version 1.0
 * @date Sat Sep 15 00:26:54 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "http/HttpRequest.h"

#include <map>
#include <string>

#include "http/HttpMacros.h"


namespace ossfs
{


// method
const std::string HttpRequest::OPTIONS = "OPTIONS";
const std::string HttpRequest::HEAD = "HEAD";
const std::string HttpRequest::GET = "GET";
const std::string HttpRequest::POST = "POST";
const std::string HttpRequest::PUT = "PUT";
const std::string HttpRequest::DELETE = "DELETE";
const std::string HttpRequest::TRACE = "TRACE";
const std::string HttpRequest::CONNECT = "CONNECT";



HttpRequest::HttpRequest()
{
    _version = HTTP_VERSION_11;
}

HttpRequest::~HttpRequest()
{

}

bool
HttpRequest::hasParameter(
    const std::string &paramName
) const
{
    std::map<std::string, std::string>::const_iterator it;

    it = _params.find(paramName);

    return (_params.end() == it) ? false : true;
}

void
HttpRequest::setParameter(
    const std::string &name,
    const std::string &value
)
{
    _params[name] = value;
}

std::string
HttpRequest::getParameter(
    const std::string &name
) const
{
    std::map<std::string, std::string>::const_iterator it;

    it = _params.find(name);

    return (_params.end() == it) ? "" : (it->second);
}

bool
HttpRequest::hasHeader(
    const std::string &name
) const
{
    std::map<std::string, std::string>::const_iterator it;

    it = _headers.find(name);

    return (_headers.end() == it) ? false : true;
}

void
HttpRequest::setHeader(
    const std::string &name,
    const std::string &value
)
{
    _headers[name] = value;
}

std::string
HttpRequest::getHeader(
    const std::string &name
) const
{
    std::map<std::string, std::string>::const_iterator it;

    it = _headers.find(name);

    return (_headers.end() == it) ? "" : (it->second);
}

bool
HttpRequest::parseFromString(
    const std::string &data
)
{

}

bool
HttpRequest::serializeToString(
    std::string *pData
) const
{

}


}


