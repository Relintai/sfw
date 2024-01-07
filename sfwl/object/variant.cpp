/*************************************************************************/
/*  variant.cpp                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "variant.h"

#include "core/math_funcs.h"

#include "object/core_string_names.h"
#include "object/object.h"
#include "object/object_rc.h"
#include "object/resource.h"
//--STRIP

String Variant::get_type_name(Variant::Type p_type) {
	switch (p_type) {
		case NIL: {
			return "Nil";
		} break;

		// atomic types
		case BOOL: {
			return "bool";
		} break;
		case INT: {
			return "int";

		} break;
		case REAL: {
			return "float";

		} break;
		case STRING: {
			return "String";
		} break;

		case OBJECT: {
			return "Object";
		} break;
		case STRING_NAME: {
			return "StringName";
		} break;
		case DICTIONARY: {
			return "Dictionary";
		} break;
		case ARRAY: {
			return "Array";
		} break;

		// arrays
		case POOL_BYTE_ARRAY: {
			return "PoolByteArray";
		} break;
		case POOL_INT_ARRAY: {
			return "PoolIntArray";
		} break;
		case POOL_REAL_ARRAY: {
			return "PoolRealArray";
		} break;
		case POOL_STRING_ARRAY: {
			return "PoolStringArray";
		} break;
		default: {
		}
	}

	return "";
}

bool Variant::can_convert(Variant::Type p_type_from, Variant::Type p_type_to) {
	if (p_type_from == p_type_to) {
		return true;
	}
	if (p_type_to == NIL && p_type_from != NIL) { //nil can convert to anything
		return true;
	}

	if (p_type_from == NIL) {
		return (p_type_to == OBJECT);
	};

	const Type *valid_types = nullptr;
	const Type *invalid_types = nullptr;

	switch (p_type_to) {
		case NIL: {
			//can't
		} break;
		case BOOL: {
			static const Type valid[] = {
				INT,
				REAL,
				STRING,
				NIL,
			};

			valid_types = valid;
		} break;
		case INT: {
			static const Type valid[] = {
				BOOL,
				REAL,
				STRING,
				NIL,
			};

			valid_types = valid;
		} break;
		case REAL: {
			static const Type valid[] = {
				BOOL,
				INT,
				STRING,
				NIL,
			};

			valid_types = valid;
		} break;
		case STRING: {
			static const Type invalid[] = {
				OBJECT,
				NIL
			};

			invalid_types = invalid;
		} break;
		case OBJECT: {
			static const Type valid[] = {
				NIL
			};

			valid_types = valid;
		} break;
		case STRING_NAME: {
			static const Type valid[] = {
				STRING,
				NIL
			};

			valid_types = valid;
		} break;
		case DICTIONARY: {
			//can't
		} break;
		case ARRAY: {
			static const Type valid[] = {
				POOL_BYTE_ARRAY,
				POOL_INT_ARRAY,
				POOL_STRING_ARRAY,
				POOL_REAL_ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		// arrays
		case POOL_BYTE_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		case POOL_INT_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};
			valid_types = valid;
		} break;
		case POOL_REAL_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		case POOL_STRING_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};
			valid_types = valid;
		} break;
		default: {
		}
	}

	if (valid_types) {
		int i = 0;
		while (valid_types[i] != NIL) {
			if (p_type_from == valid_types[i]) {
				return true;
			}
			i++;
		}

	} else if (invalid_types) {
		int i = 0;
		while (invalid_types[i] != NIL) {
			if (p_type_from == invalid_types[i]) {
				return false;
			}
			i++;
		}

		return true;
	}

	return false;
}

bool Variant::can_convert_strict(Variant::Type p_type_from, Variant::Type p_type_to) {
	if (p_type_from == p_type_to) {
		return true;
	}
	if (p_type_to == NIL && p_type_from != NIL) { //nil can convert to anything
		return true;
	}

	if (p_type_from == NIL) {
		return (p_type_to == OBJECT);
	};

	const Type *valid_types = nullptr;

	switch (p_type_to) {
		case NIL: {
			//can't, also already handled
		} break;
		case BOOL: {
			static const Type valid[] = {
				INT,
				REAL,
				//STRING,
				NIL,
			};

			valid_types = valid;
		} break;
		case INT: {
			static const Type valid[] = {
				BOOL,
				REAL,
				//STRING,
				NIL,
			};

			valid_types = valid;

		} break;
		case REAL: {
			static const Type valid[] = {
				BOOL,
				INT,
				//STRING,
				NIL,
			};

			valid_types = valid;

		} break;
		case STRING: {
			static const Type valid[] = {
				STRING_NAME,
				NIL
			};

			valid_types = valid;
		} break;
		case OBJECT: {
			static const Type valid[] = {
				NIL
			};

			valid_types = valid;
		} break;
		case STRING_NAME: {
			static const Type valid[] = {
				STRING,
				NIL
			};

			valid_types = valid;
		} break;
		case DICTIONARY: {
			//Can't
		} break;
		case ARRAY: {
			static const Type valid[] = {
				POOL_BYTE_ARRAY,
				POOL_INT_ARRAY,
				POOL_STRING_ARRAY,
				POOL_REAL_ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		// arrays
		case POOL_BYTE_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		case POOL_INT_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};
			valid_types = valid;
		} break;
		case POOL_REAL_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		case POOL_STRING_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		default: {
		}
	}

	if (valid_types) {
		int i = 0;
		while (valid_types[i] != NIL) {
			if (p_type_from == valid_types[i]) {
				return true;
			}
			i++;
		}
	}

	return false;
}

bool Variant::deep_equal(const Variant &p_variant, int p_recursion_count) const {
	ERR_FAIL_COND_V_MSG(p_recursion_count > MAX_RECURSION, true, "Max recursion reached");

	// Containers must be handled with recursivity checks
	switch (type) {
		case Variant::Type::DICTIONARY: {
			if (p_variant.type != Variant::Type::DICTIONARY) {
				return false;
			}

			const Dictionary v1_as_d = Dictionary(*this);
			const Dictionary v2_as_d = Dictionary(p_variant);

			return v1_as_d.deep_equal(v2_as_d, p_recursion_count + 1);
		} break;
		case Variant::Type::ARRAY: {
			if (p_variant.type != Variant::Type::ARRAY) {
				return false;
			}

			const Array v1_as_a = Array(*this);
			const Array v2_as_a = Array(p_variant);

			return v1_as_a.deep_equal(v2_as_a, p_recursion_count + 1);
		} break;
		default: {
			return *this == p_variant;
		} break;
	}
}

bool Variant::operator==(const Variant &p_variant) const {
	if (type != p_variant.type) { //evaluation of operator== needs to be more strict
		return false;
	}
	bool v;
	Variant r;
	evaluate(OP_EQUAL, *this, p_variant, r, v);
	return r;
}

bool Variant::operator!=(const Variant &p_variant) const {
	if (type != p_variant.type) { //evaluation of operator== needs to be more strict
		return true;
	}
	bool v;
	Variant r;
	evaluate(OP_NOT_EQUAL, *this, p_variant, r, v);
	return r;
}

bool Variant::operator<(const Variant &p_variant) const {
	if (type != p_variant.type) { //if types differ, then order by type first
		return type < p_variant.type;
	}
	bool v;
	Variant r;
	evaluate(OP_LESS, *this, p_variant, r, v);
	return r;
}

bool Variant::is_zero() const {
	switch (type) {
		case NIL: {
			return true;
		} break;

		// atomic types
		case BOOL: {
			return !(_data._bool);
		} break;
		case INT: {
			return _data._int == 0;
		} break;
		case REAL: {
			return _data._real == 0;
		} break;
		case STRING: {
			return *reinterpret_cast<const String *>(_data._mem) == String();
		} break;

		case OBJECT: {
			return _UNSAFE_OBJ_PROXY_PTR(*this) == nullptr;
		} break;
		case STRING_NAME: {
			return *reinterpret_cast<const StringName *>(_data._mem) != StringName();
		} break;
		case DICTIONARY: {
			return reinterpret_cast<const Dictionary *>(_data._mem)->empty();
		} break;
		case ARRAY: {
			return reinterpret_cast<const Array *>(_data._mem)->empty();
		} break;

		// arrays
		case POOL_BYTE_ARRAY: {
			return reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem)->size() == 0;
		} break;
		case POOL_INT_ARRAY: {
			return reinterpret_cast<const PoolVector<int> *>(_data._mem)->size() == 0;
		} break;
		case POOL_REAL_ARRAY: {
			return reinterpret_cast<const PoolVector<real_t> *>(_data._mem)->size() == 0;
		} break;
		case POOL_STRING_ARRAY: {
			return reinterpret_cast<const PoolVector<String> *>(_data._mem)->size() == 0;
		} break;
		default: {
		}
	}

	return false;
}

bool Variant::is_one() const {
	switch (type) {
		case NIL: {
			return true;
		} break;

		// atomic types
		case BOOL: {
			return _data._bool;
		} break;
		case INT: {
			return _data._int == 1;
		} break;
		case REAL: {
			return _data._real == 1;
		} break;

		default: {
			return !is_zero();
		}
	}

	return false;
}

ObjectID Variant::get_object_instance_id() const {
	if (unlikely(type != OBJECT)) {
		return 0;
	} else if (likely(_get_obj().rc)) {
		return _get_obj().rc->instance_id;
	} else if (likely(!_get_obj().ref.is_null())) {
		return _REF_OBJ_PTR(*this)->get_instance_id();
	} else {
		return 0;
	}
}

bool Variant::is_invalid_object() const {
	return type == OBJECT && _get_obj().rc && !_get_obj().rc->get_ptr();
}

void Variant::reference(const Variant &p_variant) {
	switch (type) {
		case NIL:
		case BOOL:
		case INT:
		case REAL:
			break;
		default:
			clear();
	}

	type = p_variant.type;

	switch (p_variant.type) {
		case NIL: {
			// none
		} break;

		// atomic types
		case BOOL: {
			_data._bool = p_variant._data._bool;
		} break;
		case INT: {
			_data._int = p_variant._data._int;
		} break;
		case REAL: {
			_data._real = p_variant._data._real;
		} break;
		case STRING: {
			memnew_placement(_data._mem, String(*reinterpret_cast<const String *>(p_variant._data._mem)));
		} break;

		case OBJECT: {
			memnew_placement(_data._mem, ObjData(p_variant._get_obj()));
			if (likely(_get_obj().rc)) {
				_get_obj().rc->increment();
			}
		} break;
		case STRING_NAME: {
			memnew_placement(_data._mem, StringName(*reinterpret_cast<const StringName *>(p_variant._data._mem)));
		} break;
		case DICTIONARY: {
			memnew_placement(_data._mem, Dictionary(*reinterpret_cast<const Dictionary *>(p_variant._data._mem)));
		} break;
		case ARRAY: {
			memnew_placement(_data._mem, Array(*reinterpret_cast<const Array *>(p_variant._data._mem)));
		} break;

		// arrays
		case POOL_BYTE_ARRAY: {
			memnew_placement(_data._mem, PoolVector<uint8_t>(*reinterpret_cast<const PoolVector<uint8_t> *>(p_variant._data._mem)));
		} break;
		case POOL_INT_ARRAY: {
			memnew_placement(_data._mem, PoolVector<int>(*reinterpret_cast<const PoolVector<int> *>(p_variant._data._mem)));
		} break;
		case POOL_REAL_ARRAY: {
			memnew_placement(_data._mem, PoolVector<real_t>(*reinterpret_cast<const PoolVector<real_t> *>(p_variant._data._mem)));
		} break;
		case POOL_STRING_ARRAY: {
			memnew_placement(_data._mem, PoolVector<String>(*reinterpret_cast<const PoolVector<String> *>(p_variant._data._mem)));
		} break;
		default: {
		}
	}
}

void Variant::zero() {
	switch (type) {
		case NIL:
			break;
		case BOOL:
			this->_data._bool = false;
			break;
		case INT:
			this->_data._int = 0;
			break;
		case REAL:
			this->_data._real = 0;
			break;
		default:
			this->clear();
			break;
	}
}

void Variant::clear() {
	switch (type) {
		/*
		// no point, they don't allocate memory
		BOOL,
		INT,
		REAL,
		*/
		case STRING: {
			reinterpret_cast<String *>(_data._mem)->~String();
		} break;

		// misc types
		case OBJECT: {
			if (likely(_get_obj().rc)) {
				if (unlikely(_get_obj().rc->decrement())) {
					memdelete(_get_obj().rc);
				}
			} else {
				_get_obj().ref.unref();
			}
		} break;
		case STRING_NAME: {
			reinterpret_cast<StringName *>(_data._mem)->~StringName();
		} break;
		case DICTIONARY: {
			reinterpret_cast<Dictionary *>(_data._mem)->~Dictionary();
		} break;
		case ARRAY: {
			reinterpret_cast<Array *>(_data._mem)->~Array();
		} break;

		// arrays
		case POOL_BYTE_ARRAY: {
			reinterpret_cast<PoolVector<uint8_t> *>(_data._mem)->~PoolVector<uint8_t>();
		} break;
		case POOL_INT_ARRAY: {
			reinterpret_cast<PoolVector<int> *>(_data._mem)->~PoolVector<int>();
		} break;
		case POOL_REAL_ARRAY: {
			reinterpret_cast<PoolVector<real_t> *>(_data._mem)->~PoolVector<real_t>();
		} break;
		case POOL_STRING_ARRAY: {
			reinterpret_cast<PoolVector<String> *>(_data._mem)->~PoolVector<String>();
		} break;
		default: {
		} /* not needed */
	}

	type = NIL;
}

