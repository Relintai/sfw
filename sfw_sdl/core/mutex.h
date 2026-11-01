//--STRIP
#ifndef MUTEX_H
#define MUTEX_H
//--STRIP

/*************************************************************************/
/*  mutex.h                                                              */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/error_list.h"
#include "core/typedefs.h"

#if !defined(NO_THREADS)

#if !defined(_WIN64) && !defined(_WIN32)
#include <pthread.h>
#endif

#endif
//--STRIP

#if !defined(NO_THREADS)

#if defined(_WIN64) || defined(_WIN32)

class Mutex {
	friend class MutexLock;

	// void* because we don't want to include windows.h in this header.
	mutable void *mutex;

public:
	void lock() const;
	void unlock() const;
	Error try_lock() const;

	Mutex();
	~Mutex();
};

class BinaryMutex {
	friend class MutexLock;

	// void* because we don't want to include windows.h in this header.
	mutable void *mutex;

public:
	void lock() const;
	void unlock() const;
	Error try_lock() const;

	BinaryMutex();
	~BinaryMutex();
};

// This is written this way instead of being a template to overcome a limitation of C++ pre-17
// that would require MutexLock to be used like this: MutexLock<Mutex> lock;
class MutexLock {
	union {
		Mutex *recursive_mutex;
		BinaryMutex *mutex;
	};
	bool recursive;

public:
	_ALWAYS_INLINE_ explicit MutexLock(const Mutex &p_mutex) {
		recursive_mutex = const_cast<Mutex *>(&p_mutex);
		recursive = true;

		recursive_mutex->lock();
	}
	_ALWAYS_INLINE_ explicit MutexLock(const BinaryMutex &p_mutex) {
		mutex = const_cast<BinaryMutex *>(&p_mutex);
		recursive = false;
		mutex->lock();
	}

	_ALWAYS_INLINE_ ~MutexLock() {
		if (recursive) {
			recursive_mutex->unlock();
		} else {
			mutex->unlock();
		}
	}
};

#else

class Mutex {
	friend class MutexLock;

	mutable pthread_mutexattr_t attr;
	mutable pthread_mutex_t mutex;

public:
	_ALWAYS_INLINE_ void lock() const {
		pthread_mutex_lock(&mutex);
	}

	_ALWAYS_INLINE_ void unlock() const {
		pthread_mutex_unlock(&mutex);
	}

	_ALWAYS_INLINE_ Error try_lock() const {
		return (pthread_mutex_trylock(&mutex) == 0) ? OK : ERR_BUSY;
	}

	Mutex() {
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&mutex, &attr);
	}

	~Mutex() {
		pthread_mutex_destroy(&mutex);
	}
};

class BinaryMutex {
	friend class MutexLock;

	mutable pthread_mutexattr_t attr;
	mutable pthread_mutex_t mutex;

public:
	_ALWAYS_INLINE_ void lock() const {
		pthread_mutex_lock(&mutex);
	}

	_ALWAYS_INLINE_ void unlock() const {
		pthread_mutex_unlock(&mutex);
	}

	_ALWAYS_INLINE_ Error try_lock() const {
		return (pthread_mutex_trylock(&mutex) == 0) ? OK : ERR_BUSY;
	}

	BinaryMutex() {
		pthread_mutexattr_init(&attr);
		pthread_mutex_init(&mutex, &attr);
	}

	~BinaryMutex() {
		pthread_mutex_destroy(&mutex);
	}
};

// This is written this way instead of being a template to overcome a limitation of C++ pre-17
// that would require MutexLock to be used like this: MutexLock<Mutex> lock;
class MutexLock {
	union {
		Mutex *recursive_mutex;
		BinaryMutex *mutex;
	};
	bool recursive;

public:
	_ALWAYS_INLINE_ explicit MutexLock(const Mutex &p_mutex) {
		recursive_mutex = const_cast<Mutex *>(&p_mutex);
		recursive = true;

		recursive_mutex->lock();
	}
	_ALWAYS_INLINE_ explicit MutexLock(const BinaryMutex &p_mutex) {
		mutex = const_cast<BinaryMutex *>(&p_mutex);
		recursive = false;
		mutex->lock();
	}

	_ALWAYS_INLINE_ ~MutexLock() {
		if (recursive) {
			recursive_mutex->unlock();
		} else {
			mutex->unlock();
		}
	}
};

#endif

#else

class FakeMutex {
	FakeMutex() {}
};

template <class MutexT>
class MutexImpl {
public:
	_ALWAYS_INLINE_ void lock() const {}
	_ALWAYS_INLINE_ void unlock() const {}
	_ALWAYS_INLINE_ Error try_lock() const { return OK; }
};

class MutexLock {
public:
	explicit MutexLock(const MutexImpl<FakeMutex> &p_mutex) {}
};

using Mutex = MutexImpl<FakeMutex>;
using BinaryMutex = MutexImpl<FakeMutex>; // Non-recursive, handle with care

#endif // !NO_THREADS

//--STRIP
#endif // MUTEX_H
//--STRIP
