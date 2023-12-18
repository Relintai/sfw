#ifndef VARIANT_H
#define VARIANT_H

#include "core/object.h"
#include "core/reference.h"
#include "core/string.h"

class Variant {

public:
	enum Type {
		TYPE_NULL = 0,
		TYPE_BOOL,
		TYPE_INT,
		TYPE_UINT,
		TYPE_FLOAT,
		TYPE_STRING,
		TYPE_OBJECT,
		TYPE_POINTER,
	};

	Type get_type() const;

	void clear();
	void zero();

	void parse(const String &str);
	static Variant parse_string(const String &str);

	bool is_null() const;
	bool is_bool() const;
	bool is_int() const;
	bool is_uint() const;
	bool is_float() const;
	bool is_numeric() const;
	bool is_string() const;
	bool is_object() const;
	bool is_pointer() const;
	bool is_reference() const;

	bool is_primitive_type() const;
	bool is_simple_type() const;

	bool to_bool() const;
	int to_int() const;
	uint64_t to_uint() const;
	float to_float() const;
	String to_string() const;
	Object *to_object() const;
	Reference *to_reference() const;
	void *to_pointer() const;
	String *get_string_ptr() const;
	bool is_string_owned() const;

	void set_null();
	void set_bool(const bool value);
	void set_int(const int value);
	void set_uint(const uint64_t value);
	void set_float(const float value);
	void set_float(const double value);
	void set_string(String *value, bool copy = false);
	void set_string(const String &value, bool copy = true);
	void set_object(Object *value);
	void set_pointer(void *value);
	void set_variant(const Variant &value);

	operator bool() const;
	operator int() const;
	operator uint64_t() const;
	operator float() const;
	operator double() const;
	operator String() const;
	operator Object *() const;
	operator Reference *() const;
	operator void *() const;

	void operator=(const Variant &other);
	bool operator==(const Variant &other) const;
	bool operator!=(const Variant &other) const;
	bool operator<(const Variant &other) const;

	Variant(const bool value);
	Variant(const int value);
	Variant(const uint64_t value);
	Variant(const float value);
	Variant(const double value);
	Variant(String *value, const bool copy = false);
	Variant(const String &value, const bool copy = true);
	Variant(Object *value);
	Variant(void *value);
	Variant(const Variant &value);

	Variant();
	~Variant();

private:
	struct StringData {
		bool owner;
		String *string;
	};

	struct ObjectData {
		Object *object;
		Ref<Reference> reference;
	};

	union {
		bool _bool;
		int _int;
		uint64_t _uint;
		float _float;
		StringData *_string;
		ObjectData *_object;
		void *_pointer;
	};

	Type _type;
};

#endif