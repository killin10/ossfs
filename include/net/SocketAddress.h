/*
 * @file SocketAddress.h
 * @brief Socket address object.
 *
 * @version 1.0
 * @date Sun Sep 30 21:47:54 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef net_SocketAddress_H_
#define net_SocketAddress_H_

#include <string>

#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace ossfs
{


class SocketAddress
{
public:
    SocketAddress();

    SocketAddress(const std::string &ip, uint16_t port);

    ~SocketAddress();

    inline void setAddress(const std::string &ip, uint16_t port);

    void setAddress(const struct sockaddr_in &sa);

    bool getAddress(struct sockaddr_in *sa) const;

    inline void setIp(const std::string &ip);

    inline void setPort(uint16_t port);

    inline std::string getIp() const;

    inline uint16_t getPort() const;

private:
    std::string _ip;
    uint16_t _port;
};


void
SocketAddress::setAddress(const std::string &ip, uint16_t port)
{
    _ip = ip;
    _port = port;
}

void
SocketAddress::setIp(const std::string &ip)
{
    _ip = ip;
}

void
SocketAddress::setPort(uint16_t port)
{
    _port = port;
}

std::string
SocketAddress::getIp() const
{
    return _ip;
}

uint16_t
SocketAddress::getPort() const
{
    return _port;
}


}  // namespace ossfs


#endif  // net_SocketAddress_H_


