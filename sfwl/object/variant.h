//--STRIP
#ifndef VARIANT_H
#define VARIANT_H
//--STRIP

/*************************************************************************/
/*  variant.h                                                            */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/color.h"
#include "core/pool_vector.h"
#include "core/ustring.h"
#include "core/vector2i.h"
#include "core/rect2i.h"
#include "object/array.h"
#include "object/dictionary.h"
#include "object/ref_ptr.h"
#include "object/object_id.h"
//--STRIP

class Object;
class ObjectRC;

typedef PoolVector<uint8_t> PoolByteArray;
typedef PoolVector<int> PoolIntArray;
typedef PoolVector<real_t> PoolRealArray;
typedef PoolVector<String> PoolStringArray;
typedef PoolVector<Vector2i> PoolVector2iArray;
typedef PoolVector<Color> PoolColorArray;

// Temporary workaround until c++11 alignas()
#ifdef __GNUC__
#define GCC_ALIGNED_8 __attribute__((aligned(8)))
#else
#define GCC_ALIGNED_8
#endif

#define _REF_OBJ_PTR(m_variant) (reinterpret_cast<Ref<Reference> *>((m_variant)._get_obj().ref.get_data())->ptr())
#define _OBJ_PTR(m_variant) ((m_variant)._get_obj().rc ? (m_variant)._get_obj().rc->get_ptr() : _REF_OBJ_PTR(m_variant))
// _UNSAFE_OBJ_PROXY_PTR is needed for comparing an object Variant against NIL or compare two object Variants.
// It's guaranteed to be unique per object, in contrast to the pointer stored in the RC structure,
// which is set to null when the object is destroyed.
#define _UNSAFE_OBJ_PROXY_PTR(m_variant) ((m_variant)._get_obj().rc ? reinterpret_cast<uint8_t *>((m_variant)._get_obj().rc) : reinterpret_cast<uint8_t *>(_REF_OBJ_PTR(m_variant)))

class Variant {
public:
	// If this changes the table in variant_op must be updated
	enum Type {

		NIL,

		// atomic types
		BOOL,
		INT,
		REAL,
		STRING,

		// math types
		RECT2I,
		VECTOR2I,

		// misc types
		COLOR,
		OBJECT,
		STRING_NAME,
		DICTIONARY,
		ARRAY,

		// arrays
		POOL_BYTE_ARRAY,
		POOL_INT_ARRAY,
		POOL_REAL_ARRAY,
		POOL_STRING_ARRAY,
		POOL_VECTOR2I_ARRAY,
		POOL_COLOR_ARRAY,

		VARIANT_MAX

	};

	enum {
		// Maximum recursion depth allowed when serializing variants.
		MAX_RECURSION_DEPTH = 1024,
	};

private:
	// Variant takes 20 bytes when real_t is float, and 36 if double
	// it only allocates extra memory for aabb/matrix.

	Type type;

	struct ObjData {
		// Will be null for every type deriving from Reference as they have their
		// own reference count mechanism
		ObjectRC *rc;
		// Always initialized, but will be null if the Ref<> assigned was null
		// or this Variant is not even holding a Reference-derived object
		RefPtr ref;
	};

	_FORCE_INLINE_ ObjData &_get_obj();
	_FORCE_INLINE_ const ObjData &_get_obj() const;

	union {
		bool _bool;
		int64_t _int;
		double _real;
		void *_ptr; //generic pointer
		uint8_t _mem[sizeof(ObjData) > (sizeof(real_t) * 4) ? sizeof(ObjData) : (sizeof(real_t) * 4)];
	} _data GCC_ALIGNED_8;

	void reference(const Variant &p_variant);
	void clear();

public:
	_FORCE_INLINE_ Type get_type() const { return type; }
	static String get_type_name(Variant::Type p_type);
	static bool can_convert(Type p_type_from, Type p_type_to);
	static bool can_convert_strict(Type p_type_from, Type p_type_to);

