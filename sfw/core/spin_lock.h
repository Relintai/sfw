#ifndef SPIN_LOCK_H
#define SPIN_LOCK_H

/*************************************************************************/
/*  spin_lock.h                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/typedefs.h"

#include <atomic>
//--STRIP

class SpinLock {
	std::atomic_flag locked = ATOMIC_FLAG_INIT;

public:
	_ALWAYS_INLINE_ void lock() {
		while (locked.test_and_set(std::memory_order_acquire)) {
			;
		}
	}
	_ALWAYS_INLINE_ void unlock() {
		locked.clear(std::memory_order_release);
	}
};
#endif // SPIN_LOCK_H
