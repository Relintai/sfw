#include "socket.h"

//Based on:

/**
 *
 *  Socket.cc
 *  An Tao
 *
 *  Public header file in trantor lib.
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the License file.
 *
 *
 */

#ifndef _WIN32
#include <unistd.h>
#endif
#include <fcntl.h>

///usr/include/asm-generic/errno-base.h
//http://www.virtsync.com/c-error-codes-include-errno
#include<cerrno>

#ifdef _WIN32
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/tcp.h>
#endif

void Socket::create_net_socket()
{
    create(AF_INET);
}

void Socket::create(int family)
{
#ifdef __linux__
    _socket = ::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
#else
    _socket = static_cast<int>(::socket(family, SOCK_STREAM, IPPROTO_TCP));
#endif
}

// taken from muduo
void Socket::set_non_block_and_close_on_exit()
{
#ifdef _WIN32
    // TODO how to set FD_CLOEXEC on windows? is it necessary?
    u_long arg = 1;
    auto ret = ioctlsocket(_socket, (long)FIONBIO, &arg);

    if (ret)
    {
        LOG_ERR("ioctlsocket error");
    }
#else
    // non-block
    int flags = ::fcntl(_socket, F_GETFL, 0);
    flags |= O_NONBLOCK;
    int ret = ::fcntl(_socket, F_SETFL, flags);
    // TODO check

    // close-on-exec
    flags = ::fcntl(_socket, F_GETFD, 0);
    flags |= FD_CLOEXEC;
    ret = ::fcntl(_socket, F_SETFD, flags);
    // TODO check

    (void)ret;
#endif
}

