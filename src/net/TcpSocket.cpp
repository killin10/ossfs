/*
 * @file TcpSocket.cpp
 * @brief Tcp socket object.
 *
 * @version 1.0
 * @date Tue Oct  2 21:39:31 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "net/TcpSocket.h"

#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/uio.h>

#include "log/log.h"

namespace ossfs
{


TcpSocket::TcpSocket()
{
    _sock = -1;
    _errno = 0;
}

TcpSocekt::TcpSocket(int sock)
{
    _sock = sock;
    _errno = 0;
}

TcpSocket::~TcpSocket()
{
    close();

    _errno = 0;
}

int
TcpSocket::socket()
{
    int rv = 0;

    rv = ::socket(PF_INET, SOCK_STREAM, 0);

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("socket error, %s", strerror(_errno));
        return -1;
    }

    _sock = rv;

    return 0;
}

int
TcpSocket::setNonblock()
{
    int value = 0;

    int rv = 0;

    rv = ::fcntl(_sock, F_GETFL);

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("fcntl(F_GETFL) error, %s", strerror(_errno));
        return -1;
    }

    value = rv | O_NONBLOCK;

    rv = ::fcntl(_sock, F_SETFL, value);

    if (-1 == rt) {
        _errno = errno;

        ERROR_LOG("fcntl(F_SETFL) error, %s", strerror(_errno));
        return -1;
    }

    return 0;
}

int
TcpSocket::setKeepAlive()
{
    int value = 1;

    int rv = 0;

    rv = ::setsockopt(
             _sock,
             SOL_SOCKET,
             SO_KEEPALIVE,
             (const void *) &value,
             sizeof(int)
         );

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("setsockopt(SO_KEEPALIVE) error, %s", strerror(_errno));
        return -1;
    }

    return 0;
}

int
TcpSocket::enableReuseAddr()
{
    int value = 1;

    int rv = 0;

    rv = ::setsockopt(
             _sock,
             SOL_SOCKET,
             SO_REUSEADDR,
             (const void *) &value,
             sizeof(int)
         );

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("setsockopt(SO_REUSEADDR) error, %s", strerror(_errno));
        return -1;
    }

    return 0;
}

int
TcpSocket::disableLinger()
{
    struct linger ling = {0, 0};

    int rv = 0;

    rv = ::setsockopt(
             _sock,
             SOL_SOCKET,
             SO_LINGER,
             &ling,
             sizeof(struct linger)
         );

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("setsockopt(SO_LINGER) error, %s", strerror(_errno));
        return -1;
    }

    return 0;
}

int
TcpSocket::disableNagle()
{
    int value = 1;

    int rv = 0;

    rv = ::setsockopt(
             _sock,
             IPPROTO_TCP,
             TCP_NODELAY,
             (const void *) &value,
             sizeof(int)
         );

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("setsockopt(TCP_NODELAY) error, %s", strerror(_errno));
        return -1;
    }

    return 0;
}

int
TcpSocket::bind(const SocketAddress &sa)
{
    int rv = 0;

    struct sockaddr_in addr;

    if (!sa.getAddress(&addr)) {
        _errno = 0;

        ERROR_LOG("get socket address error, ip %s, port %" PRIu16,
                  sa.getIp().c_str(), sa.getPort());

        retur - 1;
    }

    rv = ::bind(
             _sock,
             (const struct sockaddr *) &addr,
             sizeof(struct sockaddr)
         );

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("bind error, %s, ip %s, port %" PRIu16,
                  strerror(_errno),
                  sa.getIp().c_str(),
                  sa.getPort()
                 );

        return -1;
    }

    return 0;
}

int
TcpSocket::listen(int qs)
{
    int rv = 0;

    rv = ::listen(_sock, qs);

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("listen error, %s", strerror(_errno));
        return -1;
    }

    return 0;
}

int
TcpSocket::accept(SocketAddress *sa)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);

    int rv = 0;

    rv = ::accept(_sock, (struct sockaddr *) &addr, &len);

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("accept error, %s", strerror(_errno));
        return -1;
    }

    int connFd = rv;

    if (NULL != sa) {
        sa->setAddress(addr);
    }

    return connFd;
}

int
TcpSocket::connect(const SocketAddress &sa)
{
    _remoteAddr = sa;

    return connect();
}

int
TcpSocket::connect()
{
    int rv = 0;

    struct sockaddr_in addr;

    if (!_remoteAddr.getAddress(&addr)) {
        _errno = 0;

        ERROR_LOG("get socket address error, ip %s, port %" PRIu16,
                  _remoteAddr.getIp().c_str(),
                  _remoteAddr.getPort()
                 );
        return -1;
    }

    rv = ::connect(
             _sock,
             (const sockaddr *) &addr,
             sizeof(struct sockaddr_in)
         );

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("connect error, %s, ip %s, port %" PRIu16,
                  strerror(_errno),
                  _remoteAddr.getIp().c_str(),
                  _remoteAddr.getPort()
                 );

        return -1;
    }

    return 0;
}

int
TcpSocket::read(char *buf, int len)
{
    if (NULL == buf) {
        _errno = 0;

        FATAL_LOG("null pointer")
        return -1;
    }

    int rv = 0;

    rv = ::read(_sock, buf, len);

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("read error, %s", strerror(_errno));

        return -1;
    }

    return rv;
}

int
TcpSocket::readn(char *buf, int len)
{
    if (NULL == buf) {
        _errno = 0;

        FATAL_LOG("null pointer");
        return -1;
    }

    int rv = 0;

    char *vptr = buf;
    int readn = 0;

    for (; readn < len;) {
        rv = ::read(_sock, vptr, len - readn);

        if (-1 == rv) {
            if (EINTR == errno) {
                continue;
            }

            // error
            _errno = errno;

            ERROR_LOG("read error, %s", strerror(_errno));
            return readn;

        } else if (0 == rv) {
            DEBUG_LOG("EOF encountered, remote ip %s, port %" PRIu16
                      _remoteAddr.getIp().c_str(),
                      _remoteAddr.getPort()
                     );
            return readn;
        }

        readn += rv;
        vptr += rv;
    }

    return readn;
}

int
TcpSocket::write(const char *buf, int len)
{
    if (NULL == buf) {
        _errno = 0;

        FATAL_LOG("null pointer");
        return -1;
    }

    int rv = 0;

    rv = ::write(_sock, buf, len);

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("write error, %s", strerror(_errno));
        return -1;
    }

    return rv;
}

int
TcpSocket::writen(const char *buf, int len)
{
    if (NULL == buf) {
        _errno = 0;

        FATAL_LOG("null pointer");
        return -1;
    }

    int rv = 0;

    const char *vptr = buf;
    int writen = 0;

    for (; writen < len;) {
        rv = ::write(_sock, vptr, len - writen);

        if (-1 == rv) {
            if (EINTR == errno) {
                continue;
            }

            // error
            _errno = errno;

            ERROR_LOG("write error, %s", strerror(_errno));
            return -1;
        }

        vptr += rv;
        writen += rv;
    }

    return writen;
}

int
TcpSocket::writev(const struct iovec *iov, int iovcnt)
{
    if (NULL == iov) {
        _errno = 0;

        FATAL_LOG("null pointer");
        return -1;
    }

    int rv = 0;

    rv = ::writev(_sock, iov, iovcnt);

    if (-1 == rv) {
        _errno = errno;

        ERROR_LOG("writev error, %s", strerror(_errno));
        return -1;
    }

    return rv;
}


void
TcpSocket::close()
{
    if (-1 == _sock) {
        return ;
    }

    int rv = 0;

    rv = ::close(_sock);

    if (-1 == rv) {
        _errno = errno;

        WARN_LOG("close error, %s", strerror(_errno));

        return ;
    }

    _sock = -1;
}


}  // namespace ossfs


