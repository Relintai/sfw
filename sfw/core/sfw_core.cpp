
#include "sfw_core.h"

//--STRIP
#include "core/pool_vector.h"
#include "core/string_name.h"
//--STRIP

void SFWCore::setup() {
	if (_initialized) {
		return;
	}

	_initialized = true;

	StringName::setup();
	MemoryPool::setup();
}

void SFWCore::cleanup() {
	if (!_initialized) {
		return;
	}

	_initialized = false;

	StringName::cleanup();
	MemoryPool::cleanup();
}

bool SFWCore::_initialized = false;
