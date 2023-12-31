/*************************************************************************/
/*  mutex.cpp                                                            */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#include "core/mutex.h"

static Mutex _global_mutex;

void _global_lock() {
	_global_mutex.lock();
}

void _global_unlock() {
	_global_mutex.unlock();
}

#ifndef NO_THREADS

template class MutexImpl<std::recursive_mutex>;
template class MutexImpl<std::mutex>;

#endif
