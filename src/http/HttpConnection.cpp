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
#include "http/HttpMacros.h"
#include "net/TcpSocket.h"
#include "net/SocketAddress.h"

#include "log/log.h"
#include "util/util.h"

#define HTTP_READ_BUFFER_SIZE   512

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
    remote.setAddress(*((struct sockaddr_in *)(res->ai_addr)));

    freeaddrinfo(res);
    res = NULL;

    // create socket
    rv = _sock.socket();

    if (-1 == rv) {
        ERROR_LOG("create socket error");
        return -1;
    }

    // set options

    rv = _sock.disableNagle();

    if (-1 == rv) {
        ERROR_LOG("disable Nagle on socket error");
        return -1;
    }

    rv = _sock.disableLinger();

    if (-1 == rv) {
        ERROR_LOG("disable Linger on socket error");
        return -1;
    }

    // do connect

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
    if (NULL == response) {
        FATAL_LOG("null pointer");
        return -1;
    }

    // one more byte for null
    char buf[HTTP_READ_BUFFER_SIZE];

    std::string recvd;

    int rv = 0;

    int readn = 0;
    int idx = 0;
    int pos = 0;

    // read http head

    for (; ;) {
        rv = _sock.read(buf, HTTP_READ_BUFFER_SIZE);

        if (-1 == rv) {
            if (EINTR == _sock.getErrNo()) {
                continue;
            }

            return -1;
        }

        if (0 == rv) {
            DEBUG_LOG("http connection closed by %s", _host.c_str());
            return -1;
        }

        readn = rv;
        recvd.append(buf, readn);

        // the whole http head was read?

        pos = recvd.find(HTTP_CRLF HTTP_CRLF);

        if (pos != std::string::npos) {
            // whole head read
            break;
        }
    }

    idx = pos + strlen(HTTP_CRLF HTTP_CRLF);

    // parse head

    if (!response->parseHeaderFromString(recvd.substr(0, idx))) {
        ERROR_LOG("parse http packet head failed");
        return -1;
    }

    // read content
    std::string strLen = response->getHeader(HTTP_CONTENT_LENGTH);

    if (strLen.empty()) {
        return 0;
    }

    int contentLen = util::conv<int, std::string>(strLen);

    char *content = new char[contentLen];

    // copy content already read in "rcvd" to "content"
    int read = recvd.length() - idx;

    memcpy(content, recvd.c_str() + idx, read);

    int toread = contentLen - read;

    rv = _sock.readn(content, toread);

    if (rv != toread) {
        ERROR_LOG("read content failed");

        delete [] content;
        content = NULL;

        return -1;
    }

    response->setBody(content, contentLen);

    delete [] content;
    content = NULL;

    return 0;
}

void
HttpConnection::close()
{
    _sock.close();
}



}  // namespace ossfs

