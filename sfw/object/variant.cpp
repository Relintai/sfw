#include "variant.h"

#include "math.h"
#include "core/reference.h"

Variant::Type Variant::get_type() const {
	return _type;
}

void Variant::clear() {
	switch (_type) {
		case TYPE_NULL:
			break;
		case TYPE_BOOL:
			_bool = false;
			break;
		case TYPE_INT:
			_int = 0;
			break;
		case TYPE_UINT:
			_uint = 0;
			break;
		case TYPE_FLOAT:
			_float = 0;
			break;
		case TYPE_STRING:
			if (_string->owner) {
				delete _string->string;
			}

			delete _string;
			_string = nullptr;

			break;
		case TYPE_OBJECT:
			delete _object;
			_object = nullptr;

			break;
		case TYPE_POINTER:
			_pointer = nullptr;

			break;
		default:
			break;
	}

	_type = TYPE_NULL;
}
void Variant::zero() {
	switch (_type) {
		case TYPE_NULL:
			break;
		case TYPE_BOOL:
			_bool = false;
			break;
		case TYPE_INT:
			_int = 0;
			break;
		case TYPE_UINT:
			_uint = 0;
			break;
		case TYPE_FLOAT:
			_float = 0;
			break;
		case TYPE_STRING:
			_string->string->resize(0);
			break;
		case TYPE_OBJECT:
			_object->object = nullptr;
			_object->reference.unref();
			break;
		case TYPE_POINTER:
			_pointer = nullptr;
			break;
		default:
			break;
	}
}

void Variant::parse(const String &str) {
	if (str.is_int()) {
		set_int(str.to_int());
		return;
	}

	if (str.is_uint()) {
		set_uint(str.to_uint());
		return;
	}

	if (str.is_numeric()) {
		set_float(str.to_float());
		return;
	}

	if (str.is_bool()) {
		set_bool(str.to_bool());
		return;
	}

	set_string(str);
}
Variant Variant::parse_string(const String &str) {
	Variant v = Variant();

	v.parse(str);

	return v;
}

bool Variant::is_null() const {
	return _type == TYPE_NULL;
}
bool Variant::is_bool() const {
	return _type == TYPE_BOOL;
}
bool Variant::is_int() const {
	return _type == TYPE_INT;
}
bool Variant::is_uint() const {
	return _type == TYPE_UINT;
}
bool Variant::is_float() const {
	return _type == TYPE_FLOAT;
}
bool Variant::is_numeric() const {
	return _type == TYPE_INT || _type == TYPE_UINT || _type == TYPE_FLOAT;
}
bool Variant::is_string() const {
	return _type == TYPE_STRING;
}
bool Variant::is_object() const {
	return _type == TYPE_OBJECT;
}
bool Variant::is_pointer() const {
	return _type == TYPE_POINTER;
}
bool Variant::is_reference() const {
	if (_type == TYPE_OBJECT) {
		return _object->reference.is_valid();
	}

	return false;
}

bool Variant::is_primitive_type() const {
	return _type == TYPE_BOOL || _type == TYPE_INT || _type == TYPE_UINT || _type == TYPE_FLOAT;
}

bool Variant::is_simple_type() const {
	return _type == TYPE_BOOL || _type == TYPE_INT || _type == TYPE_UINT || _type == TYPE_FLOAT || _type == TYPE_STRING;
}

