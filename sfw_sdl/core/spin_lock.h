//--STRIP
#ifndef SPIN_LOCK_H
#define SPIN_LOCK_H
//--STRIP

/*************************************************************************/
/*  spin_lock.h                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/safe_refcount.h"
#include "core/typedefs.h"
//--STRIP

class SpinLock {
	SafeFlag _flag;

public:
	_ALWAYS_INLINE_ void lock() {
		while (!_flag.test_and_set()) {
			;
		}
	}

	_ALWAYS_INLINE_ void unlock() {
		_flag.clear();
	}
};

//--STRIP
#endif // SPIN_LOCK_H
//--STRIP
