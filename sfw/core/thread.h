#ifndef THREAD_H
#define THREAD_H

/*************************************************************************/
/*  thread.h                                                             */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#include "core/typedefs.h"

#if !defined(NO_THREADS)
#include "core/safe_refcount.h"
#include <thread>
#endif

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

private:
#if !defined(NO_THREADS)
	friend class Main;

	static ID main_thread_id;

	static uint64_t _thread_id_hash(const std::thread::id &p_t);

	ID id = _thread_id_hash(std::thread::id());
	std::thread thread;

	static void callback(Thread *p_self, const Settings &p_settings, Thread::Callback p_callback, void *p_userdata);

	static Error (*set_name_func)(const String &);
	static void (*set_priority_func)(Thread::Priority);
	static void (*init_func)();
	static void (*term_func)();
#endif

public:
	static void _set_platform_funcs(
			Error (*p_set_name_func)(const String &),
			void (*p_set_priority_func)(Thread::Priority),
			void (*p_init_func)() = nullptr,
			void (*p_term_func)() = nullptr);

#if !defined(NO_THREADS)
	_FORCE_INLINE_ ID get_id() const { return id; }
	// get the ID of the caller thread
	static ID get_caller_id();
	// get the ID of the main thread
	_FORCE_INLINE_ static ID get_main_id() { return main_thread_id; }

	_FORCE_INLINE_ static bool is_main_thread() { return get_caller_id() == main_thread_id; }

	static Error set_name(const String &p_name);

	void start(Thread::Callback p_callback, void *p_user, const Settings &p_settings = Settings());
	bool is_started() const;
	///< waits until thread is finished, and deallocates it.
	void wait_to_finish();

	~Thread();
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
};

#endif // THREAD_H
