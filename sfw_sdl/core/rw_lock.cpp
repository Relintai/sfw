/*************************************************************************/
/*  rw_lock.h                                                            */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "rw_lock.h"

#include "core/memory.h"

#if defined(_WIN64) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
//--STRIP

#ifndef NO_THREADS

#if defined(_WIN64) || defined(_WIN32)

// Lock the rwlock, block if locked by someone else
void RWLock::read_lock() const {
	AcquireSRWLockShared((SRWLOCK *)rwlock);
}

// Unlock the rwlock, let other threads continue
void RWLock::read_unlock() const {
	ReleaseSRWLockShared((SRWLOCK *)rwlock);
}

// Attempt to lock the rwlock, OK on success, ERR_BUSY means it can't lock.
Error RWLock::read_try_lock() const {
	if (TryAcquireSRWLockShared((SRWLOCK *)rwlock) == 0) {
		return ERR_BUSY;
	} else {
		return OK;
	}
}

// Lock the rwlock, block if locked by someone else
void RWLock::write_lock() {
	AcquireSRWLockExclusive((SRWLOCK *)rwlock);
}

// Unlock the rwlock, let other thwrites continue
void RWLock::write_unlock() {
	ReleaseSRWLockExclusive((SRWLOCK *)rwlock);
}

// Attempt to lock the rwlock, OK on success, ERR_BUSY means it can't lock.
Error RWLock::write_try_lock() {
	if (TryAcquireSRWLockExclusive((SRWLOCK *)rwlock) == 0) {
		return ERR_BUSY;
	} else {
		return OK;
	}
}

RWLock::RWLock() {
	rwlock = memnew(SRWLOCK);
	InitializeSRWLock((SRWLOCK *)rwlock);
}

RWLock::~RWLock() {
	memdelete((SRWLOCK *)rwlock);
}

#endif

#endif