bool Variant::to_bool() const {
	return _bool;
}
int Variant::to_int() const {
	switch (_type) {
		case TYPE_NULL:
			return 0;
		case TYPE_BOOL:
			if (_bool) {
				return 1;
			} else {
				return 0;
			}
		case TYPE_INT:
		case TYPE_UINT:
			return _int;
		case TYPE_FLOAT:
			return static_cast<float>(_int);
		case TYPE_STRING:
			return _string->string->to_int();
		case TYPE_OBJECT:
		case TYPE_POINTER:
			// just read the value of the pointer as int
			// Could return 1 or 0, but this is almost the same, but hopefully it's more useful
			return _int;
		default:
			return 0;
	}
}
uint64_t Variant::to_uint() const {
	switch (_type) {
		case TYPE_NULL:
			return 0;
		case TYPE_BOOL:
			if (_bool) {
				return 1;
			} else {
				return 0;
			}
		case TYPE_INT:
		case TYPE_UINT:
			return _uint;
		case TYPE_FLOAT:
			return static_cast<uint64_t>(_float);
		case TYPE_STRING:
			return _string->string->to_uint();
		case TYPE_OBJECT:
		case TYPE_POINTER:
			// just read the value of the pointer as uint
			// Could return 1 or 0, but this is almost the same, but hopefully it's more useful
			return _uint;
		default:
			return 0;
	}
}
float Variant::to_float() const {
	switch (_type) {
		case TYPE_NULL:
			return 0;
		case TYPE_BOOL:
			if (_bool) {
				return 0;
			} else {
				return 1;
			}
		case TYPE_INT:
			return static_cast<float>(_int);
		case TYPE_UINT:
			return static_cast<float>(_uint);
		case TYPE_FLOAT:
			return _float;
		case TYPE_STRING:
			return _string->string->to_float();
		case TYPE_OBJECT:
		case TYPE_POINTER:
			if (_uint) {
				return 1;
			} else {
				return 0;
			}
		default:
			return 0;
	}
}
String Variant::to_string() const {
	switch (_type) {
		case TYPE_NULL:
			return "NULL";
		case TYPE_BOOL:
			if (Math::is_zero_approx(_float)) {
				return "false";
			} else {
				return "true";
			}
		case TYPE_INT:
			return String::num(_int);
		case TYPE_UINT:
			return String::num(_uint);
		case TYPE_FLOAT:
			return String::num(_float);
		case TYPE_STRING:
			return *(_string->string);
		case TYPE_OBJECT:
		case TYPE_POINTER:
			if (_uint) {
				return "[ Object ]";
			} else {
				return "[ Object (NULL) ]";
			}
		default:
			return "";
	}
}
Object *Variant::to_object() const {
	switch (_type) {
		case TYPE_NULL:
			return nullptr;
		case TYPE_BOOL:
			return nullptr;
		case TYPE_INT:
			return nullptr;
		case TYPE_UINT:
			return nullptr;
		case TYPE_FLOAT:
			return nullptr;
		case TYPE_STRING:
			return nullptr;
		case TYPE_OBJECT:
			return _object->object;
		case TYPE_POINTER:
			return nullptr;
		default:
			return nullptr;
	}
}
Reference *Variant::to_reference() const {
	switch (_type) {
		case TYPE_NULL:
			return nullptr;
		case TYPE_BOOL:
			return nullptr;
		case TYPE_INT:
			return nullptr;
		case TYPE_UINT:
			return nullptr;
		case TYPE_FLOAT:
			return nullptr;
		case TYPE_STRING:
			return nullptr;
		case TYPE_OBJECT:
			return Object::cast_to<Reference>(_object->object);
		case TYPE_POINTER:
			return nullptr;
		default:
			return nullptr;
	}
}
void *Variant::to_pointer() const {
	switch (_type) {
		case TYPE_NULL:
			return nullptr;
		case TYPE_BOOL:
			return nullptr;
		case TYPE_INT:
			return nullptr;
		case TYPE_UINT:
			return nullptr;
		case TYPE_FLOAT:
			return nullptr;
		case TYPE_STRING:
			return nullptr;
		case TYPE_OBJECT:
			return nullptr;
		case TYPE_POINTER:
			return _pointer;
		default:
			return nullptr;
	}
}
String *Variant::get_string_ptr() const {
	if (_type == TYPE_STRING) {
		return _string->string;
	}

	return nullptr;
}
bool Variant::is_string_owned() const {
	if (_type == TYPE_STRING) {
		return _string->owner;
	}

	return false;
}