	bool is_ref() const;
	_FORCE_INLINE_ bool is_num() const { return type == INT || type == REAL; };
	_FORCE_INLINE_ bool is_array() const { return type >= ARRAY; };
	_FORCE_INLINE_ bool is_null() const { return type == NIL; };
	bool is_shared() const;
	bool is_zero() const;
	bool is_one() const;

	ObjectID get_object_instance_id() const;
	bool is_invalid_object() const;

	operator bool() const;
	operator signed int() const;
	operator unsigned int() const; // this is the real one
	operator signed short() const;
	operator unsigned short() const;
	operator signed char() const;
	operator unsigned char() const;
	//operator long unsigned int() const;
	operator int64_t() const;
	operator uint64_t() const;
#ifdef NEED_LONG_INT
	operator signed long() const;
	operator unsigned long() const;
#endif

	operator CharType() const;
	operator float() const;
	operator double() const;
	operator String() const;
	operator StringName() const;
	operator Rect2i() const;
	operator Vector2i() const;

	operator Color() const;
	operator RefPtr() const;

	operator Object *() const;

	operator Dictionary() const;
	operator Array() const;

	operator PoolVector<uint8_t>() const;
	operator PoolVector<int>() const;
	operator PoolVector<real_t>() const;
	operator PoolVector<String>() const;
	operator PoolVector<Vector2i>() const;
	operator PoolVector<Color>() const;

	operator Vector<Variant>() const;
	operator Vector<uint8_t>() const;
	operator Vector<int>() const;
	operator Vector<real_t>() const;
	operator Vector<String>() const;
	operator Vector<StringName>() const;
	operator Vector<Color>() const;
	operator Vector<Vector2i>() const;

	// some core type enums to convert to
	operator Margin() const;
	operator Side() const;
	operator Orientation() const;

	Variant(bool p_bool);
	Variant(signed int p_int); // real one
	Variant(unsigned int p_int);
#ifdef NEED_LONG_INT
	Variant(signed long p_long); // real one
	Variant(unsigned long p_long);
//Variant(long unsigned int p_long);
#endif
	Variant(signed short p_short); // real one
	Variant(unsigned short p_short);
	Variant(signed char p_char); // real one
	Variant(unsigned char p_char);
	Variant(int64_t p_int); // real one
	Variant(uint64_t p_int);
	Variant(float p_float);
	Variant(double p_double);
	Variant(const String &p_string);
	Variant(const StringName &p_string);
	Variant(const char *const p_cstring);
	Variant(const CharType *p_wstring);
	Variant(const Vector2i &p_vector2);
	Variant(const Rect2i &p_rect2);
	Variant(const Color &p_color);
	Variant(const RefPtr &p_resource);
	Variant(const Object *p_object);
	Variant(const Dictionary &p_dictionary);

	Variant(const Array &p_array);
	Variant(const PoolVector<uint8_t> &p_raw_array);
	Variant(const PoolVector<int> &p_int_array);
	Variant(const PoolVector<real_t> &p_real_array);
	Variant(const PoolVector<String> &p_string_array);
	Variant(const PoolVector<Color> &p_color_array);
	Variant(const PoolVector<Vector2i> &p_vector2_array);

	Variant(const Vector<Variant> &p_array);
	Variant(const Vector<uint8_t> &p_array);
	Variant(const Vector<int> &p_array);
	Variant(const Vector<real_t> &p_array);
	Variant(const Vector<String> &p_array);
	Variant(const Vector<StringName> &p_array);
	Variant(const Vector<Color> &p_array);
	Variant(const Vector<Vector2i> &p_array);

	// If this changes the table in variant_op must be updated
	enum Operator {
		//comparison
		OP_EQUAL,
		OP_NOT_EQUAL,
		OP_LESS,
		OP_LESS_EQUAL,
		OP_GREATER,
		OP_GREATER_EQUAL,
		//mathematic
		OP_ADD,
		OP_SUBTRACT,
		OP_MULTIPLY,
		OP_DIVIDE,
		OP_NEGATE,
		OP_POSITIVE,
		OP_MODULE,
		OP_STRING_CONCAT,
		//bitwise
		OP_SHIFT_LEFT,
		OP_SHIFT_RIGHT,
		OP_BIT_AND,
		OP_BIT_OR,
		OP_BIT_XOR,
		OP_BIT_NEGATE,
		//logic
		OP_AND,
		OP_OR,
		OP_XOR,
		OP_NOT,
		//containment
		OP_IN,
		OP_MAX
	};

