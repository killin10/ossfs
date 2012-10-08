/*
 * @file HttpResponse.cpp
 * @brief http response packet
 *
 * @version 1.0
 * @date Mon Oct  8 11:41:40 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "http/HttpResponse.h"

#include <string.h>

#include <string>
#include <map>

#include "http/HttpMacros.h"

#include "log/log.h"
#include "util/util.h"


namespace ossfs
{


const int HttpResponse::SC_CONTINUE = 100;
const int HttpResponse::SC_SWITCHING_PROTOCOLS = 101;
const int HttpResponse::SC_OK = 200;
const int HttpResponse::SC_CREATED = 201;
const int HttpResponse::SC_ACCEPTED = 202;
const int HttpResponse::SC_NON_AUTHORITATIVE_INFORMATION = 203;
const int HttpResponse::SC_NO_CONTENT = 204;
const int HttpResponse::SC_RESET_CONTENT = 205;
const int HttpResponse::SC_PARTIAL_CONTENT = 206;
const int HttpResponse::SC_MULTIPLE_CHOICES = 300;
const int HttpResponse::SC_MOVED_PERMANENTLY = 301;
const int HttpResponse::SC_FOUND = 302;
const int HttpResponse::SC_SEE_OTHER = 303;
const int HttpResponse::SC_NOT_MODIFIED = 304;
const int HttpResponse::SC_USE_PROXY = 305;
const int HttpResponse::SC_TEMPORARY_REDIRECT = 307;
const int HttpResponse::SC_BAD_REQUEST = 400;
const int HttpResponse::SC_UNAUTHORIZED = 401;
const int HttpResponse::SC_PAYMENT_REQUIRED = 402;
const int HttpResponse::SC_FORBIDDEN = 403;
const int HttpResponse::SC_NOT_FOUND = 404;
const int HttpResponse::SC_METHOD_NOT_ALLOWED = 405;
const int HttpResponse::SC_NOT_ACCEPTABLE = 406;
const int HttpResponse::SC_PROXY_AUTHENTICATION_REQUIRED = 407;
const int HttpResponse::SC_REQUEST_TIMEOUT = 408;
const int HttpResponse::SC_CONFLICT = 409;
const int HttpResponse::SC_GONE = 410;
const int HttpResponse::SC_LENGTH_REQUIRED = 411;
const int HttpResponse::SC_PRECONDITION_FAILED = 412;
const int HttpResponse::SC_REQUEST_TOO_LONG = 413;
const int HttpResponse::SC_REQUEST_URI_TOO_LONG = 414;
const int HttpResponse::SC_UNSUPPORTED_MEDIA_TYPE = 415;
const int HttpResponse::SC_REQUESTED_RANGE_NOT_SATISFIABLE = 416;
const int HttpResponse::SC_EXPECTATION_FAILED = 417;
const int HttpResponse::SC_INTERNAL_SERVER_ERROR = 500;
const int HttpResponse::SC_NOT_IMPLEMENTED = 501;
const int HttpResponse::SC_BAD_GATEWAY = 502;
const int HttpResponse::SC_SERVICE_UNAVAILABLE = 503;
const int HttpResponse::SC_GATEWAY_TIMEOUT = 504;
const int HttpResponse::SC_HTTP_VERSION_NOT_SUPPORTED = 505;


static std::map<int, std::string>::value_type mapInit[] = {
    std::map<int, std::string>::value_type(100, "Continue"),
    std::map<int, std::string>::value_type(101, "Switching Protocols"),
    std::map<int, std::string>::value_type(200, "OK"),
    std::map<int, std::string>::value_type(201, "Created"),
    std::map<int, std::string>::value_type(202, "Accepted"),
    std::map<int, std::string>::value_type(
        203,
        "Non-Authoritative Information"
    ),
    std::map<int, std::string>::value_type(204, "No Content"),
    std::map<int, std::string>::value_type(205, "Reset Content"),
    std::map<int, std::string>::value_type(206, "Partial Content"),
    std::map<int, std::string>::value_type(300, "Multiple Choices"),
    std::map<int, std::string>::value_type(301, "Moved Permanently"),
    std::map<int, std::string>::value_type(302, "Found"),
    std::map<int, std::string>::value_type(303, "See Other"),
    std::map<int, std::string>::value_type(304, "Not Modified"),
    std::map<int, std::string>::value_type(305, "Use Proxy"),
    std::map<int, std::string>::value_type(307, "Temporary Redirect"),
    std::map<int, std::string>::value_type(400, "Bad Request"),
    std::map<int, std::string>::value_type(401, "Unauthorized"),
    std::map<int, std::string>::value_type(402, "Payment Required"),
    std::map<int, std::string>::value_type(403, "Forbidden"),
    std::map<int, std::string>::value_type(404, "Not Found"),
    std::map<int, std::string>::value_type(405, "Method Not Allowed"),
    std::map<int, std::string>::value_type(406, "Not Acceptable"),
    std::map<int, std::string>::value_type(
        407,
        "Proxy Authentication Required"
    ),
    std::map<int, std::string>::value_type(408, "Request Timeout"),
    std::map<int, std::string>::value_type(409, "Conflict"),
    std::map<int, std::string>::value_type(410, "Gone"),
    std::map<int, std::string>::value_type(411, "Length Required"),
    std::map<int, std::string>::value_type(412, "Precondition Failed"),
    std::map<int, std::string>::value_type(413, "Request Entity Too Large"),
    std::map<int, std::string>::value_type(414, "Request-URI Too Long"),
    std::map<int, std::string>::value_type(415, "Unsupported Media Type"),
    std::map<int, std::string>::value_type(
        416,
        "Requested Range Not Satisfiable"
    ),
    std::map<int, std::string>::value_type(417, "Expectation Failed"),
    std::map<int, std::string>::value_type(500, "Internal Server Error"),
    std::map<int, std::string>::value_type(501, "Not Implemented"),
    std::map<int, std::string>::value_type(502, "Bad Gateway"),
    std::map<int, std::string>::value_type(503, "Service Unavailable"),
    std::map<int, std::string>::value_type(504, "Gateway Timeout"),
    std::map<int, std::string>::value_type(505, "HTTP Version Not Supported")
};

const std::map<int, std::string> HttpResponse::REASON_PHRASES(
    mapInit, mapInit + 40
);

HttpResponse::HttpResponse()
{
    _statusCode = 0;
}

HttpResponse::~HttpResponse()
{

}

int
HttpResponse::getContentLength() const
{
    std::string strLen = getHeader(HTTP_CONTENT_LENGTH);

    if (strLen.empty()) {
        return -1;
    }

    return util::conv<int, std::string>(strLen);
}

void
HttpResponse::setContentLength(int len)
{
    setHeader(HTTP_CONTENT_LENGTH, util::conv<std::string, int>(len));
}

bool
HttpResponse::hasHeader(const std::string &name) const
{
    std::map<std::string, std::string>::const_iterator it;

    it = _headers.find(name);

    return (_headers.end() == it) ? false : true;
}

void
HttpResponse::setHeader(
    const std::string &name,
    const std::string &value
)
{
    _headers[name] = value;
}

std::string
HttpResponse::getHeader(const std::string &name) const
{
    std::map<std::string, std::string>::const_iterator it;

    it = _headers.find(name);

    return (_headers.end() == it) ? "" : (it->second);
}

bool
HttpResponse::parseStatusLine(const std::string &sl)
{
    int inLineIdx = 0;
    int space = 0;

    // protocol version
    space = sl.find(HTTP_STATUS_LINE_SEPARATOR_STR, inLineIdx);

    if (std::string::npos == space) {
        ERROR_LOG("parse http version string failed");
        return false;
    }

    _version = sl.substr(0, space);

    inLineIdx = space + 1;

    // status code
    space = sl.find(HTTP_STATUS_LINE_SEPARATOR_STR, inLineIdx);

    if (std::string::npos == space) {
        ERROR_LOG("parse status code failed");
        return false;
    }

    _statusCode = util::conv<int, std::string>(
                      sl.substr(inLineIdx, space - inLineIdx)
                  );

    inLineIdx = space + 1;

    // reason phrase

    _reasonPhrase = sl.substr(inLineIdx);

    return true;
}

bool
HttpResponse::parseNameValuePair(const std::string &pair)
{
    int colon = 0;

    colon = pair.find(HTTP_NAME_VALUE_SEPARATOR_STR);

    if (std::string::npos == colon) {
        ERROR_LOG("parse http name-value pair failed");
        return false;
    }

    std::string name = util::trim(pair.substr(0, colon));
    std::string value = util::trim(pair.substr(colon + 1));

    _headers[name] = value;

    return true;
}


bool
HttpResponse::parseHeaderFromString(const std::string &header)
{
    int crlf = 0;
    int idx = 0;

    // status line

    crlf = header.find(HTTP_CRLF, idx);

    if (std::string::npos == crlf) {
        ERROR_LOG("parse status line from response failed");
        return false;
    }

    std::string statusLine = header.substr(idx, crlf - idx);

    if (!parseStatusLine(statusLine)) {
        ERROR_LOG("parse status line failed");
        return false;
    }

    idx = crlf + strlen(HTTP_CRLF);

    // headers

    std::string line;

    for (; ;) {
        crlf = header.find(HTTP_CRLF, idx);

        if (std::string::npos == crlf) {
            ERROR_LOG("parse name-value pair from response failed");
            return false;
        }

        line = header.substr(idx, crlf - idx);

        if (line.empty()) {
            break;
        }

        if (!parseNameValuePair(line)) {
            ERROR_LOG("parse name-value pair failed");
            return false;
        }

        idx = crlf + strlen(HTTP_CRLF);
    }

    return true;
}

bool
HttpResponse::parseFromString(const std::string &data)
{

}

bool
HttpResponse::parseFromBuffer(const char *buf, int len)
{

}

bool
HttpResponse::serializeToString(std::string *data) const
{

}



}  // namespace ossfs

