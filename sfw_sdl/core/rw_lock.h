//--STRIP
#ifndef RWLOCK_H
#define RWLOCK_H
//--STRIP

/*************************************************************************/
/*  rw_lock.h                                                            */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/error_list.h"
#include "core/typedefs.h"
#include "core/error_macros.h"

#if !defined(NO_THREADS)

#if !defined(_WIN64) && !defined(_WIN32)
#include <pthread.h>
#endif

#endif
//--STRIP

#if !defined(NO_THREADS)

#if defined(_WIN64) || defined(_WIN32)

class RWLock {
	// Don't want to include windows.h here
	mutable void *rwlock;

public:
	// Lock the rwlock, block if locked by someone else
	void read_lock() const;

	// Unlock the rwlock, let other threads continue
	void read_unlock() const;

	// Attempt to lock the rwlock, OK on success, ERR_BUSY means it can't lock.
	Error read_try_lock() const;

	// Lock the rwlock, block if locked by someone else
	void write_lock();

	// Unlock the rwlock, let other thwrites continue
	void write_unlock();

	// Attempt to lock the rwlock, OK on success, ERR_BUSY means it can't lock.
	Error write_try_lock();

	RWLock();

	~RWLock();
};

#else

class RWLock {
	mutable pthread_rwlock_t rwlock;

public:
	// Lock the rwlock, block if locked by someone else
	_FORCE_INLINE_ void read_lock() const {
		int err = pthread_rwlock_rdlock(&rwlock);
		ERR_FAIL_COND(err != 0);
	}

	// Unlock the rwlock, let other threads continue
	_FORCE_INLINE_ void read_unlock() const {
		pthread_rwlock_unlock(&rwlock);
	}

	// Attempt to lock the rwlock, OK on success, ERR_BUSY means it can't lock.
	_FORCE_INLINE_ Error read_try_lock() const {
		if (pthread_rwlock_tryrdlock(&rwlock) != 0) {
			return ERR_BUSY;
		} else {
			return OK;
		}
	}

	// Lock the rwlock, block if locked by someone else
	_FORCE_INLINE_ void write_lock() {
		int err = pthread_rwlock_wrlock(&rwlock);
		ERR_FAIL_COND(err != 0);
	}

	// Unlock the rwlock, let other thwrites continue
	_FORCE_INLINE_ void write_unlock() {
		pthread_rwlock_unlock(&rwlock);
	}

	// Attempt to lock the rwlock, OK on success, ERR_BUSY means it can't lock.
	_FORCE_INLINE_ Error write_try_lock() {
		if (pthread_rwlock_trywrlock(&rwlock) != 0) {
			return ERR_BUSY;
		} else {
			return OK;
		}
	}

	RWLock() {
		//rwlock=PTHREAD_RWLOCK_INITIALIZER; fails on OSX
		pthread_rwlock_init(&rwlock, NULL);
	}

	~RWLock() {
		pthread_rwlock_destroy(&rwlock);
	}
};

#endif

#else

class RWLock {
public:
	_FORCE_INLINE_ void read_lock() const {}
	_FORCE_INLINE_ void read_unlock() const {}
	_FORCE_INLINE_ Error read_try_lock() const { return OK; }

	_FORCE_INLINE_ void write_lock() {}
	_FORCE_INLINE_ void write_unlock() {}
	_FORCE_INLINE_ Error write_try_lock() { return OK; }
};

#endif

class RWLockRead {
	const RWLock &lock;

public:
	RWLockRead(const RWLock &p_lock) :
			lock(p_lock) {
		lock.read_lock();
	}
	~RWLockRead() {
		lock.read_unlock();
	}
};

class RWLockWrite {
	RWLock &lock;

public:
	RWLockWrite(RWLock &p_lock) :
			lock(p_lock) {
		lock.write_lock();
	}
	~RWLockWrite() {
		lock.write_unlock();
	}
};

//--STRIP
#endif // RWLOCK_H
//--STRIP
