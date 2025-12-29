
#include "sfwl.h"

#include "sfw_hash.h"

int main(int argc, char **argv) {
	SFWCore::setup();

	String test = "ASDFGHJKL";

	SFWHash h;

	ERR_PRINT("MD5");
	h.init(SFWHash::HASH_MD5);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	h.reset();
	h.hash_string(test);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	ERR_PRINT("SHA1");
	h.init(SFWHash::HASH_SHA1);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	h.reset();
	h.hash_string(test);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	ERR_PRINT("SHA3_224");
	h.init(SFWHash::HASH_SHA3_224);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	h.reset();
	h.hash_string(test);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	ERR_PRINT("SHA3_256");
	h.init(SFWHash::HASH_SHA3_256);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	h.reset();
	h.hash_string(test);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	ERR_PRINT("SHA3_384");
	h.init(SFWHash::HASH_SHA3_384);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	h.reset();
	h.hash_string(test);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	ERR_PRINT("SHA3_512");
	h.init(SFWHash::HASH_SHA3_512);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	h.reset();
	h.hash_string(test);
	h.hash_string(test);
	ERR_PRINT(h.get_hash());

	SFWCore::cleanup();

	return 0;
}
