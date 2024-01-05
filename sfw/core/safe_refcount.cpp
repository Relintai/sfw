/*************************************************************************/
/*  safe_refcount.cpp                                                    */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#if defined(DEBUG_ENABLED) && !defined(NO_THREADS)

//--STRIP
#include "core/safe_refcount.h"

#include "core/error/error_macros.h"
//--STRIP

// On C++14 we don't have std::atomic::is_always_lockfree, so this is the best we can do
void check_lockless_atomics() {
	// Doing the check for the types we actually care about
	if (!std::atomic<uint32_t>{}.is_lock_free() || !std::atomic<uint64_t>{}.is_lock_free() || !std::atomic_bool{}.is_lock_free()) {
		WARN_PRINT("Your compiler doesn't seem to support lockless atomics. Performance will be degraded. Please consider upgrading to a different or newer compiler.");
	}
}

#endif