Variant::operator signed int() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}
Variant::operator unsigned int() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}

Variant::operator int64_t() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int64();
		default: {
			return 0;
		}
	}
}

/*
Variant::operator long unsigned int() const {

	switch( type ) {

		case NIL: return 0;
		case BOOL: return _data._bool ? 1 : 0;
		case INT: return _data._int;
		case REAL: return _data._real;
		case STRING: return operator String().to_int();
		default: {

			return 0;
		}
	}

	return 0;
};
*/

Variant::operator uint64_t() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}

#ifdef NEED_LONG_INT
Variant::operator signed long() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}

	return 0;
};

Variant::operator unsigned long() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}

	return 0;
};
#endif

Variant::operator signed short() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}
Variant::operator unsigned short() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}
Variant::operator signed char() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}
Variant::operator unsigned char() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}

Variant::operator CharType() const {
	return operator unsigned int();
}

Variant::operator float() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1.0 : 0.0;
		case INT:
			return (float)_data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_double();
		default: {
			return 0;
		}
	}
}
Variant::operator double() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1.0 : 0.0;
		case INT:
			return (double)_data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_double();
		default: {
			return 0;
		}
	}
}

Variant::operator StringName() const {
	if (type == STRING_NAME) {
		return *reinterpret_cast<const StringName *>(_data._mem);
	}

	return StringName(operator String());
}

