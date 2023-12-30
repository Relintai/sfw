#ifndef REFERENCE_H
#define REFERENCE_H

// Most of the code is from the godot engine's reference.h
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */

#include "memory.h"
#include "object.h"
#include "safe_refcount.h"

class Reference : public Object {
	SFW_OBJECT(Reference, Object);

public:
	/*_FORCE_INLINE_*/ bool is_referenced() const { return refcount_init.get() != 1; }
	bool init_ref();
	bool reference(); // returns false if refcount is at zero and didn't get increased
	bool unreference();
	int reference_get_count() const;

	Reference();
	virtual ~Reference();

private:
	SafeRefCount refcount;
	SafeRefCount refcount_init;
};

template <class T>
class Ref {
	T *reference;

	void ref(const Ref &p_from) {
		if (p_from.reference == reference) {
			return;
		}

		unref();

		reference = p_from.reference;
		if (reference) {
			reference->reference();
		}
	}

	void ref_pointer(T *p_ref) {
		//ERR_FAIL_COND(!p_ref);

		if (p_ref->init_ref()) {
			reference = p_ref;
		}
	}

	//virtual Reference * get_reference() const { return reference; }
public:
	_FORCE_INLINE_ bool operator==(const T *p_ptr) const {
		return reference == p_ptr;
	}
	_FORCE_INLINE_ bool operator!=(const T *p_ptr) const {
		return reference != p_ptr;
	}

	_FORCE_INLINE_ bool operator<(const Ref<T> &p_r) const {
		return reference < p_r.reference;
	}
	_FORCE_INLINE_ bool operator==(const Ref<T> &p_r) const {
		return reference == p_r.reference;
	}
	_FORCE_INLINE_ bool operator!=(const Ref<T> &p_r) const {
		return reference != p_r.reference;
	}

	_FORCE_INLINE_ T *operator->() {
		return reference;
	}

	_FORCE_INLINE_ T *operator*() {
		return reference;
	}

	_FORCE_INLINE_ const T *operator->() const {
		return reference;
	}

	_FORCE_INLINE_ const T *ptr() const {
		return reference;
	}
	_FORCE_INLINE_ T *ptr() {
		return reference;
	}

	_FORCE_INLINE_ const T *operator*() const {
		return reference;
	}

	void operator=(const Ref &p_from) {
		ref(p_from);
	}

	template <class T_Other>
	void operator=(const Ref<T_Other> &p_from) {
		Reference *refb = const_cast<Reference *>(static_cast<const Reference *>(p_from.ptr()));
		if (!refb) {
			unref();
			return;
		}
		Ref r;
		r.reference = Object::cast_to<T>(refb);
		ref(r);
		r.reference = nullptr;
	}

	template <class T_Other>
	void reference_ptr(T_Other *p_ptr) {
		if (reference == p_ptr) {
			return;
		}
		unref();

		T *r = Object::cast_to<T>(p_ptr);
		if (r) {
			ref_pointer(r);
		}
	}

	Ref(const Ref &p_from) {
		reference = nullptr;
		ref(p_from);
	}

	template <class T_Other>
	Ref(const Ref<T_Other> &p_from) {
		reference = nullptr;
		Reference *refb = const_cast<Reference *>(static_cast<const Reference *>(p_from.ptr()));
		if (!refb) {
			unref();
			return;
		}
		Ref r;
		r.reference = Object::cast_to<T>(refb);
		ref(r);
		r.reference = nullptr;
	}

	Ref(T *p_reference) {
		reference = nullptr;
		if (p_reference) {
			ref_pointer(p_reference);
		}
	}

	inline bool is_valid() const { return reference != nullptr; }
	inline bool is_null() const { return reference == nullptr; }

	void unref() {
		//TODO this should be moved to mutexes, since this engine does not really
		// do a lot of referencing on references and stuff
		// mutexes will avoid more crashes?

		if (reference && reference->unreference()) {
			memdelete(reference);
		}
		reference = nullptr;
	}

	void instance() {
		ref(memnew(T));
	}

	Ref() {
		reference = nullptr;
	}

	~Ref() {
		unref();
	}
};

typedef Ref<Reference> REF;

/*
class WeakRef : public Reference {
	SFW_OBJECT(WeakRef, Reference);

	ObjectID ref;

protected:
	static void _bind_methods();

public:
	void set_obj(Object *p_object);
	void set_ref(const REF &p_ref);

	WeakRef();
};
*/

#endif