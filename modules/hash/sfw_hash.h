#ifndef SFW_HASH_H
#define SFW_HASH_H

// Originally from:

// https://github.com/zzo38/freeheromesh/commits/trunk/
// 50e22c8c3008b8b2d610974fdb02029855f1dfba

// Free public domain cryptographic hash library

// Some of the code in the .cpp file is based on some code from SQLite.
// The original code and this code also is public domain.

// Adding -fwrapv (or equivalent) flag to the compiler might be needed in some specific compilers

//--STRIP
//#include "sfw.h"
#include "sfwl.h"
//--STRIP

//--INCLUDE_SFW_HEADER

class SFWHash {
public:
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

	void hash_string(const String &p_str);
	void hash_buffer(const uint8_t *p_buffer, const int p_length);

	void finalize();
	void reset();

	String get_hash();

	SFWHash();
	~SFWHash();

protected:
	// Tell the length (in bytes) of the hash of the specified algorithm. If
	// it is not implemented, then the result is zero.
	static int _hash_length(HashFunc alg);

	// Returns a writable stream. If the echo stream is not null, then any
	// data written to the stream is also written to the echo stream. When
	// the stream is closed, the hash (as binary) is written to the out.
	static FILE *_hash_stream(HashFunc alg, FILE *echo, uint8_t *out);

	// Returns a hash (as binary) of the specified data. The returned buffer
	// is allocated by malloc and must be freed by free. (This function is a
	// convenience function implemented in terms of the other two functions.)
	static uint8_t *_hash_buffer(HashFunc alg, const uint8_t *data, int len);

	/* Context for the SHA1 hash */
	struct SHA1Context {
		uint32_t state[5];
		uint32_t count[2];
		uint8_t buffer[64];
	};

	/*
	** State structure for a SHA3 hash in progress
	*/
	struct SHA3Context {
		union {
			uint64_t s[25]; /* Keccak state. 5x5 lines of 64 bits each */
			uint8_t x[1600]; /* ... or 1600 bytes */
		} u;
		uint32_t nRate; /* Bytes of input accepted per Keccak iteration */
		uint32_t nLoaded; /* Input bytes loaded into u.x[] so far this cycle */
		uint32_t ixMask; /* Insert next input into u.x[nLoaded^ixMask]. */
	};

	typedef struct {
		uint8_t chunk[64];
		uint64_t len;
		uint32_t a, b, c, d;
	} MD5Context;

	static void SHA1Transform(uint32_t state[5], const uint8_t buffer[64]);
	static void sha1_hash_init(SHA1Context *p);
	static void sha1_hash_step(
			SHA1Context *p, /* Add content to this context */
			const uint8_t *data, /* Data to be added */
			uint32_t len /* Number of bytes in data */
	);
	static void sha1_hash_finish(
			SHA1Context *p, /* The SHA1 context to finish and render */
			uint8_t *digest /* Store hash here */
	);

	static void KeccakF1600Step(SHA3Context *p);
	static void SHA3Init(SHA3Context *p, int iSize);
	static void SHA3Update(SHA3Context *p, const uint8_t *aData, uint32_t nData);
	static uint8_t *SHA3Final(SHA3Context *p);

	static void md5_init(MD5Context *v);
	static void md5_step(MD5Context *v);
	static void md5_write(MD5Context *v, const uint8_t *buf, size_t len);
	static void md5_finish(MD5Context *v, uint8_t *o);

protected:
	union {
		SHA1Context _sha1_context;
		SHA3Context _sha3_context;
		MD5Context _md5_context;
	};

	bool _finalized;
	HashFunc _hash_func;
	uint8_t *_out;
};

#endif