struct _VariantStrPair {
	String key;
	String value;

	bool operator<(const _VariantStrPair &p) const {
		return key < p.key;
	}
};

Variant::operator String() const {
	List<const void *> stack;

	return stringify(stack);
}

template <class T>
String stringify_vector(const T &vec, List<const void *> &stack) {
	String str("[");
	for (int i = 0; i < vec.size(); i++) {
		if (i > 0) {
			str += ", ";
		}
		str = str + Variant(vec[i]).stringify(stack);
	}
	str += "]";
	return str;
}

String Variant::stringify(List<const void *> &stack) const {
	switch (type) {
		case NIL:
			return "Null";
		case BOOL:
			return _data._bool ? "True" : "False";
		case INT:
			return itos(_data._int);
		case REAL:
			return rtos(_data._real);
		case STRING:
			return *reinterpret_cast<const String *>(_data._mem);
		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (likely(obj)) {
				return obj->to_string();
			} else {
				if (_get_obj().rc) {
					return "[Deleted Object]";
				}
				return "[Object:null]";
			}
		} break;
		case STRING_NAME:
			return operator StringName();
		case DICTIONARY: {
			const Dictionary &d = *reinterpret_cast<const Dictionary *>(_data._mem);
			if (stack.find(d.id())) {
				return "{...}";
			}

			stack.push_back(d.id());

			//const String *K=NULL;
			String str("{");
			List<Variant> keys;
			d.get_key_list(&keys);

			Vector<_VariantStrPair> pairs;

			for (List<Variant>::Element *E = keys.front(); E; E = E->next()) {
				_VariantStrPair sp;
				sp.key = E->get().stringify(stack);
				sp.value = d[E->get()].stringify(stack);

				pairs.push_back(sp);
			}

			pairs.sort();

			for (int i = 0; i < pairs.size(); i++) {
				if (i > 0) {
					str += ", ";
				}
				str += pairs[i].key + ":" + pairs[i].value;
			}
			str += "}";

			stack.erase(d.id());
			return str;
		} break;
		case ARRAY: {
			Array arr = operator Array();
			if (stack.find(arr.id())) {
				return "[...]";
			}
			stack.push_back(arr.id());
			String str = stringify_vector(arr, stack);
			stack.erase(arr.id());
			return str;

		} break;

		case POOL_BYTE_ARRAY: {
			return stringify_vector(operator PoolVector<uint8_t>(), stack);
		} break;
		case POOL_INT_ARRAY: {
			return stringify_vector(operator PoolVector<int>(), stack);
		} break;
		case POOL_REAL_ARRAY: {
			return stringify_vector(operator PoolVector<real_t>(), stack);
		} break;
		case POOL_STRING_ARRAY: {
			return stringify_vector(operator PoolVector<String>(), stack);
		} break;

		default: {
			return "[" + get_type_name(type) + "]";
		}
	}

	return "";
}

