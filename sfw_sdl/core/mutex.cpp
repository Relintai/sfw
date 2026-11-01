/*************************************************************************/
/*  mutex.cpp                                                            */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/mutex.h"
#include "core/memory.h"

#if defined(_WIN64) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
//--STRIP

static Mutex _global_mutex;

void _global_lock() {
	_global_mutex.lock();
}

void _global_unlock() {
	_global_mutex.unlock();
}

#ifndef NO_THREADS

#if defined(_WIN64) || defined(_WIN32)

void Mutex::lock() const {
#ifdef WINDOWS_USE_MUTEX
	WaitForSingleObject((HANDLE)mutex, INFINITE);
#else
	EnterCriticalSection((CRITICAL_SECTION *)mutex);
#endif
}

void Mutex::unlock() const {
#ifdef WINDOWS_USE_MUTEX
	ReleaseMutex((HANDLE)mutex);
#else
	LeaveCriticalSection((CRITICAL_SECTION *)mutex);
#endif
}

Error Mutex::try_lock() const {
#ifdef WINDOWS_USE_MUTEX
	return (WaitForSingleObject((HANDLE)mutex, 0) == WAIT_TIMEOUT) ? ERR_BUSY : OK;
#else

	if (TryEnterCriticalSection((CRITICAL_SECTION *)mutex)) {
		return OK;
	} else {
		return ERR_BUSY;
	}
#endif
}

Mutex::Mutex() {
#ifdef WINDOWS_USE_MUTEX
	mutex = CreateMutex(NULL, FALSE, NULL);
#else

	mutex = memnew(CRITICAL_SECTION);

#ifdef UWP_ENABLED
	InitializeCriticalSectionEx((CRITICAL_SECTION *)mutex, 0, 0);
#else
	InitializeCriticalSection((CRITICAL_SECTION *)mutex);
#endif
#endif
}

Mutex::~Mutex() {
#ifdef WINDOWS_USE_MUTEX
	CloseHandle((HANDLE)mutex);
#else

	DeleteCriticalSection((CRITICAL_SECTION *)mutex);

	memdelete((CRITICAL_SECTION *)mutex);
#endif
}

void BinaryMutex::lock() const {
#ifdef WINDOWS_USE_MUTEX
	WaitForSingleObject((HANDLE)mutex, INFINITE);
#else
	EnterCriticalSection((CRITICAL_SECTION *)mutex);
#endif
}

void BinaryMutex::unlock() const {
#ifdef WINDOWS_USE_MUTEX
	ReleaseMutex((HANDLE)mutex);
#else
	LeaveCriticalSection((CRITICAL_SECTION *)mutex);
#endif
}

Error BinaryMutex::try_lock() const {
#ifdef WINDOWS_USE_MUTEX
	return (WaitForSingleObject((HANDLE)mutex, 0) == WAIT_TIMEOUT) ? ERR_BUSY : OK;
#else

	if (TryEnterCriticalSection((CRITICAL_SECTION *)mutex)) {
		return OK;
	} else {
		return ERR_BUSY;
	}
#endif
}

BinaryMutex::BinaryMutex() {
#ifdef WINDOWS_USE_MUTEX
	mutex = CreateMutex(NULL, FALSE, NULL);
#else

	mutex = memnew(CRITICAL_SECTION);

#ifdef UWP_ENABLED
	InitializeCriticalSectionEx((CRITICAL_SECTION *)mutex, 0, 0);
#else
	InitializeCriticalSection((CRITICAL_SECTION *)mutex);
#endif
#endif
}

BinaryMutex::~BinaryMutex() {
#ifdef WINDOWS_USE_MUTEX
	CloseHandle((HANDLE)mutex);
#else

	DeleteCriticalSection((CRITICAL_SECTION *)mutex);

	memdelete((CRITICAL_SECTION *)mutex);
#endif
}

#endif

#endif
