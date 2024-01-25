/*************************************************************************/
/*  thread.cpp                                                           */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "thread.h"
//--STRIP

#if !defined(NO_THREADS)

//--STRIP
#include "core/error_macros.h"
#include "core/safe_refcount.h"
//--STRIP

Error (*Thread::set_name_func)(const String &) = nullptr;
void (*Thread::set_priority_func)(Thread::Priority) = nullptr;
void (*Thread::init_func)() = nullptr;
void (*Thread::term_func)() = nullptr;

uint64_t Thread::_thread_id_hash(const std::thread::id &p_t) {
	static std::hash<std::thread::id> hasher;
	return hasher(p_t);
}

Thread::ID Thread::main_thread_id = _thread_id_hash(std::this_thread::get_id());
static thread_local Thread::ID caller_id = 0;
static thread_local bool caller_id_cached = false;

void Thread::_set_platform_funcs(
		Error (*p_set_name_func)(const String &),
		void (*p_set_priority_func)(Thread::Priority),
		void (*p_init_func)(),
		void (*p_term_func)()) {
	Thread::set_name_func = p_set_name_func;
	Thread::set_priority_func = p_set_priority_func;
	Thread::init_func = p_init_func;
	Thread::term_func = p_term_func;
}

void Thread::callback(Thread *p_self, const Settings &p_settings, Callback p_callback, void *p_userdata) {
	caller_id = _thread_id_hash(p_self->thread.get_id());
	caller_id_cached = true;

	if (set_priority_func) {
		set_priority_func(p_settings.priority);
	}
	if (init_func) {
		init_func();
	}

	p_callback(p_userdata);

	if (term_func) {
		term_func();
	}
}

void Thread::start(Thread::Callback p_callback, void *p_user, const Settings &p_settings) {
	if (id != _thread_id_hash(std::thread::id())) {
#ifdef DEBUG_ENABLED
		LOG_WARN("A Thread object has been re-started without wait_to_finish() having been called on it. Please do so to ensure correct cleanup of the thread.");
#endif
		thread.detach();
		std::thread empty_thread;
		thread.swap(empty_thread);
	}
	std::thread new_thread(&Thread::callback, this, p_settings, p_callback, p_user);
	thread.swap(new_thread);
	id = _thread_id_hash(thread.get_id());
}

bool Thread::is_started() const {
	return id != _thread_id_hash(std::thread::id());
}

void Thread::wait_to_finish() {
	if (id != _thread_id_hash(std::thread::id())) {
		ERR_FAIL_COND_MSG(id == get_caller_id(), "A Thread can't wait for itself to finish.");
		thread.join();
		std::thread empty_thread;
		thread.swap(empty_thread);
		id = _thread_id_hash(std::thread::id());
	}
}

Error Thread::set_name(const String &p_name) {
	if (set_name_func) {
		return set_name_func(p_name);
	}

	return ERR_UNAVAILABLE;
}

Thread::~Thread() {
	if (id != _thread_id_hash(std::thread::id())) {
#ifdef DEBUG_ENABLED
		LOG_WARN("A Thread object has been destroyed without wait_to_finish() having been called on it. Please do so to ensure correct cleanup of the thread.");
#endif
		thread.detach();
	}
}

Thread::ID Thread::get_caller_id() {
	if (likely(caller_id_cached)) {
		return caller_id;
	} else {
		caller_id = _thread_id_hash(std::this_thread::get_id());
		caller_id_cached = true;
		return caller_id;
	}
}
#endif
