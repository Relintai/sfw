//--STRIP
#include "resource.h"
//--STRIP

void Resource::emit_changed() {
	changed.emit(this);
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
