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

    static const std::map<int, std::string> REASON_PHRASES;

public:
    HttpResponse();

    virtual ~HttpResponse();

    inline void setVersion(const std::string &version);

    inline std::string getVersion() const;

    inline void setStatusCode(int sc);

    inline int getStatusCode() const;

    inline void setReasonPhrase(const std::string &rp);

    inline std::string getReasonPhrase() const;

    bool hasHeader(const std::string &name) const;

    void setHeader(const std::string &name, const std::string &value);

    std::string getHeader(const std::string &name) const;

    inline void setBody(const std::string &body);

    inline void setBody(const char *buf, int len);

    inline void appendBody(const std::string &data);

    inline void appendBody(const char *buf, int len);

    inline const std::string &getBody() const;

    bool parseFromString(const std::string &data);

    bool parseFromBuffer(const char *buf, int len);

    bool serializeToString(std::string *data) const;

protected:
    std::string _version;
    int _statusCode;
    std::string _reasonPhrase;

    std::map<std::string, std::string> _headers;

    std::string _body;
};


void
HttpResponse::setVersion(const std::string &version)
{
    _version = version;
}

std::string
HttpResponse::getVersion() const
{
    return _version;
}

void
HttpResponse::setStatusCode(int sc)
{
    _statusCode = sc;
}

int
HttpResponse::getStatusCode() const
{
    return _statusCode;
}

void
HttpResponse::setReasonPhrase(const std::string &rp)
{
    _reasonPhrase = rp;
}

std::string
HttpResponse::getReasonPhrase() const
{
    return _reasonPhrase;
}

void
HttpResponse::setBody(const std::string &body)
{
    _body = body;
}

void
HttpResponse::setBody(const char *buf, int len)
{
    _body.assign(buf, len);
}

void
HttpResponse::appendBody(const std::string &data)
{
    _body.append(data);
}

void
HttpResponse::appendBody(const char *buf, int len)
{
    _body.append(buf, len);
}

const std::string &
HttpResponse::getBody() const
{
    return _body;
}


}



#endif  // http_HttpResponse_H_

