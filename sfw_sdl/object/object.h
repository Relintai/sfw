//--STRIP
#ifndef OBJECT_H
#define OBJECT_H
//--STRIP

//--STRIP
#include "core/hash_map.h"
#include "core/rw_lock.h"
#include "core/string_name.h"
#include "core/ustring.h"
#include "core/vector.h"
#include "object/object_id.h"
#include "object/variant.h"

#include "object/dictionary.h"
//--STRIP

/*************************************************************************/
/*  object.h                                                             */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

class ObjectRC;

#define SFW_OBJECT(m_class, m_inherits)                                                                    \
private:                                                                                                   \
	void operator=(const m_class &p_rval) {}                                                               \
                                                                                                           \
public:                                                                                                    \
	virtual String get_class() const {                                                                     \
		return String(#m_class);                                                                           \
	}                                                                                                      \
	virtual const StringName *_get_class_namev() const {                                                   \
		if (!_class_name)                                                                                  \
			_class_name = get_class_static();                                                              \
		return &_class_name;                                                                               \
	}                                                                                                      \
	static void *get_class_ptr_static() {                                                                  \
		static int ptr;                                                                                    \
		return &ptr;                                                                                       \
	}                                                                                                      \
	static String get_class_static() {                                                                     \
		return String(#m_class);                                                                           \
	}                                                                                                      \
	static String get_parent_class_static() {                                                              \
		return m_inherits::get_class_static();                                                             \
	}                                                                                                      \
	static void get_inheritance_list_static(Vector<String> *p_inheritance_list) {                          \
		m_inherits::get_inheritance_list_static(p_inheritance_list);                                       \
		p_inheritance_list->push_back(String(#m_class));                                                   \
	}                                                                                                      \
	static String inherits_static() {                                                                      \
		return String(#m_inherits);                                                                        \
	}                                                                                                      \
	virtual bool is_class(const String &p_class) const {                                                   \
		return (p_class == (#m_class)) ? true : m_inherits::is_class(p_class);                             \
	}                                                                                                      \
	virtual bool is_class_ptr(void *p_ptr) const {                                                         \
		return (p_ptr == get_class_ptr_static()) ? true : m_inherits::is_class_ptr(p_ptr);                 \
	}                                                                                                      \
	static void get_valid_parents_static(Vector<String> *p_parents) {                                      \
		if (m_class::_get_valid_parents_static != m_inherits::_get_valid_parents_static) {                 \
			m_class::_get_valid_parents_static(p_parents);                                                 \
		}                                                                                                  \
		m_inherits::get_valid_parents_static(p_parents);                                                   \
	}                                                                                                      \
	_FORCE_INLINE_ void (Object::*_get_notification() const)(int) {                                        \
		return (void(Object::*)(int)) & m_class::_notification;                                            \
	}                                                                                                      \
	virtual void _notificationv(int p_notification, bool p_reversed) {                                     \
		if (!p_reversed)                                                                                   \
			m_inherits::_notificationv(p_notification, p_reversed);                                        \
		if (m_class::_get_notification() != m_inherits::_get_notification()) {                             \
			_notification(p_notification);                                                                 \
		}                                                                                                  \
		if (p_reversed)                                                                                    \
			m_inherits::_notificationv(p_notification, p_reversed);                                        \
	}                                                                                                      \
	_FORCE_INLINE_ bool (Object::*_get_get() const)(const StringName &p_name, Variant &) const {           \
		return (bool(Object::*)(const StringName &, Variant &) const) & m_class::_get;                     \
	}                                                                                                      \
	virtual bool _getv(const StringName &p_name, Variant &r_ret) const {                                   \
		if (m_class::_get_get() != m_inherits::_get_get()) {                                               \
			if (_get(p_name, r_ret))                                                                       \
				return true;                                                                               \
		}                                                                                                  \
		return m_inherits::_getv(p_name, r_ret);                                                           \
	}                                                                                                      \
	_FORCE_INLINE_ bool (Object::*_get_set() const)(const StringName &p_name, const Variant &p_property) { \
		return (bool(Object::*)(const StringName &, const Variant &)) & m_class::_set;                     \
	}                                                                                                      \
	virtual bool _setv(const StringName &p_name, const Variant &p_property) {                              \
		if (m_inherits::_setv(p_name, p_property))                                                         \
			return true;                                                                                   \
		if (m_class::_get_set() != m_inherits::_get_set()) {                                               \
			return _set(p_name, p_property);                                                               \
		}                                                                                                  \
		return false;                                                                                      \
	}                                                                                                      \
                                                                                                           \
private:

class Object {
public:
	enum {
		NOTIFICATION_POSTINITIALIZE = 0,
		NOTIFICATION_PREDELETE = 1
	};

	void set(const StringName &p_name, const Variant &p_value, bool *r_valid = nullptr);
	Variant get(const StringName &p_name, bool *r_valid = nullptr) const;

	//less than. < "operator" used for cutrom sorting Arrays.
	virtual bool lt(const Variant &p_value_l, const Variant &p_value_r);

	virtual String get_class() const { return "Object"; }
	static void *get_class_ptr_static() {
		static int ptr;
		return &ptr;
	}

	static String get_class_static() { return "Object"; }
	static String get_parent_class_static() { return String(); }

	static void get_inheritance_list_static(Vector<String> *p_inheritance_list) { p_inheritance_list->push_back("Object"); }

	virtual bool is_class(const String &p_class) const { return (p_class == "Object"); }
	virtual bool is_class_ptr(void *p_ptr) const { return get_class_ptr_static() == p_ptr; }

	static void get_valid_parents_static(Vector<String> *p_parents) {}
	static void _get_valid_parents_static(Vector<String> *p_parents) {}

	virtual const StringName *_get_class_namev() const {
		if (!_class_name) {
			_class_name = get_class_static();
		}
		return &_class_name;
	}

	_FORCE_INLINE_ const StringName &get_class_name() const {
		if (!_class_ptr) {
			return *_get_class_namev();
		} else {
			return *_class_ptr;
		}
	}

	ObjectRC *_use_rc();

	_FORCE_INLINE_ ObjectID get_instance_id() const {
		return _instance_id;
	}

	void notification(int p_notification, bool p_reversed = false);
	virtual String to_string();

	bool _is_queued_for_deletion;
	bool is_queued_for_deletion() const {
		return _is_queued_for_deletion;
	}

	void cancel_free();

	bool has_meta(const String &p_name) const;
	void set_meta(const String &p_name, const Variant &p_value);
	void remove_meta(const String &p_name);
	Variant get_meta(const String &p_name, const Variant &p_default = Variant()) const;
	void get_meta_list(List<String> *p_list) const;

	Object();
	virtual ~Object();

	template <class T>
	static T *cast_to(Object *p_object) {
		if (!p_object)
			return NULL;
		if (p_object->is_class_ptr(T::get_class_ptr_static()))
			return static_cast<T *>(p_object);
		else
			return NULL;
	}

	template <class T>
	static const T *cast_to(const Object *p_object) {
		if (!p_object)
			return NULL;
		if (p_object->is_class_ptr(T::get_class_ptr_static()))
			return static_cast<const T *>(p_object);
		else
			return NULL;
	}

protected:
	_FORCE_INLINE_ void (Object::*_get_notification() const)(int) {
		return &Object::_notification;
	}

	bool _set(const StringName &p_name, const Variant &p_property) {
		return false;
	};
	bool _get(const StringName &p_name, Variant &r_property) const {
		return false;
	};

	virtual bool _setv(const StringName &p_name, const Variant &p_property) {
		return false;
	};
	virtual bool _getv(const StringName &p_name, Variant &r_property) const {
		return false;
	};

	_FORCE_INLINE_ bool (Object::*_get_get() const)(const StringName &p_name, Variant &r_ret) const {
		return &Object::_get;
	}
	_FORCE_INLINE_ bool (Object::*_get_set() const)(const StringName &p_name, const Variant &p_property) {
		return &Object::_set;
	}

	virtual void _notificationv(int p_notification, bool p_reversed){};
	void _notification(int p_notification){};

	friend bool predelete_handler(Object *);
	friend void postinitialize_handler(Object *);

	int _predelete_ok;
	bool _predelete();
	void _postinitialize();

	mutable StringName _class_name;
	mutable const StringName *_class_ptr;

	ObjectID _instance_id;
	SafePointer<ObjectRC *> _rc;

	Dictionary metadata;
};

bool predelete_handler(Object *p_object);
void postinitialize_handler(Object *p_object);

class ObjectDB {
	struct ObjectPtrHash {
		static _FORCE_INLINE_ uint32_t hash(const Object *p_obj) {
			union {
				const Object *p;
				unsigned long i;
			} u;
			u.p = p_obj;
			return HashMapHasherDefault::hash((uint64_t)u.i);
		}
	};

	static HashMap<ObjectID, Object *> instances;
	static HashMap<Object *, ObjectID, ObjectPtrHash> instance_checks;

	static ObjectID instance_counter;
	friend class Object;
	friend void unregister_core_types();

	static RWLock rw_lock;
	static void cleanup();
	static ObjectID add_instance(Object *p_object);
	static void remove_instance(Object *p_object);
	friend void register_core_types();

public:
	typedef void (*DebugFunc)(Object *p_obj);

	static Object *get_instance(ObjectID p_instance_id);
	static void debug_objects(DebugFunc p_func);
	static int get_object_count();

	// This one may give false positives because a new object may be allocated at the same memory of a previously freed one
	_FORCE_INLINE_ static bool instance_validate(Object *p_ptr) {
		rw_lock.read_lock();

		bool exists = instance_checks.has(p_ptr);

		rw_lock.read_unlock();

		return exists;
	}
};

//--STRIP
#endif
//--STRIP
