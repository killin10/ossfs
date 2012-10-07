/*
 * @file HttpConnection.cpp
 * @brief A tcp connection running http protocol.
 *
 * @version 1.0
 * @date Wed Oct  3 21:17:43 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "http/HttpConnection.h"

#include <string.h>

#include <string>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "net/TcpSocket.h"
#include "net/SocketAddress.h"

#include "log/log.h"

namespace ossfs
{


HttpConnection::HttpConnection()
{

}

HttpConnection::HttpConnection(const std::string &host)
{
    _host = host;
}

HttpConnection::~HttpConnection()
{
    close();
}

int
HttpConnection::connect()
{
    int rv = 0;

    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    struct addrinfo *res = NULL;

    std::string service = "http";

    rv = getaddrinfo(_host.c_str(), service.c_str(), &hints, &res);

    if (0 != rv) {
        if (EAI_SYSTEM == rv) {
            ERROR_LOG("getaddrinfo error, %s", strerror(errno));

        } else {
            ERROR_LOG("getaddrinfo error, %s", gai_strerror(errno));
        }

        return -1;
    }

    SocketAddress remote;
    remote.setAddress((struct sockaddr_in *)(res->ai_addr));

    freeaddrinfo(res);
    res = NULL;

    return _sock.connect(remote);
}

int
HttpConnection::connect(const std::string &host)
{
    _host = host;

    return connect();
}

int
HttpConnection::sendRequest(const HttpRequest &request)
{
    std::string data;

    if (!request.serializeToString(&data)) {
        ERROR_LOG("serialize http request to string failed");
        return -1;
    }

    int rv = 0;

    rv = _sock.writen(data.c_str(), data.length());

    if (data.length() != rv) {
        ERROR_LOG("writen error whilst sending http request");
        return -1;
    }

    return 0;
}

int
HttpConnection::recvResponse(HttpResponse *response)
{
    return 0;
}

void
HttpConnection::close()
{
    _sock.close();
}



}  // namespace ossfs