Variant::operator RefPtr() const {
	if (type == OBJECT) {
		return _get_obj().ref;
	} else {
		return RefPtr();
	}
}

Variant::operator Object *() const {
	if (type == OBJECT) {
		return _OBJ_PTR(*this);
	} else {
		return nullptr;
	}
}

template <class DA, class SA>
inline DA _convert_array(const SA &p_array) {
	DA da;
	da.resize(p_array.size());

	for (int i = 0; i < p_array.size(); i++) {
		da.set(i, Variant(p_array.get(i)));
	}

	return da;
}

template <class DA>
inline DA _convert_array_from_variant(const Variant &p_variant) {
	switch (p_variant.get_type()) {
		case Variant::ARRAY: {
			return _convert_array<DA, Array>(p_variant.operator Array());
		}
		case Variant::POOL_BYTE_ARRAY: {
			return _convert_array<DA, PoolVector<uint8_t>>(p_variant.operator PoolVector<uint8_t>());
		}
		case Variant::POOL_INT_ARRAY: {
			return _convert_array<DA, PoolVector<int>>(p_variant.operator PoolVector<int>());
		}
		case Variant::POOL_REAL_ARRAY: {
			return _convert_array<DA, PoolVector<real_t>>(p_variant.operator PoolVector<real_t>());
		}
		case Variant::POOL_STRING_ARRAY: {
			return _convert_array<DA, PoolVector<String>>(p_variant.operator PoolVector<String>());
		}
		default: {
			return DA();
		}
	}
}

