//--STRIP
#ifndef OBJECTRC_H
#define OBJECTRC_H
//--STRIP

/*************************************************************************/
/*  object_rc.h                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/memory.h"
#include "core/typedefs.h"

#include <atomic>
//--STRIP

class Object;

// Used to track Variants pointing to a non-Reference Object
class ObjectRC {
	SafePointer<Object *> _ptr;
	SafeNumeric<uint32_t> _users;

public:
	// This is for allowing debug builds to check for instance ID validity,
	// so warnings are shown in debug builds when a stray Variant (one pointing
	// to a released Object) would have happened.
	const ObjectID instance_id;

	_FORCE_INLINE_ void increment() {
		_users.postincrement();
	}

	_FORCE_INLINE_ bool decrement() {
		return _users.postdecrement() == 1;
	}

	_FORCE_INLINE_ bool invalidate() {
		_ptr.set(nullptr);
		return decrement();
	}

	_FORCE_INLINE_ Object *get_ptr() {
		return _ptr.get();
	}

	_FORCE_INLINE_ ObjectRC(Object *p_object) :
			instance_id(p_object->get_instance_id()) {
		// 1 (the Object) + 1 (the first user)
		_users.set(2);
		_ptr.set(p_object);
	}
};

//--STRIP
#endif
//--STRIP
