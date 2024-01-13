//Based on:

// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

// Taken from Muduo and modified
// Copyright 2016, Tao An.  All rights reserved.
// https://github.com/an-tao/trantor
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Tao An

#ifndef INET_ADDRESS_H
#define INET_ADDRESS_H

//On windows link to ws2_32

//--STRIP
#include "int_types.h"
//--STRIP

#if defined(_WIN64) || defined(_WIN32)
#include <ws2tcpip.h>
using sa_family_t = unsigned short;
using in_addr_t = uint32_t;
using uint16_t = unsigned short;
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif

//--STRIP
#include "int_types.h"
#include "core/ustring.h"
//--STRIP

class InetAddress {
public:
	sa_family_t family() const;

	String to_ip() const;
	String to_ip_port() const;

	uint16_t to_port() const;

	bool is_ip_v6() const;
	bool is_intranet_ip() const;
	bool is_loopback_ip() const;

	const struct sockaddr *get_sock_addr() const;

	void set_sock_addr_inet6(const struct sockaddr_in6 &addr6);

	uint32_t ip_net_endian() const;
	const uint32_t *ip6_net_endian() const;

	uint16_t port_net_endian() const;

	void set_port_net_endian(uint16_t port);

	inline bool is_unspecified() const;

	InetAddress(uint16_t port = 0, bool loopbackOnly = false, bool ipv6 = false);
	InetAddress(const String &ip, uint16_t port, bool ipv6 = false);

	explicit InetAddress(const struct sockaddr_in &addr) {
		_addr = addr;
		_is_unspecified = false;
	}

	explicit InetAddress(const struct sockaddr_in6 &addr) {
		_addr6 = addr;
		_is_ip_v6 = true;
		_is_unspecified = false;
	}

private:
	union {
		struct sockaddr_in _addr;
		struct sockaddr_in6 _addr6;
	};

	bool _is_ip_v6;
	bool _is_unspecified;
};

#endif