Variant::operator Dictionary() const {
	if (type == DICTIONARY) {
		return *reinterpret_cast<const Dictionary *>(_data._mem);
	} else {
		return Dictionary();
	}
}

Variant::operator Array() const {
	if (type == ARRAY) {
		return *reinterpret_cast<const Array *>(_data._mem);
	} else {
		return _convert_array_from_variant<Array>(*this);
	}
}

Variant::operator PoolVector<uint8_t>() const {
	if (type == POOL_BYTE_ARRAY) {
		return *reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
	} else {
		return _convert_array_from_variant<PoolVector<uint8_t>>(*this);
	}
}
Variant::operator PoolVector<int>() const {
	if (type == POOL_INT_ARRAY) {
		return *reinterpret_cast<const PoolVector<int> *>(_data._mem);
	} else {
		return _convert_array_from_variant<PoolVector<int>>(*this);
	}
}
Variant::operator PoolVector<real_t>() const {
	if (type == POOL_REAL_ARRAY) {
		return *reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
	} else {
		return _convert_array_from_variant<PoolVector<real_t>>(*this);
	}
}

Variant::operator PoolVector<String>() const {
	if (type == POOL_STRING_ARRAY) {
		return *reinterpret_cast<const PoolVector<String> *>(_data._mem);
	} else {
		return _convert_array_from_variant<PoolVector<String>>(*this);
	}
}

/* helpers */

Variant::operator Vector<Variant>() const {
	Array from = operator Array();
	Vector<Variant> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}

Variant::operator Vector<uint8_t>() const {
	PoolVector<uint8_t> from = operator PoolVector<uint8_t>();
	Vector<uint8_t> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}
Variant::operator Vector<int>() const {
	PoolVector<int> from = operator PoolVector<int>();
	Vector<int> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}
Variant::operator Vector<real_t>() const {
	PoolVector<real_t> from = operator PoolVector<real_t>();
	Vector<real_t> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}

Variant::operator Vector<String>() const {
	PoolVector<String> from = operator PoolVector<String>();
	Vector<String> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}
Variant::operator Vector<StringName>() const {
	PoolVector<String> from = operator PoolVector<String>();
	Vector<StringName> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}

Variant::operator Margin() const {
	return (Margin) operator int();
}
Variant::operator Side() const {
	return (Side) operator int();
}
Variant::operator Orientation() const {
	return (Orientation) operator int();
}

Variant::Variant(bool p_bool) {
	type = BOOL;
	_data._bool = p_bool;
}

/*
Variant::Variant(long unsigned int p_long) {

	type=INT;
	_data._int=p_long;
};
*/

Variant::Variant(signed int p_int) {
	type = INT;
	_data._int = p_int;
}
Variant::Variant(unsigned int p_int) {
	type = INT;
	_data._int = p_int;
}

#ifdef NEED_LONG_INT

Variant::Variant(signed long p_int) {
	type = INT;
	_data._int = p_int;
}
Variant::Variant(unsigned long p_int) {
	type = INT;
	_data._int = p_int;
}
#endif

Variant::Variant(int64_t p_int) {
	type = INT;
	_data._int = p_int;
}

Variant::Variant(uint64_t p_int) {
	type = INT;
	_data._int = p_int;
}

Variant::Variant(signed short p_short) {
	type = INT;
	_data._int = p_short;
}
Variant::Variant(unsigned short p_short) {
	type = INT;
	_data._int = p_short;
}
Variant::Variant(signed char p_char) {
	type = INT;
	_data._int = p_char;
}
Variant::Variant(unsigned char p_char) {
	type = INT;
	_data._int = p_char;
}
Variant::Variant(float p_float) {
	type = REAL;
	_data._real = p_float;
}
Variant::Variant(double p_double) {
	type = REAL;
	_data._real = p_double;
}

Variant::Variant(const StringName &p_string) {
	type = STRING_NAME;
	memnew_placement(_data._mem, StringName(p_string));
}
Variant::Variant(const String &p_string) {
	type = STRING;
	memnew_placement(_data._mem, String(p_string));
}

Variant::Variant(const char *const p_cstring) {
	type = STRING;
	memnew_placement(_data._mem, String((const char *)p_cstring));
}

Variant::Variant(const CharType *p_wstring) {
	type = STRING;
	memnew_placement(_data._mem, String(p_wstring));
}

Variant::Variant(const RefPtr &p_resource) {
	type = OBJECT;
	memnew_placement(_data._mem, ObjData);
	_get_obj().rc = nullptr;
	_get_obj().ref = p_resource;
}

