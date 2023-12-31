#ifndef OBJECT_H
#define OBJECT_H

#include "ustring.h"
#include "vector.h"

/*************************************************************************/
/*  object.h                                                             */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#define SFW_OBJECT(m_class, m_inherits)                                                   \
private:                                                                                   \
	void operator=(const m_class &p_rval) {}                                               \
                                                                                           \
public:                                                                                    \
	virtual String get_class() const override {                                            \
		return String(#m_class);                                                           \
	}                                                                                      \
	static void *get_class_ptr_static() {                                                  \
		static int ptr;                                                                    \
		return &ptr;                                                                       \
	}                                                                                      \
	static String get_class_static() {                                                     \
		return String(#m_class);                                                           \
	}                                                                                      \
	static String get_parent_class_static() {                                              \
		return m_inherits::get_class_static();                                             \
	}                                                                                      \
	static void get_inheritance_list_static(Vector<String> *p_inheritance_list) {          \
		m_inherits::get_inheritance_list_static(p_inheritance_list);                       \
		p_inheritance_list->push_back(String(#m_class));                                   \
	}                                                                                      \
	static String inherits_static() {                                                      \
		return String(#m_inherits);                                                        \
	}                                                                                      \
	virtual bool is_class(const String &p_class) const override {                          \
		return (p_class == (#m_class)) ? true : m_inherits::is_class(p_class);             \
	}                                                                                      \
	virtual bool is_class_ptr(void *p_ptr) const override {                                \
		return (p_ptr == get_class_ptr_static()) ? true : m_inherits::is_class_ptr(p_ptr); \
	}                                                                                      \
                                                                                           \
	static void get_valid_parents_static(Vector<String> *p_parents) {                      \
		if (m_class::_get_valid_parents_static != m_inherits::_get_valid_parents_static) { \
			m_class::_get_valid_parents_static(p_parents);                                 \
		}                                                                                  \
                                                                                           \
		m_inherits::get_valid_parents_static(p_parents);                                   \
	}                                                                                      \
                                                                                           \
private:

class Object {
public:
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
};

#endif