	//Maybe add helper methods that use these
	//Like max()
	//add()
	//maybe operators like with add
	//?

	static String get_operator_name(Operator p_op);
	static void evaluate(const Operator &p_op, const Variant &p_a, const Variant &p_b, Variant &r_ret, bool &r_valid);
	static _FORCE_INLINE_ Variant evaluate(const Operator &p_op, const Variant &p_a, const Variant &p_b) {
		bool valid = true;
		Variant res;
		evaluate(p_op, p_a, p_b, res, valid);
		return res;
	}

	void zero();
	Variant duplicate(bool deep = false) const;
	static void blend(const Variant &a, const Variant &b, float c, Variant &r_dst);
	static void interpolate(const Variant &a, const Variant &b, float c, Variant &r_dst);
	static void sub(const Variant &a, const Variant &b, Variant &r_dst);

	//Maybe add helper methods that call this? like get_x(), set_x() etc Or just x(), x(value)?
	//Check if operator[] can take strings and ints that might work too
	void set_named(const StringName &p_index, const Variant &p_value, bool *r_valid = nullptr);
	Variant get_named(const StringName &p_index, bool *r_valid = nullptr) const;

	//Implement operator[]s that use these?
	void set(const Variant &p_index, const Variant &p_value, bool *r_valid = nullptr);
	Variant get(const Variant &p_index, bool *r_valid = nullptr) const;
	bool in(const Variant &p_index, bool *r_valid = nullptr) const;

	bool iter_init(Variant &r_iter, bool &r_valid) const;
	bool iter_next(Variant &r_iter, bool &r_valid) const;
	Variant iter_get(const Variant &r_iter, bool &r_valid) const;

	bool deep_equal(const Variant &p_variant, int p_recursion_count = 0) const;
	bool operator==(const Variant &p_variant) const;
	bool operator!=(const Variant &p_variant) const;
	bool operator<(const Variant &p_variant) const;
	uint32_t hash() const;
	uint32_t recursive_hash(int p_recursion_count) const;

	bool hash_compare(const Variant &p_variant) const;
	bool booleanize() const;
	String stringify(List<const void *> &stack) const;

	void operator=(const Variant &p_variant); // only this is enough for all the other types
	Variant(const Variant &p_variant);
	_FORCE_INLINE_ Variant() {
		type = NIL;
	}
	_FORCE_INLINE_ ~Variant() {
		if (type != Variant::NIL) {
			clear();
		}
	}
};

//typedef Dictionary Dictionary; no
//typedef Array Array;

Vector<Variant> varray();
Vector<Variant> varray(const Variant &p_arg1);
Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2);
Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3);
Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3, const Variant &p_arg4);
Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3, const Variant &p_arg4, const Variant &p_arg5);

struct VariantHasher {
	static _FORCE_INLINE_ uint32_t hash(const Variant &p_variant) { return p_variant.hash(); }
};

struct VariantComparator {
	static _FORCE_INLINE_ bool compare(const Variant &p_lhs, const Variant &p_rhs) { return p_lhs.hash_compare(p_rhs); }
};

Variant::ObjData &Variant::_get_obj() {
	return *reinterpret_cast<ObjData *>(&_data._mem[0]);
}

const Variant::ObjData &Variant::_get_obj() const {
	return *reinterpret_cast<const ObjData *>(&_data._mem[0]);
}

String vformat(const String &p_text, const Variant &p1 = Variant(), const Variant &p2 = Variant(), const Variant &p3 = Variant(), const Variant &p4 = Variant(), const Variant &p5 = Variant());

//--STRIP
#endif
//--STRIP