void Variant::set_null() {
	clear();

	_type = TYPE_NULL;
}
void Variant::set_bool(const bool value) {
	clear();

	_type = TYPE_BOOL;
	_bool = value;
}
void Variant::set_int(const int value) {
	clear();

	_type = TYPE_INT;
	_int = value;
}
void Variant::set_uint(const uint64_t value) {
	clear();

	_type = TYPE_UINT;
	_uint = value;
}
void Variant::set_float(const float value) {
	clear();

	_type = TYPE_FLOAT;
	_float = value;
}
void Variant::set_float(const double value) {
	clear();

	_type = TYPE_FLOAT;
	_float = value;
}
void Variant::set_string(String *value, const bool copy) {
	clear();

	if (!value) {
		return;
	}

	_type = TYPE_STRING;

	_string = new StringData();

	if (copy) {
		_string->string = new String(*value);
		_string->owner = true;
	} else {
		_string->string = value;
		_string->owner = false;
	}
}
void Variant::set_string(const String &value, const bool copy) {
	clear();

	_type = TYPE_STRING;

	_string = new StringData();

	if (copy) {
		_string->string = new String(value);
		_string->owner = true;
	} else {
		_string->string = &const_cast<String &>(value);
		_string->owner = false;
	}
}
void Variant::set_object(Object *value) {
	clear();

	if (!value) {
		return;
	}

	_object = new ObjectData();
	_object->object = value;

	if (value->is_class_ptr(Reference::get_class_ptr_static())) {
		_object->reference = Ref<Reference>(Object::cast_to<Reference>(value));
	}
}
void Variant::set_pointer(void *value) {
	clear();

	_type = TYPE_POINTER;
	_pointer = value;
}
void Variant::set_variant(const Variant &value) {
	clear();

	switch (value._type) {
		case TYPE_NULL:
			break;
		case TYPE_BOOL:
			_bool = value._bool;
			break;
		case TYPE_INT:
			_int = value._int;
			break;
		case TYPE_UINT:
			_uint = value._uint;
			break;
		case TYPE_FLOAT:
			_float = value._float;
			break;
		case TYPE_STRING:
			set_string(value._string->string, true);
			break;
		case TYPE_OBJECT:
			set_object(value._object->object);
			break;
		case TYPE_POINTER:
			_pointer = value._pointer;
		default:
			break;
	}

	_type = value._type;
}

Variant::operator bool() const {
	return to_bool();
}
Variant::operator int() const {
	return to_int();
}
Variant::operator uint64_t() const {
	return to_uint();
}
Variant::operator float() const {
	return to_float();
}
Variant::operator double() const {
	return to_float();
}
Variant::operator String() const {
	return to_string();
}
Variant::operator Object *() const {
	return to_object();
}
Variant::operator Reference *() const {
	return to_reference();
}
Variant::operator void *() const {
	return to_pointer();
}

void Variant::operator=(const Variant &other) {
	set_variant(other);
}
bool Variant::operator==(const Variant &other) const {
	if (_type != other._type) {
		return false;
	}

	switch (_type) {
		case TYPE_NULL:
			return true;
		case TYPE_BOOL:
			return _bool == other._bool;
		case TYPE_INT:
			return _int == other._int;
		case TYPE_UINT:
			return _uint == other._uint;
		case TYPE_FLOAT:
			return _float == other._float;
		case TYPE_STRING:
			return (*_string->string) == (*other._string->string);
		case TYPE_OBJECT:
			return (_object->object) == (other._object->object);
		case TYPE_POINTER:
			return _pointer == other._pointer;
		default:
			break;
	}

	return false;
}
bool Variant::operator!=(const Variant &other) const {
	return !(operator==(other));
}
bool Variant::operator<(const Variant &other) const {
	switch (_type) {
		case TYPE_NULL: {
			if (other.is_null()) {
				return false;
			} else {
				return true;
			}
		}
		case TYPE_BOOL: {
			return _bool < other.to_bool();
		}
		case TYPE_INT:
			return _int < other.to_int();
			return _int == other._int;
		case TYPE_UINT:
			return _uint < other.to_uint();
			return _uint == other._uint;
		case TYPE_FLOAT:
			return _float < other.to_float();
			return _float == other._float;
		case TYPE_STRING:
			return (*_string->string) < other.to_string();
		case TYPE_OBJECT:
			return (_object->object) < other.to_object();
		case TYPE_POINTER:
			return _pointer < other.to_pointer();
		default:
			break;
	}

	return false;
}

Variant::Variant(const bool value) {
	_type = TYPE_BOOL;

	_bool = value;
}
Variant::Variant(const int value) {
	_type = TYPE_INT;

	_int = value;
}
Variant::Variant(const uint64_t value) {
	_type = TYPE_UINT;

	_uint = value;
}
Variant::Variant(const float value) {
	_type = TYPE_FLOAT;

	_float = value;
}
Variant::Variant(const double value) {
	_type = TYPE_FLOAT;

	_float = value;
}
Variant::Variant(String *value, bool copy) {
	_type = TYPE_NULL;

	set_string(value, copy);
}
Variant::Variant(const String &value, bool copy) {
	_type = TYPE_NULL;

	set_string(value, copy);
}
Variant::Variant(Object *value) {
	_type = TYPE_NULL;

	set_object(value);
}
Variant::Variant(void *value) {
	_type = TYPE_NULL;

	set_pointer(value);
}
Variant::Variant(const Variant &value) {
	_type = TYPE_NULL;

	set_variant(value);
}

Variant::Variant() {
	_type = TYPE_NULL;
}

Variant::~Variant() {
	clear();
}