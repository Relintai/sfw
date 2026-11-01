//--STRIP
#ifndef THREAD_H
#define THREAD_H
//--STRIP

/*************************************************************************/
/*  thread.h                                                             */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/typedefs.h"

#if !defined(NO_THREADS)
#include "core/safe_refcount.h"
#endif

#if !defined(NO_THREADS)

#if !defined(_WIN64) && !defined(_WIN32)
#include <pthread.h>
#include <sys/types.h>
#endif

#endif
//--STRIP


class String;

class Thread {
public:
	typedef void (*Callback)(void *p_userdata);

	typedef uint64_t ID;

	enum Priority {
		PRIORITY_LOW,
		PRIORITY_NORMAL,
		PRIORITY_HIGH
	};

	struct Settings {
		Priority priority;
		Settings() { priority = PRIORITY_NORMAL; }
	};

public:
#if !defined(NO_THREADS)

	_FORCE_INLINE_ ID get_id() const { return _id; }

	// get the ID of the caller thread
	static ID get_caller_id();

	// get the ID of the main thread
	_FORCE_INLINE_ static ID get_main_id() { return _main_thread_id; }

	_FORCE_INLINE_ static bool is_main_thread() { return get_caller_id() == _main_thread_id; }

	static Error set_name(const String &p_name);

	void start(Thread::Callback p_callback, void *p_user, const Settings &p_settings = Settings());

	bool is_started() const;

	///< waits until thread is finished, and deallocates it.
	void wait_to_finish();

	Thread();
	~Thread();

	static void setup_main_thread_id(ID p_main_thread_id);

#if defined(_WIN64) || defined(_WIN32)
	// Need to be public
	static void _thread_callback(Thread *t);
#endif

#else
	_FORCE_INLINE_ ID get_id() const { return 0; }
	// get the ID of the caller thread
	_FORCE_INLINE_ static ID get_caller_id() { return 0; }
	// get the ID of the main thread
	_FORCE_INLINE_ static ID get_main_id() { return 0; }

	_FORCE_INLINE_ static bool is_main_thread() { return true; }

	static Error set_name(const String &p_name) { return ERR_UNAVAILABLE; }

	void start(Thread::Callback p_callback, void *p_user, const Settings &p_settings = Settings()) {}
	bool is_started() const { return false; }
	void wait_to_finish() {}
#endif

private:
#if !defined(NO_THREADS)

	static ID _main_thread_id;

	ID _id;
	Settings _settings;
	Callback _callback;
	void *_user;

#if defined(_WIN64) || defined(_WIN32)
	// HANDLE. According to the internets just casting this to a void* should work.
	// Don't want to include windows.h here.
	void *_handle;
#else
	static void *thread_callback(void *userdata);

	static pthread_key_t _thread_id_key;
	static SafeNumeric<ID> _next_thread_id;

	pthread_t _pthread;
	pthread_attr_t _pthread_attr;
#endif

#endif
};

//--STRIP
#endif // THREAD_H
//--STRIP
