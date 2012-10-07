/*
 * @file TcpSocket.h
 * @brief Tcp socket object.
 *
 * @version 1.0
 * @date Tue Oct  2 21:11:07 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef net_TcpSocket_H_
#define net_TcpSocket_H_


#include "net/SocketAddress.h"


namespace ossfs
{


class TcpSocket
{
public:
    TcpSocket();

    explicit TcpSocket(int sock);

    ~TcpSocket();

    int socket();

    int setNonblock();

    int setKeepAlive();

    int enableReuseAddr();

    int disableLinger();

    int disableNagle();

    int bind(const SocketAddress &sa);

    int listen(int qs);

    int accept(SocketAddress *sa);

    int connect(const SocketAddress &sa);

    int connect();

    int read(char *buf, int len);

    int readn(char *buf, int len);

    int write(const char *buf, int len);

    int writen(const char *buf, int len);

    int writev(const struct iovec *iov, int iovcnt);

    void close();

    inline void setRemoteAddress(const SocketAddress &sa);

    inline int getSockFd() const;

    inline int getErrNo() const;

private:
    int _sock;
    int _errno;

    SocketAddress _localAddr;
    SocketAddress _remoteAddr;
};


int
TcpSocket::getSockFd() const
{
    return _sock;
}

int
TcpSocket::getErrNo() const
{
    return _errno;
}

void
TcpSocket::setRemoteAddress(const SocketAddress &sa)
{
    _remoteAddr = sa;
}


}  // namespace ossfs


#endif  // net_TcpSocket_H_

