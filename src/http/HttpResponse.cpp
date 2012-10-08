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

#include <string>
#include <map>


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

const std::map<int, std::string> HttpResponse::REASON_PHRASES = {
    {100, "Continue"},
    {101, "Switching Protocols"},
    {200, "OK"},
    {201, "Created"},
    {202, "Accepted"},
    {203, "Non-Authoritative Information"},
    {204, "No Content"},
    {205, "Reset Content"},
    {206, "Partial Content"},
    {300, "Multiple Choices"},
    {301, "Moved Permanently"},
    {302, "Found"},
    {303, "See Other"},
    {304, "Not Modified"},
    {305, "Use Proxy"},
    {307, "Temporary Redirect"},
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {402, "Payment Required"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {405, "Method Not Allowed"},
    {406, "Not Acceptable"},
    {407, "Proxy Authentication Required"}
};



}  // namespace ossfs

