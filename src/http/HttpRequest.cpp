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

// version
const std::string HTTP_VERSION_11 = "HTTP/1.1";


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
    return true;
}

bool
HttpRequest::serializeToString(
    std::string *data
) const
{
    if (NULL == data) {
        return false;
    }

    // uri

    std::string furi = _uri;

    if (!_params.empty()) {
        furi += HTTP_PARAM_LEADER_STR;
    }

    for (std::map<std::string, std::string>::const_iterator it =
             _params.begin(); it != _params.end();) {
        furi += it->first + HTTP_NAME_VALUE_SEPARATOR_STR + it->second;

        if ((++it) != _params.end()) {
            furi += HTTP_PARAM_SEPARATOR_STR;
        }
    }

    // request line

    std::string requestLine = _method + HTTP_REQUEST_LINE_SEPARATOR_STR
                              + furi + HTTP_REQUEST_LINE_SEPARATOR_STR
                              + _version + HTTP_CRLF;

    // headers

    std::string headers;

    for (std::map<std::string, std::string>::const_iterator it =
             _headers.begin(); it != _headers.end(); ++it) {
        headers += it->first + HTTP_NAME_VALUE_SEPARATOR_STR
                   + it->second + HTTP_CRLF;
    }

    // total request

    *data = requestLine + headers + HTTP_CRLF + _body;

    return true;
}


}


