#ifndef THREAD_SAFE_H
#define THREAD_SAFE_H

/*************************************************************************/
/*  thread_safe.h                                                        */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/mutex.h"
//--STRIP

#define _THREAD_SAFE_CLASS_ mutable Mutex _thread_safe_;
#define _THREAD_SAFE_METHOD_ MutexLock _thread_safe_method_(_thread_safe_);
#define _THREAD_SAFE_LOCK_ _thread_safe_.lock();
#define _THREAD_SAFE_UNLOCK_ _thread_safe_.unlock();

#endif
