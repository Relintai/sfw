#ifndef SOCKET_H
#define SOCKET_H

//Based on:

/**
 *
 *  Socket.h
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

#include "error_macros.h"
#include <string.h>

#ifndef _WIN32
#include <unistd.h>
#endif
#include <fcntl.h>

#include "inet_address.h"

class Socket
{
public:
    void create_net_socket();
    void create(int family);
    void set_non_block_and_close_on_exit();
    int get_error();
    int connect(const InetAddress &address);
    bool is_self_connect();
    void bind_address(const InetAddress &address);
    void listen();
    int accept(Socket *sock);
    void close_write();
    int read(char *buffer, uint64_t len);
    int send(const char *buffer, uint64_t len);

    void set_tcp_nodelay(bool on);
    void set_reuse_addr(bool on);
    void set_reuse_port(bool on);
    void set_keep_alive(bool on);

    struct sockaddr_in6 get_local_addr();
    struct sockaddr_in6 get_peer_addr();

    static int global_init();

    Socket();
    Socket(int socketFD, const InetAddress &address);
    ~Socket();

    int _socket;
    InetAddress _address;
};


#endif // SOCKET_H