Variant::Variant(const Object *p_object) {
	type = OBJECT;
	Object *obj = const_cast<Object *>(p_object);

	memnew_placement(_data._mem, ObjData);
	Reference *ref = Object::cast_to<Reference>(obj);
	if (unlikely(ref)) {
		*reinterpret_cast<Ref<Reference> *>(_get_obj().ref.get_data()) = Ref<Reference>(ref);
		_get_obj().rc = nullptr;
	} else {
		_get_obj().rc = likely(obj) ? obj->_use_rc() : nullptr;
	}
}

Variant::Variant(const Dictionary &p_dictionary) {
	type = DICTIONARY;
	memnew_placement(_data._mem, Dictionary(p_dictionary));
}

Variant::Variant(const Array &p_array) {
	type = ARRAY;
	memnew_placement(_data._mem, Array(p_array));
}

Variant::Variant(const PoolVector<uint8_t> &p_raw_array) {
	type = POOL_BYTE_ARRAY;
	memnew_placement(_data._mem, PoolVector<uint8_t>(p_raw_array));
}
Variant::Variant(const PoolVector<int> &p_int_array) {
	type = POOL_INT_ARRAY;
	memnew_placement(_data._mem, PoolVector<int>(p_int_array));
}
Variant::Variant(const PoolVector<real_t> &p_real_array) {
	type = POOL_REAL_ARRAY;
	memnew_placement(_data._mem, PoolVector<real_t>(p_real_array));
}
Variant::Variant(const PoolVector<String> &p_string_array) {
	type = POOL_STRING_ARRAY;
	memnew_placement(_data._mem, PoolVector<String>(p_string_array));
}

/* helpers */

