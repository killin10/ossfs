/*
 * @file HttpResponse.h
 * @brief http response packet
 *
 * @version 1.0
 * @date Sat Sep 15 16:49:44 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef http_HttpResponse_H_
#define http_HttpResponse_H_

#include <string>
#include <map>


namespace ossfs
{


class HttpResponse
{
public:
    static const int SC_CONTINUE;
    static const int SC_SWITCHING_PROTOCOLS;
    static const int SC_OK;
    static const int SC_CREATED;
    static const int SC_ACCEPTED;
    static const int SC_NON_AUTHORITATIVE_INFORMATION;
    static const int SC_NO_CONTENT;
    static const int SC_RESET_CONTENT;
    static const int SC_PARTIAL_CONTENT;
    static const int SC_MULTIPLE_CHOICES;
    static const int SC_MOVED_PERMANENTLY;
    static const int SC_FOUND;
    static const int SC_SEE_OTHER;
    static const int SC_NOT_MODIFIED;
    static const int SC_USE_PROXY;
    static const int SC_TEMPORARY_REDIRECT;
    static const int SC_BAD_REQUEST;
    static const int SC_UNAUTHORIZED;
    static const int SC_PAYMENT_REQUIRED;
    static const int SC_FORBIDDEN;
    static const int SC_NOT_FOUND;
    static const int SC_METHOD_NOT_ALLOWED;
    static const int SC_NOT_ACCEPTABLE;
    static const int SC_PROXY_AUTHENTICATION_REQUIRED;
    static const int SC_REQUEST_TIMEOUT;
    static const int SC_CONFLICT;
    static const int SC_GONE;
    static const int SC_LENGTH_REQUIRED;
    static const int SC_PRECONDITION_FAILED;
    static const int SC_REQUEST_TOO_LONG;
    static const int SC_REQUEST_URI_TOO_LONG;
    static const int SC_UNSUPPORTED_MEDIA_TYPE;
    static const int SC_REQUESTED_RANGE_NOT_SATISFIABLE;
    static const int SC_EXPECTATION_FAILED;
    static const int SC_INTERNAL_SERVER_ERROR;
    static const int SC_NOT_IMPLEMENTED;
    static const int SC_BAD_GATEWAY;
    static const int SC_SERVICE_UNAVAILABLE;
    static const int SC_GATEWAY_TIMEOUT;
    static const int SC_HTTP_VERSION_NOT_SUPPORTED;

public:
    HttpResponse();

    virtual ~HttpResponse();

    bool parseFromString(const std::string &data);

    bool serializeToString(std::string *data) const;

protected:
    std::string _version;
    std::string _statusCode;
    std::string _reasonPhrase;

    std::map<std::string, std::string> _headers;

    std::string _body;
};


}



#endif  // http_HttpResponse_H_

