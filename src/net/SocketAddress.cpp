/*
 * @file SocketAddress.cpp
 * @brief Socket address object.
 *
 * @version 1.0
 * @date Sun Sep 30 21:58:21 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "net/SocketAddress.h"

#include <string.h>

#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "log/log.h"


#define INET_ADDR_DEFAULT       "0.0.0.0"


namespace ossfs
{


SocketAddress::SocketAddress()
{
    _ip = INET_ADDR_DEFAULT;
    _port = 0;
}

SocketAddress::SocketAddress(const std::string &ip, uint16_t port)
{
    _ip = ip;
    _port = port;
}

SocketAddress::~SocketAddress()
{

}

void
SocketAddress::setAddress(const struct sockaddr_in &sa)
{
    _port = ntohs(sa.sin_port);

    char str[INET_ADDRSTRLEN];

    const char *dst = NULL;
    dst = inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);

    if (NULL == dst) {
        ERROR_LOG("inet_ntop error, %s", strerror(errno));
        _ip = "";

    } else {
        _ip.assign(str, INET_ADDRSTRLEN);
    }
}

bool
SocketAddress::getAddress(struct sockaddr_in *sa) const
{
    memset(sa, 0, sizeof(struct sockaddr_in));

    sa->sin_family = PF_INET;
    sa->sin_port = htons(_port);

    int rv = 0;

    rv = inet_pton(AF_INET, _ip.c_str(), &(sa->sin_addr));

    if (-1 == rv) {
        ERROR_LOG("inet_pton error, %s", strerror(errno));
        return false;
    }

    return true;
}


}  // namespace ossfs


