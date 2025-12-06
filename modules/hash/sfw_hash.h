#ifndef SFW_HASH_H
#define SFW_HASH_H

// Originally from:

// https://github.com/zzo38/freeheromesh/commits/trunk/
// 50e22c8c3008b8b2d610974fdb02029855f1dfba

// Free public domain cryptographic hash library

// Adding the -fwrapv flag might be needed

//#include "sfw.h"
#include "sfwl.h"

class SFWHash {
	enum HashFunc {
		HASH_SHA1 = 0x11,
		HASH_SHA3_512 = 0x14,
		HASH_SHA3_384 = 0x15,
		HASH_SHA3_256 = 0x16,
		HASH_SHA3_224 = 0x17,
		HASH_MD5 = 0xD5,
	};

	void init(HashFunc p_func);
	bool is_initialized() const;

	HashFunc get_hash_func() const;

	int get_hash_length();
	String get_current_hash();

	void hash_string(const String &p_str);
	void hash_buffer(const uint8_t *p_buffer, const int p_length);

	SFWHash();
	~SFWHash();

protected:
	// Tell the length (in bytes) of the hash of the specified algorithm. If
	// it is not implemented, then the result is zero.
	static uint64_t _hash_length(HashFunc alg);

	// Returns a writable stream. If the echo stream is not null, then any
	// data written to the stream is also written to the echo stream. When
	// the stream is closed, the hash (as binary) is written to the out.
	static FILE *_hash_stream(HashFunc alg, FILE *echo, unsigned char *out);

	// Returns a hash (as binary) of the specified data. The returned buffer
	// is allocated by malloc and must be freed by free. (This function is a
	// convenience function implemented in terms of the other two functions.)
	static unsigned char *_hash_buffer(HashFunc alg, const unsigned char *data, int len);

	static ssize_t _hash_write(void *cookie, const char *buf, size_t size);
	static int _hash_close(void *cookie);

	/* Context for the SHA1 hash */
	struct SHA1Context {
		unsigned int state[5];
		unsigned int count[2];
		unsigned char buffer[64];
	};

	typedef unsigned long long u64;

	/*
	** State structure for a SHA3 hash in progress
	*/
	struct SHA3Context {
		union {
			u64 s[25]; /* Keccak state. 5x5 lines of 64 bits each */
			unsigned char x[1600]; /* ... or 1600 bytes */
		} u;
		unsigned nRate; /* Bytes of input accepted per Keccak iteration */
		unsigned nLoaded; /* Input bytes loaded into u.x[] so far this cycle */
		unsigned ixMask; /* Insert next input into u.x[nLoaded^ixMask]. */
	};

	typedef struct {
		uint8_t chunk[64];
		uint64_t len;
		uint32_t a, b, c, d;
	} MD5Context;

	typedef struct {
		union {
			SHA1Context sha1;
			SHA3Context sha3;
			MD5Context md5;
		};
		long long alg;
		FILE *echo;
		unsigned char *out;
	} HashState;

	static void SHA1Transform(unsigned int state[5], const unsigned char buffer[64]);
	static void sha1_hash_init(SHA1Context *p);
	static void sha1_hash_step(
			SHA1Context *p, /* Add content to this context */
			const unsigned char *data, /* Data to be added */
			unsigned int len /* Number of bytes in data */
	);
	static void sha1_hash_finish(
			SHA1Context *p, /* The SHA1 context to finish and render */
			unsigned char *digest /* Store hash here */
	);

	static void KeccakF1600Step(SHA3Context *p);
	static void SHA3Init(SHA3Context *p, int iSize);
	static void SHA3Update(SHA3Context *p, const unsigned char *aData, unsigned int nData);
	static unsigned char *SHA3Final(SHA3Context *p);

	static void md5_init(MD5Context *v);
	static void md5_step(MD5Context *v);
	static void md5_write(MD5Context *v, const char *buf, size_t len);
	static void md5_finish(MD5Context *v, unsigned char *o);

protected:
	HashFunc _hash_func;
	HashState *_hash_state;
};

#endif
