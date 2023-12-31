#include "object/reference.h"

/*************************************************************************/
/*  reference.cpp                                                        */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

bool Reference::init_ref() {
	if (reference()) {
		if (!is_referenced() && refcount_init.unref()) {
			unreference(); // first referencing is already 1, so compensate for the ref above
		}

		return true;
	} else {
		return false;
	}
}

int Reference::reference_get_count() const {
	return refcount.get();
}

bool Reference::reference() {
	uint32_t rc_val = refcount.refval();
	bool success = rc_val != 0;

	return success;
}

bool Reference::unreference() {
	uint32_t rc_val = refcount.unrefval();
	bool die = rc_val == 0;

	return die;
}

Reference::Reference() :
		Object() {
	refcount.init();
	refcount_init.init();
}

Reference::~Reference() {
}

/*
void WeakRef::set_obj(Object *p_object) {
	//ref = p_object ? p_object->get_instance_id() : 0;
}

void WeakRef::set_ref(const REF &p_ref) {
	//ref = p_ref.is_valid() ? p_ref->get_instance_id() : 0;
}

WeakRef::WeakRef() :
		ref(0) {
}
*/