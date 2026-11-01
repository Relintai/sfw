//--STRIP
#ifndef SEMAPHORE_H
#define SEMAPHORE_H
//--STRIP

/*************************************************************************/
/*  semaphore.h                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/error_list.h"
#include "core/error_macros.h"
#include "core/typedefs.h"

#if !defined(NO_THREADS)

#if defined(_WIN64) || defined(_WIN32)
#elif defined(__APPLE__)

#include <dispatch/dispatch.h>
#include <errno.h>

#else

#include <errno.h>
#include <semaphore.h>

#endif

#endif
//--STRIP

#if !defined(NO_THREADS)

#if defined(_WIN64) || defined(_WIN32)

class Semaphore {
public:
	void post() const;
	void wait() const;
	bool try_wait() const;
	int get() const;

	Semaphore();
	~Semaphore();

private:
	// Don't want to include windows.h here
	// HANDLE
	mutable void *_semaphore;
};

#elif defined(__APPLE__)

class Semaphore {
public:
	_ALWAYS_INLINE_ void post() const {
		_count.increment();
		dispatch_semaphore_signal(_sem);
	}

	_ALWAYS_INLINE_ void wait() const {
		dispatch_semaphore_wait(_sem, DISPATCH_TIME_FOREVER);
		_count.decrement();
	}

	_ALWAYS_INLINE_ bool try_wait() const {
		//Returns zero on success, or non-zero if the timeout occurred.
		if (dispatch_semaphore_wait(_sem, DISPATCH_TIME_NOW) == 0) {
			_count.decrement();
			return true;
		}

		return false;
	}

	_ALWAYS_INLINE_ int get() const {
		return _count.get();
	}

	Semaphore() {
		// Passing zero for the value is useful for when two threads need to reconcile
		// the completion of a particular event. Passing a value greater than zero is
		// useful for managing a finite pool of resources, where the pool size is equal
		// to the value.
		_sem = dispatch_semaphore_create(0);
	}

	~Semaphore() {
	}

private:
	mutable dispatch_semaphore_t _sem;
	mutable SafeNumeric<uint32_t> _count;
};

#else

class Semaphore {
public:
	_ALWAYS_INLINE_ void post() const {
		sem_post(&_sem);
	}

	_ALWAYS_INLINE_ void wait() const {
		//return 0 on success; on error, the value of the semaphore is left unchanged, -1 is returned, and errno is set to indicate the error.
		while (sem_wait(&_sem)) {
			if (errno == EINTR) {
				//he call was interrupted by a signal handler;
				errno = 0;
				continue;
			} else {
				return;
			}
		}
	}

	_ALWAYS_INLINE_ bool try_wait() const {
		while (sem_trywait(&_sem)) {
			if (errno == EINTR) {
				errno = 0;
				continue;
			} else if (errno == EAGAIN) {
				return false;
			} else {
				return false;
			}
		}

		return true;
	}

	_ALWAYS_INLINE_ int get() const {
		int val;
		sem_getvalue(&_sem, &val);

		return val;
	}

	Semaphore() {
		int r = sem_init(&_sem, 0, 0);

		ERR_FAIL_COND(r != 0);
	}

	~Semaphore() {
		sem_destroy(&_sem);
	}

private:
	mutable sem_t _sem;
};

#endif

#else // !defined(NO_THREADS)

class Semaphore {
public:
	_ALWAYS_INLINE_ void post() const {}
	_ALWAYS_INLINE_ void wait() const {}
	_ALWAYS_INLINE_ bool try_wait() const { return true; }
	_ALWAYS_INLINE_ int get() const { return 1; }
};

#endif // !defined(NO_THREADS)

//--STRIP
#endif // SEMAPHORE_H
//--STRIP
