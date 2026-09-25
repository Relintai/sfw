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
#include "core/memory.h"
#include "core/safe_refcount.h"
#include "core/ustring.h"

#if defined(_WIN64) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
//--STRIP

#ifdef __APPLE__
#define PTHREAD_RENAME_SELF
#endif

#if defined(_WIN64) || defined(_WIN32)

Thread::ID Thread::_main_thread_id = 0;
static thread_local Thread::ID _caller_id = 0;
static thread_local bool _caller_id_cached = false;

static DWORD WINAPI thread_callback(LPVOID userdata) {
	Thread *t = reinterpret_cast<Thread *>(userdata);

	Thread::_thread_callback(t);

	return 0;
}

void Thread::_thread_callback(Thread *t) {
	t->_id = (ID)GetCurrentThreadId(); // must implement

	_caller_id = t->_id;
	_caller_id_cached = true;

	if (t->_settings.priority == Thread::PRIORITY_LOW) {
		SetThreadPriority((HANDLE)t->_handle, THREAD_PRIORITY_LOWEST);
	} else if (t->_settings.priority == Thread::PRIORITY_HIGH) {
		SetThreadPriority((HANDLE)t->_handle, THREAD_PRIORITY_HIGHEST);
	}

	//ScriptServer::thread_enter(); //scripts may need to attach a stack

	t->_callback(t->_user);
	SetEvent(t->_handle);

	//ScriptServer::thread_exit();
}

Thread::ID Thread::get_caller_id() {
	if (likely(_caller_id_cached)) {
		return _caller_id;
	} else {
		_caller_id = (ID)GetCurrentThreadId();
		_caller_id_cached = true;

		return _caller_id;
	}
}

Error Thread::set_name(const String &p_name) {
	return ERR_UNAVAILABLE;
}

void Thread::start(Thread::Callback p_callback, void *p_user, const Settings &p_settings) {
	ERR_FAIL_COND_MSG(_handle != NULL, "A Thread cannot be started without wait_to_finish() having been called on it. Please do so to ensure correct cleanup of the thread.");

	_settings = p_settings;
	_callback = p_callback;
	_user = p_user;
	_handle = CreateEvent(NULL, TRUE, FALSE, NULL);

	QueueUserWorkItem(thread_callback, this, WT_EXECUTELONGFUNCTION);
}

bool Thread::is_started() const {
	return _id != 0;
}

///< waits until thread is finished, and deallocates it.
void Thread::wait_to_finish() {
	if (_handle == NULL) {
		return;
	}

	ERR_FAIL_COND_MSG(_id == get_caller_id(), "A Thread can't wait for itself to finish.");

	WaitForSingleObject((HANDLE)_handle, INFINITE);
	CloseHandle((HANDLE)_handle);

	_handle = 0;
	_id = 0;
}

Thread::Thread() {
	_handle = NULL;
	_id = 0;
	_callback = NULL;
	_user = NULL;
}

Thread::~Thread() {
	if (_handle != NULL) {
#ifdef DEBUG_ENABLED
		PRINT_WARN("A Thread object has been destroyed without wait_to_finish() having been called on it. Please do so to ensure correct cleanup of the thread.");
#endif

		CloseHandle((HANDLE)_handle);
	}
}

void Thread::setup_main_thread_id(Thread::ID p_main_thread_id) {
	_main_thread_id = p_main_thread_id;

	_caller_id = _main_thread_id;
	_caller_id_cached = true;
}

#else //defined(_WIN64) || defined(_WIN32)

#ifdef PTHREAD_BSD_SET_NAME
#include <pthread_np.h>
#endif

static void _thread_id_key_destr_callback(void *p_value) {
	memdelete(static_cast<Thread::ID *>(p_value));
}

static pthread_key_t _create_thread_id_key() {
	pthread_key_t key;
	pthread_key_create(&key, &_thread_id_key_destr_callback);
	return key;
}

Thread::ID Thread::_main_thread_id = 0;
static thread_local Thread::ID _caller_id = 0;
static thread_local bool _caller_id_cached = false;

pthread_key_t Thread::_thread_id_key = _create_thread_id_key();
SafeNumeric<Thread::ID> Thread::_next_thread_id;

