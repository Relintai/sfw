/*************************************************************************/
/*  semaphore.h                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "semaphore.h"
#include "core/memory.h"

#if !defined(NO_THREADS)

#if defined(_WIN64) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#endif
//--STRIP

#if !defined(NO_THREADS)

#if defined(_WIN64) || defined(_WIN32)

void Semaphore::post() const {
	ReleaseSemaphore((HANDLE)_semaphore, 1, NULL);
}

void Semaphore::wait() const {
	WaitForSingleObjectEx((HANDLE)_semaphore, INFINITE, false);
}

bool Semaphore::try_wait() const {
	if (WaitForSingleObjectEx((HANDLE)_semaphore, 0, false) == WAIT_TIMEOUT) {
		return false;
	}

	return true;
}

int Semaphore::get() const {
	long previous;
	switch (WaitForSingleObjectEx((HANDLE)_semaphore, 0, false)) {
		case WAIT_OBJECT_0: {
			ERR_FAIL_COND_V(!ReleaseSemaphore((HANDLE)_semaphore, 1, &previous), -1);
			return previous + 1;
		} break;
		case WAIT_TIMEOUT: {
			return 0;
		} break;
		default: {
		}
	}

	ERR_FAIL_V(-1);
}

Semaphore::Semaphore() {
#ifdef UWP_ENABLED
	_semaphore = (void *)CreateSemaphoreEx(
			NULL,
			0,
			0xFFFFFFF, //wathever
			NULL,
			0,
			SEMAPHORE_ALL_ACCESS);
#else
	_semaphore = (void *)CreateSemaphore(
			NULL,
			0,
			0xFFFFFFF, //wathever
			NULL);
#endif
}

Semaphore::~Semaphore() {
	CloseHandle((HANDLE)_semaphore);
}

#endif

#endif