Variant::Variant(const Vector<Variant> &p_array) {
	type = NIL;
	Array v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

Variant::Variant(const Vector<uint8_t> &p_array) {
	type = NIL;
	PoolVector<uint8_t> v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

Variant::Variant(const Vector<int> &p_array) {
	type = NIL;
	PoolVector<int> v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

Variant::Variant(const Vector<real_t> &p_array) {
	type = NIL;
	PoolVector<real_t> v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

Variant::Variant(const Vector<String> &p_array) {
	type = NIL;
	PoolVector<String> v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

Variant::Variant(const Vector<StringName> &p_array) {
	type = NIL;
	PoolVector<String> v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

void Variant::operator=(const Variant &p_variant) {
	if (unlikely(this == &p_variant)) {
		return;
	}

	if (unlikely(type != p_variant.type)) {
		reference(p_variant);
		return;
	}

	switch (p_variant.type) {
		case NIL: {
			// none
		} break;

		// atomic types
		case BOOL: {
			_data._bool = p_variant._data._bool;
		} break;
		case INT: {
			_data._int = p_variant._data._int;
		} break;
		case REAL: {
			_data._real = p_variant._data._real;
		} break;
		case STRING: {
			*reinterpret_cast<String *>(_data._mem) = *reinterpret_cast<const String *>(p_variant._data._mem);
		} break;
		case OBJECT: {
			if (likely(_get_obj().rc)) {
				if (unlikely(_get_obj().rc->decrement())) {
					memdelete(_get_obj().rc);
				}
			}
			*reinterpret_cast<ObjData *>(_data._mem) = p_variant._get_obj();
			if (likely(_get_obj().rc)) {
				_get_obj().rc->increment();
			}
		} break;
		case STRING_NAME: {
			*reinterpret_cast<StringName *>(_data._mem) = *reinterpret_cast<const StringName *>(p_variant._data._mem);
		} break;
		case DICTIONARY: {
			*reinterpret_cast<Dictionary *>(_data._mem) = *reinterpret_cast<const Dictionary *>(p_variant._data._mem);
		} break;
		case ARRAY: {
			*reinterpret_cast<Array *>(_data._mem) = *reinterpret_cast<const Array *>(p_variant._data._mem);
		} break;

		// arrays
		case POOL_BYTE_ARRAY: {
			*reinterpret_cast<PoolVector<uint8_t> *>(_data._mem) = *reinterpret_cast<const PoolVector<uint8_t> *>(p_variant._data._mem);
		} break;
		case POOL_INT_ARRAY: {
			*reinterpret_cast<PoolVector<int> *>(_data._mem) = *reinterpret_cast<const PoolVector<int> *>(p_variant._data._mem);
		} break;
		case POOL_REAL_ARRAY: {
			*reinterpret_cast<PoolVector<real_t> *>(_data._mem) = *reinterpret_cast<const PoolVector<real_t> *>(p_variant._data._mem);
		} break;
		case POOL_STRING_ARRAY: {
			*reinterpret_cast<PoolVector<String> *>(_data._mem) = *reinterpret_cast<const PoolVector<String> *>(p_variant._data._mem);
		} break;
		default: {
		}
	}
}

Variant::Variant(const Variant &p_variant) {
	type = NIL;
	reference(p_variant);
}

/*
Variant::~Variant() {

	clear();
}*/

uint32_t Variant::hash() const {
	return recursive_hash(0);
}

uint32_t Variant::recursive_hash(int p_recursion_count) const {
	switch (type) {
		case NIL: {
			return 0;
		} break;

		case BOOL: {
			return _data._bool ? 1 : 0;
		} break;
		case INT: {
			return hash_one_uint64((uint64_t)_data._int);
		} break;
		case REAL: {
			return hash_murmur3_one_float(_data._real);
		} break;
		case STRING: {
			return reinterpret_cast<const String *>(_data._mem)->hash();
		} break;
		case OBJECT: {
			return hash_one_uint64(hash_make_uint64_t(_UNSAFE_OBJ_PROXY_PTR(*this)));
		} break;
		case STRING_NAME: {
			return reinterpret_cast<const StringName *>(_data._mem)->hash();
		} break;
		case DICTIONARY: {
			return reinterpret_cast<const Dictionary *>(_data._mem)->recursive_hash(p_recursion_count);
		} break;
		case ARRAY: {
			const Array &arr = *reinterpret_cast<const Array *>(_data._mem);
			return arr.recursive_hash(p_recursion_count);
		} break;

		case POOL_BYTE_ARRAY: {
			const PoolVector<uint8_t> &arr = *reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
			int len = arr.size();
			if (likely(len)) {
				PoolVector<uint8_t>::Read r = arr.read();
				return hash_murmur3_buffer((uint8_t *)&r[0], len);
			} else {
				return hash_murmur3_one_64(0);
			}

		} break;
		case POOL_INT_ARRAY: {
			const PoolVector<int> &arr = *reinterpret_cast<const PoolVector<int> *>(_data._mem);
			int len = arr.size();
			if (likely(len)) {
				PoolVector<int>::Read r = arr.read();
				return hash_murmur3_buffer((uint8_t *)&r[0], len * sizeof(int));
			} else {
				return hash_murmur3_one_64(0);
			}

		} break;
		case POOL_REAL_ARRAY: {
			const PoolVector<real_t> &arr = *reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
			int len = arr.size();

			if (likely(len)) {
				PoolVector<real_t>::Read r = arr.read();
				uint32_t h = HASH_MURMUR3_SEED;

				for (int i = 0; i < len; i++) {
					h = hash_murmur3_one_real(r[i], h);
				}

				return hash_fmix32(h);
			} else {
				return hash_murmur3_one_real(0.0);
			}

		} break;
		case POOL_STRING_ARRAY: {
			uint32_t hash = HASH_MURMUR3_SEED;
			const PoolVector<String> &arr = *reinterpret_cast<const PoolVector<String> *>(_data._mem);
			int len = arr.size();

			if (likely(len)) {
				PoolVector<String>::Read r = arr.read();

				for (int i = 0; i < len; i++) {
					hash = hash_murmur3_one_32(r[i].hash(), hash);
				}

				hash = hash_fmix32(hash);
			}

			return hash;
		} break;
		default: {
		}
	}

	return 0;
}

#define hash_compare_scalar(p_lhs, p_rhs) \
	(((p_lhs) == (p_rhs)) || (Math::is_nan(p_lhs) && Math::is_nan(p_rhs)))

#define hash_compare_vector2(p_lhs, p_rhs)        \
	(hash_compare_scalar((p_lhs).x, (p_rhs).x) && \
			hash_compare_scalar((p_lhs).y, (p_rhs).y))

#define hash_compare_vector2i(p_lhs, p_rhs) \
	(((p_lhs).x == (p_rhs).x) &&            \
			((p_lhs).y == (p_rhs).y))

#define hash_compare_vector3(p_lhs, p_rhs)               \
	(hash_compare_scalar((p_lhs).x, (p_rhs).x) &&        \
			hash_compare_scalar((p_lhs).y, (p_rhs).y) && \
			hash_compare_scalar((p_lhs).z, (p_rhs).z))

#define hash_compare_vector3i(p_lhs, p_rhs) \
	(((p_lhs).x == (p_rhs).x) &&            \
			((p_lhs).y == (p_rhs).y) &&     \
			((p_lhs).z == (p_rhs).z))

#define hash_compare_vector4(p_lhs, p_rhs)               \
	(hash_compare_scalar((p_lhs).x, (p_rhs).x) &&        \
			hash_compare_scalar((p_lhs).y, (p_rhs).y) && \
			hash_compare_scalar((p_lhs).z, (p_rhs).z) && \
			hash_compare_scalar((p_lhs).w, (p_rhs).w))

#define hash_compare_vector4i(p_lhs, p_rhs) \
	(((p_lhs).x == (p_rhs).x) &&            \
			((p_lhs).y == (p_rhs).y) &&     \
			((p_lhs).z == (p_rhs).z) &&     \
			((p_lhs).w == (p_rhs).w))

#define hash_compare_quat(p_lhs, p_rhs)                  \
	(hash_compare_scalar((p_lhs).x, (p_rhs).x) &&        \
			hash_compare_scalar((p_lhs).y, (p_rhs).y) && \
			hash_compare_scalar((p_lhs).z, (p_rhs).z) && \
			hash_compare_scalar((p_lhs).w, (p_rhs).w))

#define hash_compare_color(p_lhs, p_rhs)                 \
	(hash_compare_scalar((p_lhs).r, (p_rhs).r) &&        \
			hash_compare_scalar((p_lhs).g, (p_rhs).g) && \
			hash_compare_scalar((p_lhs).b, (p_rhs).b) && \
			hash_compare_scalar((p_lhs).a, (p_rhs).a))

#define hash_compare_pool_array(p_lhs, p_rhs, p_type, p_compare_func)                   \
	const PoolVector<p_type> &l = *reinterpret_cast<const PoolVector<p_type> *>(p_lhs); \
	const PoolVector<p_type> &r = *reinterpret_cast<const PoolVector<p_type> *>(p_rhs); \
                                                                                        \
	if (l.size() != r.size())                                                           \
		return false;                                                                   \
                                                                                        \
	PoolVector<p_type>::Read lr = l.read();                                             \
	PoolVector<p_type>::Read rr = r.read();                                             \
                                                                                        \
	for (int i = 0; i < l.size(); ++i) {                                                \
		if (!p_compare_func((lr[i]), (rr[i])))                                          \
			return false;                                                               \
	}                                                                                   \
                                                                                        \
	return true

bool Variant::hash_compare(const Variant &p_variant) const {
	if (type != p_variant.type) {
		return false;
	}

	switch (type) {
		//BOOL
		case INT: {
			return _data._int == p_variant._data._int;
		} break;
		case REAL: {
			return hash_compare_scalar(_data._real, p_variant._data._real);
		} break;
		case STRING: {
			return *reinterpret_cast<const String *>(_data._mem) == *reinterpret_cast<const String *>(p_variant._data._mem);
		} break;
		case ARRAY: {
			const Array &l = *(reinterpret_cast<const Array *>(_data._mem));
			const Array &r = *(reinterpret_cast<const Array *>(p_variant._data._mem));

			if (l.size() != r.size()) {
				return false;
			}

			for (int i = 0; i < l.size(); ++i) {
				if (!l[i].hash_compare(r[i])) {
					return false;
				}
			}

			return true;
		} break;

		case POOL_REAL_ARRAY: {
			hash_compare_pool_array(_data._mem, p_variant._data._mem, real_t, hash_compare_scalar);
		} break;
		default:
			bool v;
			Variant r;
			evaluate(OP_EQUAL, *this, p_variant, r, v);
			return r;
	}

	return false;
}

bool Variant::is_ref() const {
	return type == OBJECT && !_get_obj().ref.is_null();
}

Vector<Variant> varray() {
	return Vector<Variant>();
}

Vector<Variant> varray(const Variant &p_arg1) {
	Vector<Variant> v;
	v.push_back(p_arg1);
	return v;
}
Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2) {
	Vector<Variant> v;
	v.push_back(p_arg1);
	v.push_back(p_arg2);
	return v;
}
Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3) {
	Vector<Variant> v;
	v.push_back(p_arg1);
	v.push_back(p_arg2);
	v.push_back(p_arg3);
	return v;
}
Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3, const Variant &p_arg4) {
	Vector<Variant> v;
	v.push_back(p_arg1);
	v.push_back(p_arg2);
	v.push_back(p_arg3);
	v.push_back(p_arg4);
	return v;
}

Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3, const Variant &p_arg4, const Variant &p_arg5) {
	Vector<Variant> v;
	v.push_back(p_arg1);
	v.push_back(p_arg2);
	v.push_back(p_arg3);
	v.push_back(p_arg4);
	v.push_back(p_arg5);
	return v;
}

bool Variant::is_shared() const {
	switch (type) {
		case OBJECT:
			return true;
		case ARRAY:
			return true;
		case DICTIONARY:
			return true;
		default: {
		}
	}

	return false;
}

String vformat(const String &p_text, const Variant &p1, const Variant &p2, const Variant &p3, const Variant &p4, const Variant &p5) {
	Array args;
	if (p1.get_type() != Variant::NIL) {
		args.push_back(p1);

		if (p2.get_type() != Variant::NIL) {
			args.push_back(p2);

			if (p3.get_type() != Variant::NIL) {
				args.push_back(p3);

				if (p4.get_type() != Variant::NIL) {
					args.push_back(p4);

					if (p5.get_type() != Variant::NIL) {
						args.push_back(p5);
					}
				}
			}
		}
	}

	bool error = false;
	String fmt = args.sprintf(p_text, &error);

	ERR_FAIL_COND_V_MSG(error, String(), fmt);

	return fmt;
}
