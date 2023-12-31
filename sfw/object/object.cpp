#include "object/object.h"

#include "core/error_macros.h"
#include "core/logger.h"
#include "object/object_rc.h"

void Object::notification(int p_notification, bool p_reversed) {
	_notificationv(p_notification, p_reversed);
}

String Object::to_string() {
	return "[" + get_class() + ":" + itos(get_instance_id()) + "]";
}

bool Object::_predelete() {
	_predelete_ok = 1;
	notification(NOTIFICATION_PREDELETE, true);
	if (_predelete_ok) {
		_class_ptr = nullptr; //must restore so destructors can access class ptr correctly
	}
	return _predelete_ok;
}

void Object::_postinitialize() {
	_class_ptr = _get_class_namev();
	notification(NOTIFICATION_POSTINITIALIZE);
}

/*
bool Object::has_meta(const String &p_name) const {
	return metadata.has(p_name);
}

void Object::set_meta(const String &p_name, const Variant &p_value) {
	if (p_value.get_type() == Variant::NIL) {
		metadata.erase(p_name);
		return;
	};

	metadata[p_name] = p_value;
}

Variant Object::get_meta(const String &p_name, const Variant &p_default) const {
	if (!metadata.has(p_name)) {
		return p_default;
	}
	return metadata[p_name];
}

void Object::remove_meta(const String &p_name) {
	metadata.erase(p_name);
}
*/

void Object::cancel_free() {
	_predelete_ok = 0;
}

Object::Object() {
	_is_queued_for_deletion = false;
	_predelete_ok = 0;
	_instance_id = 0;
	_instance_id = ObjectDB::add_instance(this);
}

Object::~Object() {
}

ObjectRC *Object::_use_rc() {
	// The RC object is lazily created the first time it's requested;
	// that way, there's no need to allocate and release it at all if this Object
	// is not being referred by any Variant at all.

	// Although when dealing with Objects from multiple threads some locking
	// mechanism should be used, this at least makes safe the case of first
	// assignment.

	ObjectRC *rc = nullptr;
	ObjectRC *const creating = reinterpret_cast<ObjectRC *>(1);
	if (unlikely(_rc.compare_exchange_strong(rc, creating, std::memory_order_acq_rel))) {
		// Not created yet
		rc = memnew(ObjectRC(this));
		_rc.store(rc, std::memory_order_release);
		return rc;
	}

	// Spin-wait until we know it's created (or just return if it's already created)
	for (;;) {
		if (likely(rc != creating)) {
			rc->increment();
			return rc;
		}
		rc = _rc.load(std::memory_order_acquire);
	}
}

bool predelete_handler(Object *p_object) {
	return p_object->_predelete();
}

void postinitialize_handler(Object *p_object) {
	p_object->_postinitialize();
}

HashMap<ObjectID, Object *> ObjectDB::instances;
ObjectID ObjectDB::instance_counter = 1;
HashMap<Object *, ObjectID, ObjectDB::ObjectPtrHash> ObjectDB::instance_checks;
ObjectID ObjectDB::add_instance(Object *p_object) {
	ERR_FAIL_COND_V(p_object->get_instance_id() != 0, 0);

	rw_lock.write_lock();
	ObjectID instance_id = ++instance_counter;
	instances[instance_id] = p_object;
	instance_checks[p_object] = instance_id;

	rw_lock.write_unlock();

	return instance_id;
}

void ObjectDB::remove_instance(Object *p_object) {
	rw_lock.write_lock();

	instances.erase(p_object->get_instance_id());
	instance_checks.erase(p_object);

	rw_lock.write_unlock();
}
Object *ObjectDB::get_instance(ObjectID p_instance_id) {
	rw_lock.read_lock();
	Object **obj = instances.getptr(p_instance_id);
	rw_lock.read_unlock();

	if (!obj) {
		return nullptr;
	}
	return *obj;
}

void ObjectDB::debug_objects(DebugFunc p_func) {
	rw_lock.read_lock();

	const ObjectID *K = nullptr;
	while ((K = instances.next(K))) {
		p_func(instances[*K]);
	}

	rw_lock.read_unlock();
}

int ObjectDB::get_object_count() {
	rw_lock.read_lock();
	int count = instances.size();
	rw_lock.read_unlock();

	return count;
}

RWLock ObjectDB::rw_lock;

void ObjectDB::cleanup() {
	rw_lock.write_lock();
	if (instances.size()) {
		LOG_WARN("ObjectDB instances leaked at exit!");
	}
	instances.clear();
	instance_checks.clear();
	rw_lock.write_unlock();
}
