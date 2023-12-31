#include "resource.h"

void Resource::emit_changed() {
	//emit
}

Error Resource::load(const String &path) {
	return ERR_UNAVAILABLE;
}
Error Resource::save(const String &path) {
	return ERR_UNAVAILABLE;
}

Resource::Resource() :
		Reference() {
}

Resource::~Resource() {
}