int Socket::get_error()
{
    int optval;

    socklen_t optlen = static_cast<socklen_t>(sizeof optval);

#ifdef _WIN32
    if (::getsockopt(_socket, SOL_SOCKET, SO_ERROR, (char *)&optval, &optlen) < 0)
#else
    if (::getsockopt(_socket, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
#endif
    {
        return errno;
    }
    else
    {
        return optval;
    }
}

int Socket::connect(const InetAddress &addr)
{
    if (addr.is_ip_v6())
    {
        return ::connect(_socket, addr.get_sock_addr(), static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
    }
    else
    {
        return ::connect(_socket, addr.get_sock_addr(), static_cast<socklen_t>(sizeof(struct sockaddr_in)));
    }
}

bool Socket::is_self_connect()
{
    struct sockaddr_in6 localaddr = get_local_addr();
    struct sockaddr_in6 peeraddr = get_peer_addr();

    if (localaddr.sin6_family == AF_INET)
    {
        const struct sockaddr_in *laddr4 = reinterpret_cast<struct sockaddr_in *>(&localaddr);
        const struct sockaddr_in *raddr4 = reinterpret_cast<struct sockaddr_in *>(&peeraddr);
        return laddr4->sin_port == raddr4->sin_port && laddr4->sin_addr.s_addr == raddr4->sin_addr.s_addr;
    }
    else if (localaddr.sin6_family == AF_INET6)
    {
        return localaddr.sin6_port == peeraddr.sin6_port && memcmp(&localaddr.sin6_addr, &peeraddr.sin6_addr, sizeof localaddr.sin6_addr) == 0;
    }
    else
    {
        return false;
    }
}

void Socket::bind_address(const InetAddress &address)
{
    ERR_FAIL_COND(_socket == 0);

    int ret;
    if (address.is_ip_v6())
    {
        ret = ::bind(_socket, address.get_sock_addr(), sizeof(sockaddr_in6));
    }
    else
    {
        ret = ::bind(_socket, address.get_sock_addr(), sizeof(sockaddr_in));
    }

    if (ret != 0)
    {
        RLOG_ERR("Bind address failed:");
        RLOG_ERR(address.to_ip_port());

#ifdef _WIN32
        exit(WSAGetLastError());
#else
        exit(errno);
#endif
    }
}

void Socket::listen()
{
    ERR_FAIL_COND(_socket == 0);

    int ret = ::listen(_socket, SOMAXCONN);
    if (ret < 0)
    {
        RLOG_ERR("listen failed");

        exit(1);
    }
}

int Socket::accept(Socket *sock)
{
    struct sockaddr_in6 addr6;
    memset(&addr6, 0, sizeof(addr6));
    socklen_t size = sizeof(addr6);

#ifdef __linux__
    int connfd = ::accept4(_socket, (struct sockaddr *)&addr6, &size, SOCK_NONBLOCK | SOCK_CLOEXEC);
#else
    int connfd = static_cast<int>(::accept(_socket, (struct sockaddr *)&addr6, &size));
#endif

    if (connfd >= 0)
    {
        sock->_socket = connfd;
        sock->_address.set_sock_addr_inet6(addr6);
#ifndef __linux__
        sock->set_non_block_and_close_on_exit();
#endif
    }

    return connfd;
}

void Socket::close_write()
{
#ifndef _WIN32
    if (::shutdown(_socket, SHUT_WR) < 0)
#else
    if (::shutdown(_socket, SD_SEND) < 0)
#endif
    {
        RLOG_ERR("sockets::shutdownwrite");
    }
}

int Socket::read(char *buffer, uint64_t len)
{
#ifndef _WIN32
    return ::read(_socket, buffer, len);
#else
    return recv(_socket, buffer, static_cast<int>(len), 0);
#endif
}

int Socket::send(const char *buffer, uint64_t len)
{
#ifndef _WIN32
    return write(_socket, buffer, len);
#else
    errno = 0;
    return ::send(_socket, buffer, static_cast<int>(len), 0);
#endif
}

void Socket::set_tcp_nodelay(bool on)
{
#ifdef _WIN32
    char optval = on ? 1 : 0;
#else
    int optval = on ? 1 : 0;
#endif
    ::setsockopt(_socket, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::set_reuse_addr(bool on)
{
#ifdef _WIN32
    char optval = on ? 1 : 0;
#else
    int optval = on ? 1 : 0;
#endif
    ::setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::set_reuse_port(bool on)
{
#ifdef SO_REUSEPORT
#ifdef _WIN32
    char optval = on ? 1 : 0;
#else
    int optval = on ? 1 : 0;
#endif
    int ret = ::setsockopt(_socket, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof optval));

    if (ret < 0 && on)
    {
        RLOG_ERR("SO_REUSEPORT failed.");
    }
#else
    if (on)
    {
        RLOG_ERR("SO_REUSEPORT is not supported.");
    }
#endif
}

void Socket::set_keep_alive(bool on)
{
#ifdef _WIN32
    char optval = on ? 1 : 0;
#else
    int optval = on ? 1 : 0;
#endif
    ::setsockopt(_socket, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof optval));
}

struct sockaddr_in6 Socket::get_local_addr()
{
    struct sockaddr_in6 localaddr;
    memset(&localaddr, 0, sizeof(localaddr));
    socklen_t addrlen = static_cast<socklen_t>(sizeof localaddr);

    if (::getsockname(_socket, static_cast<struct sockaddr *>((void *)(&localaddr)), &addrlen) < 0)
    {
        RLOG_ERR("sockets::getLocalAddr");
    }

    return localaddr;
}

struct sockaddr_in6 Socket::get_peer_addr()
{
    struct sockaddr_in6 peeraddr;
    memset(&peeraddr, 0, sizeof(peeraddr));
    socklen_t addrlen = static_cast<socklen_t>(sizeof peeraddr);

    if (::getpeername(_socket, static_cast<struct sockaddr *>((void *)(&peeraddr)), &addrlen) < 0)
    {
        RLOG_ERR("sockets::getPeerAddr");
    }

    return peeraddr;
}

int Socket::global_init()
{
#ifdef _WIN32
    int r;
    WSADATA wsa_data;

    r = WSAStartup(MAKEWORD(2, 2), &wsa_data);

    return r;
#else
    return 0;
#endif
}

Socket::Socket()
{
    _socket = 0;
}

Socket::Socket(int socketFD, const InetAddress &address)
{
    _socket = socketFD;
    _address = address;
}

Socket::~Socket()
{
    if (_socket >= 0)
    {
#ifndef _WIN32
        close(_socket);
#else
        closesocket(_socket);
#endif
    }
}
