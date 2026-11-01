
//--STRIP
#include "sfw_core.h"

#include "core/pool_vector.h"
#include "core/string_name.h"

#include "core/thread.h"
//--STRIP

void SFWCore::setup() {
	if (_initialized) {
		return;
	}

	_initialized = true;

	Thread::setup_main_thread_id(Thread::get_caller_id());

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
