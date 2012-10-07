/*
 * @file HttpConnection.h
 * @brief A tcp connection running http protocol.
 *
 * @version 1.0
 * @date Wed Oct  3 21:08:41 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef http_HttpConnection_H_
#define http_HttpConnection_H_

#include <string>

#include "net/TcpSocket.h"
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"

namespace ossfs
{


class HttpConnection
{
public:
    HttpConnection();

    explicit HttpConnection(const std::string &host);

    ~HttpConnection();

    inline void setHost(const std::string &host);

    int connect();

    int connect(const std::string &host);

    int sendRequest(const HttpRequest &request);

    int recvResponse(HttpResponse *response);

    void close();

private:
    TcpSocket _sock;
    std::string _host;
};

void
HttpConnection::setHost(const std::string &host)
{
    _host = host;
}


}  // namespace ossfs


#endif  // http_HttpConnection_H_