Thread::ID Thread::get_caller_id() {
	if (likely(_caller_id_cached)) {
		return _caller_id;
	} else {
		void *value = pthread_getspecific(_thread_id_key);

		if (value) {
			return *static_cast<ID *>(value);

			_caller_id = *static_cast<ID *>(value);
			_caller_id_cached = true;
			return _caller_id;
		}

		ID new_id = _next_thread_id.increment();

		// Was this the reason thread ids got hashed?
		if (unlikely(new_id == _main_thread_id)) {
			new_id = _next_thread_id.increment();
		}

		pthread_setspecific(_thread_id_key, (void *)memnew(ID(new_id)));

		_caller_id = new_id;
		_caller_id_cached = true;

		return new_id;
	}
}

Error Thread::set_name(const String &p_name) {
#ifdef PTHREAD_NO_RENAME
	return ERR_UNAVAILABLE;

#else

#ifdef PTHREAD_RENAME_SELF

	// check if thread is the same as caller
	int err = pthread_setname_np(p_name.utf8().get_data());

#else

	pthread_t running_thread = pthread_self();
#ifdef PTHREAD_BSD_SET_NAME
	pthread_set_name_np(running_thread, p_name.utf8().get_data());
	int err = 0; // Open/FreeBSD ignore errors in this function
#elif defined(PTHREAD_NETBSD_SET_NAME)
	int err = pthread_setname_np(running_thread, "%s", const_cast<char *>(p_name.utf8().get_data()));
#else
	int err = pthread_setname_np(running_thread, p_name.utf8().get_data());
#endif // PTHREAD_BSD_SET_NAME

#endif // PTHREAD_RENAME_SELF

	return err == 0 ? OK : ERR_INVALID_PARAMETER;

#endif // PTHREAD_NO_RENAME
}

void Thread::start(Thread::Callback p_callback, void *p_user, const Settings &p_settings) {
	ERR_FAIL_COND_MSG(_pthread != 0, "A Thread cannot be started without wait_to_finish() having been called on it. Please do so to ensure correct cleanup of the thread.");

	_settings = p_settings;
	_callback = p_callback;
	_user = p_user;

	pthread_attr_init(&_pthread_attr);
	pthread_attr_setdetachstate(&_pthread_attr, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setstacksize(&_pthread_attr, 256 * 1024);

	pthread_create(&_pthread, &_pthread_attr, thread_callback, this);
}

bool Thread::is_started() const {
	return _id != 0;
}

///< waits until thread is finished, and deallocates it.
void Thread::wait_to_finish() {
	if (_pthread == 0) {
		return;
	}

	ERR_FAIL_COND_MSG(_id == get_caller_id(), "A Thread can't wait for itself to finish.");

	pthread_join(_pthread, NULL);
	_pthread = 0;
	_id = 0;
}

Thread::Thread() {
	_pthread = 0;
	_id = 0;
	_callback = NULL;
	_user = NULL;
}

Thread::~Thread() {
	if (_pthread != 0) {
#ifdef DEBUG_ENABLED
		PRINT_WARN("A Thread object has been destroyed without wait_to_finish() having been called on it. Please do so to ensure correct cleanup of the thread.");
#endif

		pthread_detach(_pthread);
	}
}

void Thread::setup_main_thread_id(Thread::ID p_main_thread_id) {
	_main_thread_id = p_main_thread_id;

	_caller_id = _main_thread_id;
	_caller_id_cached = true;

	pthread_setspecific(_thread_id_key, (void *)memnew(ID(_caller_id)));
}

void *Thread::thread_callback(void *userdata) {
	Thread *t = reinterpret_cast<Thread *>(userdata);
	t->_id = _next_thread_id.increment();

	// Was this the reason thread ids got hashed?
	if (unlikely(t->_id == _main_thread_id)) {
		t->_id = _next_thread_id.increment();
	}

	_caller_id = t->_id;
	_caller_id_cached = true;

	// Note _thread_id_key_destr_callback frees this
	pthread_setspecific(_thread_id_key, (void *)memnew(ID(t->_id)));

#ifndef __APPLE__
	if (t->_settings.priority != PRIORITY_NORMAL) {
		pthread_setschedprio(t->_pthread, t->_settings.priority);
	}
#endif

	//init_func();

	//ScriptServer::thread_enter(); //scripts may need to attach a stack

	t->_callback(t->_user);

	//ScriptServer::thread_exit();

	//term_func();

	return NULL;
}

#endif // defined(_WIN64) || defined(_WIN32)

#endif //!defined(NO_THREADS)
