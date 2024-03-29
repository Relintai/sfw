//--STRIP
#ifndef SOCKET_H
#define SOCKET_H
//--STRIP

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

//--STRIP
#include "inet_address.h"
//--STRIP

class Socket {
public:
	void create_net_socket();
	void create(int family);
	void close_socket();

	int connect(const InetAddress &address);
	int bind_address(const InetAddress &address);
	int listen();
	int accept(Socket *sock);

	int close_write();

	int read(char *buffer, uint64_t len);
	int send(const char *buffer, uint64_t len);

	bool is_self_connect();

	void set_tcp_nodelay(bool on);
	void set_reuse_addr(bool on);
	int set_reuse_port(bool on);
	void set_keep_alive(bool on);

	int set_non_block();
	int set_close_on_exit();

	int get_error();

	struct sockaddr_in6 get_local_addr(int *r_err = NULL);
	struct sockaddr_in6 get_peer_addr(int *r_err = NULL);

	static int global_init();

	Socket();
	Socket(int socketFD, const InetAddress &address);
	~Socket();

	int _socket;
	InetAddress _address;
};

//--STRIP
#endif // SOCKET_H
//--STRIP
