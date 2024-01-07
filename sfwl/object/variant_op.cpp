/*************************************************************************/
/*  variant_op.cpp                                                       */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "variant.h"

#include "object/core_string_names.h"
#include "object/object.h"
#include "object/object_rc.h"
#include "object/resource.h"
//--STRIP

#define CASE_TYPE_ALL(PREFIX, OP) \
	CASE_TYPE(PREFIX, OP, INT)    \
	CASE_TYPE_ALL_BUT_INT(PREFIX, OP)

#define CASE_TYPE_ALL_BUT_INT(PREFIX, OP)      \
	CASE_TYPE(PREFIX, OP, NIL)                 \
	CASE_TYPE(PREFIX, OP, BOOL)                \
	CASE_TYPE(PREFIX, OP, REAL)                \
	CASE_TYPE(PREFIX, OP, STRING)              \
	CASE_TYPE(PREFIX, OP, OBJECT)              \
	CASE_TYPE(PREFIX, OP, STRING_NAME)         \
	CASE_TYPE(PREFIX, OP, DICTIONARY)          \
	CASE_TYPE(PREFIX, OP, ARRAY)               \
	CASE_TYPE(PREFIX, OP, POOL_BYTE_ARRAY)     \
	CASE_TYPE(PREFIX, OP, POOL_INT_ARRAY)      \
	CASE_TYPE(PREFIX, OP, POOL_REAL_ARRAY)     \
	CASE_TYPE(PREFIX, OP, POOL_STRING_ARRAY)   

#ifdef __GNUC__
#define TYPE(PREFIX, OP, TYPE) &&PREFIX##_##OP##_##TYPE

/* clang-format off */

#define TYPES(PREFIX, OP) {                    \
		TYPE(PREFIX, OP, NIL),                 \
		TYPE(PREFIX, OP, BOOL),                \
		TYPE(PREFIX, OP, INT),                 \
		TYPE(PREFIX, OP, REAL),                \
		TYPE(PREFIX, OP, STRING),              \
		TYPE(PREFIX, OP, OBJECT),              \
		TYPE(PREFIX, OP, STRING_NAME),         \
		TYPE(PREFIX, OP, DICTIONARY),          \
		TYPE(PREFIX, OP, ARRAY),               \
		TYPE(PREFIX, OP, POOL_BYTE_ARRAY),     \
		TYPE(PREFIX, OP, POOL_INT_ARRAY),      \
		TYPE(PREFIX, OP, POOL_REAL_ARRAY),     \
		TYPE(PREFIX, OP, POOL_STRING_ARRAY),   \
}

/* clang-format on */

#define CASES(PREFIX) static const void *switch_table_##PREFIX[25][38] = { \
	TYPES(PREFIX, OP_EQUAL),                                               \
	TYPES(PREFIX, OP_NOT_EQUAL),                                           \
	TYPES(PREFIX, OP_LESS),                                                \
	TYPES(PREFIX, OP_LESS_EQUAL),                                          \
	TYPES(PREFIX, OP_GREATER),                                             \
	TYPES(PREFIX, OP_GREATER_EQUAL),                                       \
	TYPES(PREFIX, OP_ADD),                                                 \
	TYPES(PREFIX, OP_SUBTRACT),                                            \
	TYPES(PREFIX, OP_MULTIPLY),                                            \
	TYPES(PREFIX, OP_DIVIDE),                                              \
	TYPES(PREFIX, OP_NEGATE),                                              \
	TYPES(PREFIX, OP_POSITIVE),                                            \
	TYPES(PREFIX, OP_MODULE),                                              \
	TYPES(PREFIX, OP_STRING_CONCAT),                                       \
	TYPES(PREFIX, OP_SHIFT_LEFT),                                          \
	TYPES(PREFIX, OP_SHIFT_RIGHT),                                         \
	TYPES(PREFIX, OP_BIT_AND),                                             \
	TYPES(PREFIX, OP_BIT_OR),                                              \
	TYPES(PREFIX, OP_BIT_XOR),                                             \
	TYPES(PREFIX, OP_BIT_NEGATE),                                          \
	TYPES(PREFIX, OP_AND),                                                 \
	TYPES(PREFIX, OP_OR),                                                  \
	TYPES(PREFIX, OP_XOR),                                                 \
	TYPES(PREFIX, OP_NOT),                                                 \
	TYPES(PREFIX, OP_IN),                                                  \
}

#define SWITCH(PREFIX, op, val) goto *switch_table_##PREFIX[op][val];
#define SWITCH_OP(PREFIX, OP, val)
#define CASE_TYPE(PREFIX, OP, TYPE) PREFIX##_##OP##_##TYPE:

#else
#define CASES(PREFIX)
#define SWITCH(PREFIX, op, val) switch (op)
#define SWITCH_OP(PREFIX, OP, val) \
	case OP:                       \
		switch (val)
#define CASE_TYPE(PREFIX, OP, TYPE) case TYPE:
#endif

Variant::operator bool() const {
	return booleanize();
}

// We consider all uninitialized or empty types to be false based on the type's
// zeroiness.
bool Variant::booleanize() const {
	return !is_zero();
}

#define _RETURN(m_what) \
	{                   \
		r_ret = m_what; \
		return;         \
	}

#define _RETURN_FAIL     \
	{                    \
		r_valid = false; \
		return;          \
	}

#define DEFAULT_OP_NUM(m_prefix, m_op_name, m_name, m_op, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                      \
		if (p_b.type == INT)                                      \
			_RETURN(p_a._data.m_type m_op p_b._data._int);        \
		if (p_b.type == REAL)                                     \
			_RETURN(p_a._data.m_type m_op p_b._data._real);       \
                                                                  \
		_RETURN_FAIL                                              \
	};

#define DEFAULT_OP_NUM_NULL(m_prefix, m_op_name, m_name, m_op, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                           \
		if (p_b.type == INT)                                           \
			_RETURN(p_a._data.m_type m_op p_b._data._int);             \
		if (p_b.type == REAL)                                          \
			_RETURN(p_a._data.m_type m_op p_b._data._real);            \
		if (p_b.type == NIL)                                           \
			_RETURN(!(p_b.type m_op NIL));                             \
                                                                       \
		_RETURN_FAIL                                                   \
	};

#ifdef DEBUG_ENABLED
#define DEFAULT_OP_NUM_DIV(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                    \
		if (p_b.type == INT) {                                  \
			if (p_b._data._int == 0) {                          \
				r_valid = false;                                \
				_RETURN("Division By Zero");                    \
			}                                                   \
			_RETURN(p_a._data.m_type / p_b._data._int);         \
		}                                                       \
		if (p_b.type == REAL) {                                 \
			if (p_b._data._real == 0) {                         \
				r_valid = false;                                \
				_RETURN("Division By Zero");                    \
			}                                                   \
			_RETURN(p_a._data.m_type / p_b._data._real);        \
		}                                                       \
                                                                \
		_RETURN_FAIL                                            \
	};
#else
#define DEFAULT_OP_NUM_DIV(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                    \
		if (p_b.type == INT)                                    \
			_RETURN(p_a._data.m_type / p_b._data._int);         \
		if (p_b.type == REAL)                                   \
			_RETURN(p_a._data.m_type / p_b._data._real);        \
                                                                \
		_RETURN_FAIL                                            \
	};
#endif

#define DEFAULT_OP_NUM_NEG(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                    \
		_RETURN(-p_a._data.m_type);                             \
	};

#define DEFAULT_OP_NUM_POS(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                    \
		_RETURN(p_a._data.m_type);                              \
	};

#define DEFAULT_OP_NUM_VEC(m_prefix, m_op_name, m_name, m_op, m_type)                           \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                    \
		if (p_b.type == INT)                                                                    \
			_RETURN(p_a._data.m_type m_op p_b._data._int);                                      \
		if (p_b.type == REAL)                                                                   \
			_RETURN(p_a._data.m_type m_op p_b._data._real);                                     \
                                                                                                \
		_RETURN_FAIL                                                                            \
	};

#define DEFAULT_OP_STR_REV(m_prefix, m_op_name, m_name, m_op, m_type)                                                              \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                       \
		if (p_b.type == STRING)                                                                                                    \
			_RETURN(*reinterpret_cast<const m_type *>(p_b._data._mem) m_op *reinterpret_cast<const String *>(p_a._data._mem));     \
		if (p_b.type == STRING_NAME)                                                                                               \
			_RETURN(*reinterpret_cast<const m_type *>(p_b._data._mem) m_op *reinterpret_cast<const StringName *>(p_a._data._mem)); \
                                                                                                                                   \
		_RETURN_FAIL                                                                                                               \
	};

#define DEFAULT_OP_STR(m_prefix, m_op_name, m_name, m_op, m_type)                                                                  \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                       \
		if (p_b.type == STRING)                                                                                                    \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const String *>(p_b._data._mem));     \
		if (p_b.type == STRING_NAME)                                                                                               \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const StringName *>(p_b._data._mem)); \
                                                                                                                                   \
		_RETURN_FAIL                                                                                                               \
	};

#define DEFAULT_OP_STR_NULL(m_prefix, m_op_name, m_name, m_op, m_type)                                                             \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                       \
		if (p_b.type == STRING)                                                                                                    \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const String *>(p_b._data._mem));     \
		if (p_b.type == STRING_NAME)                                                                                               \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const StringName *>(p_b._data._mem)); \
		if (p_b.type == NIL)                                                                                                       \
			_RETURN(!(p_b.type m_op NIL));                                                                                         \
                                                                                                                                   \
		_RETURN_FAIL                                                                                                               \
	};

#define DEFAULT_OP_STR_NULL_NP(m_prefix, m_op_name, m_name, m_op, m_type)                                                      \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                   \
		if (p_b.type == STRING)                                                                                                \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const String *>(p_b._data._mem)); \
		if (p_b.type == NIL)                                                                                                   \
			_RETURN(!(p_b.type m_op NIL));                                                                                     \
                                                                                                                               \
		_RETURN_FAIL                                                                                                           \
	};

#define DEFAULT_OP_STR_NULL_SN(m_prefix, m_op_name, m_name, m_op, m_type)                                                          \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                       \
		if (p_b.type == STRING)                                                                                                    \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const String *>(p_b._data._mem));     \
		if (p_b.type == STRING_NAME)                                                                                               \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const StringName *>(p_b._data._mem)); \
		if (p_b.type == NIL)                                                                                                       \
			_RETURN(!(p_b.type m_op NIL));                                                                                         \
                                                                                                                                   \
		_RETURN_FAIL                                                                                                               \
	};

#define DEFAULT_OP_LOCALMEM_REV(m_prefix, m_op_name, m_name, m_op, m_type)                                                     \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                   \
		if (p_b.type == m_name)                                                                                                \
			_RETURN(*reinterpret_cast<const m_type *>(p_b._data._mem) m_op *reinterpret_cast<const m_type *>(p_a._data._mem)); \
                                                                                                                               \
		_RETURN_FAIL                                                                                                           \
	};

#define DEFAULT_OP_LOCALMEM(m_prefix, m_op_name, m_name, m_op, m_type)                                                         \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                   \
		if (p_b.type == m_name)                                                                                                \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const m_type *>(p_b._data._mem)); \
                                                                                                                               \
		_RETURN_FAIL                                                                                                           \
	};

#define DEFAULT_OP_LOCALMEM_NULL(m_prefix, m_op_name, m_name, m_op, m_type)                                                    \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                   \
		if (p_b.type == m_name)                                                                                                \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const m_type *>(p_b._data._mem)); \
		if (p_b.type == NIL)                                                                                                   \
			_RETURN(!(p_b.type m_op NIL));                                                                                     \
                                                                                                                               \
		_RETURN_FAIL                                                                                                           \
	};

#define DEFAULT_OP_LOCALMEM_NEG(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                         \
		_RETURN(-*reinterpret_cast<const m_type *>(p_a._data._mem)); \
	}

#define DEFAULT_OP_LOCALMEM_POS(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                         \
		_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem));  \
	}

#define DEFAULT_OP_LOCALMEM_NUM(m_prefix, m_op_name, m_name, m_op, m_type)                                                     \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                   \
		if (p_b.type == m_name)                                                                                                \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const m_type *>(p_b._data._mem)); \
		if (p_b.type == INT)                                                                                                   \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op p_b._data._int);                                    \
		if (p_b.type == REAL)                                                                                                  \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op p_b._data._real);                                   \
                                                                                                                               \
		_RETURN_FAIL                                                                                                           \
	}

#define DEFAULT_OP_PTR(m_op, m_name, m_sub)                \
	CASE_TYPE(m_prefix, m_op_name, m_name) {               \
		if (p_b.type == m_name)                            \
			_RETURN(p_a._data.m_sub m_op p_b._data.m_sub); \
                                                           \
		_RETURN_FAIL                                       \
	}

#define DEFAULT_OP_PTRREF(m_prefix, m_op_name, m_name, m_op, m_sub) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                        \
		if (p_b.type == m_name)                                     \
			_RETURN(*p_a._data.m_sub m_op *p_b._data.m_sub);        \
                                                                    \
		_RETURN_FAIL                                                \
	}

#define DEFAULT_OP_PTRREF_NULL(m_prefix, m_op_name, m_name, m_op, m_sub) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                             \
		if (p_b.type == m_name)                                          \
			_RETURN(*p_a._data.m_sub m_op *p_b._data.m_sub);             \
		if (p_b.type == NIL)                                             \
			_RETURN(!(p_b.type m_op NIL));                               \
                                                                         \
		_RETURN_FAIL                                                     \
	}

#define DEFAULT_OP_ARRAY_EQ(m_prefix, m_op_name, m_name, m_type)                                  \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                      \
		if (p_b.type == NIL)                                                                      \
			_RETURN(false)                                                                        \
		DEFAULT_OP_ARRAY_OP_BODY(m_prefix, m_op_name, m_name, m_type, !=, !=, true, false, false) \
	}

#define DEFAULT_OP_ARRAY_NEQ(m_prefix, m_op_name, m_name, m_type)                                \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                     \
		if (p_b.type == NIL)                                                                     \
			_RETURN(true)                                                                        \
		DEFAULT_OP_ARRAY_OP_BODY(m_prefix, m_op_name, m_name, m_type, !=, !=, false, true, true) \
	}

#define DEFAULT_OP_ARRAY_LT(m_prefix, m_op_name, m_name, m_type) \
	DEFAULT_OP_ARRAY_OP(m_prefix, m_op_name, m_name, m_type, <, !=, false, a_len < array_b.size(), true)

#define DEFAULT_OP_ARRAY_GT(m_prefix, m_op_name, m_name, m_type) \
	DEFAULT_OP_ARRAY_OP(m_prefix, m_op_name, m_name, m_type, >, !=, false, a_len < array_b.size(), true)

#define DEFAULT_OP_ARRAY_OP(m_prefix, m_op_name, m_name, m_type, m_opa, m_opb, m_ret_def, m_ret_s, m_ret_f)      \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                     \
		DEFAULT_OP_ARRAY_OP_BODY(m_prefix, m_op_name, m_name, m_type, m_opa, m_opb, m_ret_def, m_ret_s, m_ret_f) \
	}

#define DEFAULT_OP_ARRAY_OP_BODY(m_prefix, m_op_name, m_name, m_type, m_opa, m_opb, m_ret_def, m_ret_s, m_ret_f) \
	if (p_a.type != p_b.type)                                                                                    \
		_RETURN_FAIL                                                                                             \
                                                                                                                 \
	const PoolVector<m_type> &array_a = *reinterpret_cast<const PoolVector<m_type> *>(p_a._data._mem);           \
	const PoolVector<m_type> &array_b = *reinterpret_cast<const PoolVector<m_type> *>(p_b._data._mem);           \
                                                                                                                 \
	int a_len = array_a.size();                                                                                  \
	if (a_len m_opa array_b.size()) {                                                                            \
		_RETURN(m_ret_s);                                                                                        \
	} else {                                                                                                     \
		PoolVector<m_type>::Read ra = array_a.read();                                                            \
		PoolVector<m_type>::Read rb = array_b.read();                                                            \
                                                                                                                 \
		for (int i = 0; i < a_len; i++) {                                                                        \
			if (ra[i] m_opb rb[i])                                                                               \
				_RETURN(m_ret_f);                                                                                \
		}                                                                                                        \
                                                                                                                 \
		_RETURN(m_ret_def);                                                                                      \
	}

#define DEFAULT_OP_ARRAY_ADD(m_prefix, m_op_name, m_name, m_type)                                          \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                               \
		if (p_a.type != p_b.type)                                                                          \
			_RETURN_FAIL;                                                                                  \
                                                                                                           \
		const PoolVector<m_type> &array_a = *reinterpret_cast<const PoolVector<m_type> *>(p_a._data._mem); \
		const PoolVector<m_type> &array_b = *reinterpret_cast<const PoolVector<m_type> *>(p_b._data._mem); \
		PoolVector<m_type> sum = array_a;                                                                  \
		sum.append_array(array_b);                                                                         \
		_RETURN(sum);                                                                                      \
	}

void Variant::evaluate(const Operator &p_op, const Variant &p_a,
		const Variant &p_b, Variant &r_ret, bool &r_valid) {
	CASES(math);
	r_valid = true;

	SWITCH(math, p_op, p_a.type) {
		SWITCH_OP(math, OP_EQUAL, p_a.type) {
			CASE_TYPE(math, OP_EQUAL, NIL) {
				if (p_b.type == NIL)
					_RETURN(true);
				if (p_b.type == OBJECT)
					_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_b) == nullptr);

				_RETURN(false);
			}

			CASE_TYPE(math, OP_EQUAL, BOOL) {
				if (p_b.type != BOOL) {
					if (p_b.type == NIL)
						_RETURN(false);
					_RETURN_FAIL;
				}

				_RETURN(p_a._data._bool == p_b._data._bool);
			}

			CASE_TYPE(math, OP_EQUAL, OBJECT) {
				if (p_b.type == OBJECT)
					_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) == _UNSAFE_OBJ_PROXY_PTR(p_b));
				if (p_b.type == NIL)
					_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) == nullptr);

				_RETURN_FAIL;
			}

			CASE_TYPE(math, OP_EQUAL, DICTIONARY) {
				if (p_b.type != DICTIONARY) {
					if (p_b.type == NIL)
						_RETURN(false);
					_RETURN_FAIL;
				}

				const Dictionary *arr_a = reinterpret_cast<const Dictionary *>(p_a._data._mem);
				const Dictionary *arr_b = reinterpret_cast<const Dictionary *>(p_b._data._mem);

				_RETURN(*arr_a == *arr_b);
			}

			CASE_TYPE(math, OP_EQUAL, ARRAY) {
				if (p_b.type != ARRAY) {
					if (p_b.type == NIL)
						_RETURN(false);
					_RETURN_FAIL;
				}
				const Array *arr_a = reinterpret_cast<const Array *>(p_a._data._mem);
				const Array *arr_b = reinterpret_cast<const Array *>(p_b._data._mem);

				int l = arr_a->size();
				if (arr_b->size() != l)
					_RETURN(false);
				for (int i = 0; i < l; i++) {
					if (!((*arr_a)[i] == (*arr_b)[i])) {
						_RETURN(false);
					}
				}

				_RETURN(true);
			}

			DEFAULT_OP_NUM_NULL(math, OP_EQUAL, INT, ==, _int);
			DEFAULT_OP_NUM_NULL(math, OP_EQUAL, REAL, ==, _real);
			DEFAULT_OP_STR_NULL(math, OP_EQUAL, STRING, ==, String);
			DEFAULT_OP_STR_NULL_SN(math, OP_EQUAL, STRING_NAME, ==, StringName);

			DEFAULT_OP_ARRAY_EQ(math, OP_EQUAL, POOL_BYTE_ARRAY, uint8_t);
			DEFAULT_OP_ARRAY_EQ(math, OP_EQUAL, POOL_INT_ARRAY, int);
			DEFAULT_OP_ARRAY_EQ(math, OP_EQUAL, POOL_REAL_ARRAY, real_t);
			DEFAULT_OP_ARRAY_EQ(math, OP_EQUAL, POOL_STRING_ARRAY, String);
		}

		SWITCH_OP(math, OP_NOT_EQUAL, p_a.type) {
			CASE_TYPE(math, OP_NOT_EQUAL, NIL) {
				if (p_b.type == NIL)
					_RETURN(false);
				if (p_b.type == OBJECT)
					_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_b) != nullptr);

				_RETURN(true);
			}

			CASE_TYPE(math, OP_NOT_EQUAL, BOOL) {
				if (p_b.type != BOOL) {
					if (p_b.type == NIL)
						_RETURN(true);

					_RETURN_FAIL;
				}

				_RETURN(p_a._data._bool != p_b._data._bool);
			}

			CASE_TYPE(math, OP_NOT_EQUAL, OBJECT) {
				if (p_b.type == OBJECT)
					_RETURN((_UNSAFE_OBJ_PROXY_PTR(p_a) != _UNSAFE_OBJ_PROXY_PTR(p_b)));
				if (p_b.type == NIL)
					_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) != nullptr);

				_RETURN_FAIL;
			}

			CASE_TYPE(math, OP_NOT_EQUAL, DICTIONARY) {
				if (p_b.type != DICTIONARY) {
					if (p_b.type == NIL)
						_RETURN(true);
					_RETURN_FAIL;
				}

				const Dictionary *arr_a = reinterpret_cast<const Dictionary *>(p_a._data._mem);
				const Dictionary *arr_b = reinterpret_cast<const Dictionary *>(p_b._data._mem);

				_RETURN(*arr_a != *arr_b);
			}

			CASE_TYPE(math, OP_NOT_EQUAL, ARRAY) {
				if (p_b.type != ARRAY) {
					if (p_b.type == NIL)
						_RETURN(true);

					_RETURN_FAIL;
				}

				const Array *arr_a = reinterpret_cast<const Array *>(p_a._data._mem);
				const Array *arr_b = reinterpret_cast<const Array *>(p_b._data._mem);

				int l = arr_a->size();
				if (arr_b->size() != l)
					_RETURN(true);
				for (int i = 0; i < l; i++) {
					if (((*arr_a)[i] != (*arr_b)[i])) {
						_RETURN(true);
					}
				}

				_RETURN(false);
			}

			DEFAULT_OP_NUM_NULL(math, OP_NOT_EQUAL, INT, !=, _int);
			DEFAULT_OP_NUM_NULL(math, OP_NOT_EQUAL, REAL, !=, _real);
			DEFAULT_OP_STR_NULL(math, OP_NOT_EQUAL, STRING, !=, String);
			DEFAULT_OP_STR_NULL_SN(math, OP_NOT_EQUAL, STRING_NAME, !=, StringName);

			DEFAULT_OP_ARRAY_NEQ(math, OP_NOT_EQUAL, POOL_BYTE_ARRAY, uint8_t);
			DEFAULT_OP_ARRAY_NEQ(math, OP_NOT_EQUAL, POOL_INT_ARRAY, int);
			DEFAULT_OP_ARRAY_NEQ(math, OP_NOT_EQUAL, POOL_REAL_ARRAY, real_t);
			DEFAULT_OP_ARRAY_NEQ(math, OP_NOT_EQUAL, POOL_STRING_ARRAY, String);
		}

		SWITCH_OP(math, OP_LESS, p_a.type) {
			CASE_TYPE(math, OP_LESS, BOOL) {
				if (p_b.type != BOOL)
					_RETURN_FAIL;

				if (p_a._data._bool == p_b._data._bool)
					_RETURN(false);

				if (p_a._data._bool && !p_b._data._bool)
					_RETURN(false);

				_RETURN(true);
			}

			CASE_TYPE(math, OP_LESS, OBJECT) {
				if (p_b.type != OBJECT)
					_RETURN_FAIL;
				_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) < _UNSAFE_OBJ_PROXY_PTR(p_b));
			}

			CASE_TYPE(math, OP_LESS, ARRAY) {
				if (p_b.type != ARRAY)
					_RETURN_FAIL;

				const Array *arr_a = reinterpret_cast<const Array *>(p_a._data._mem);
				const Array *arr_b = reinterpret_cast<const Array *>(p_b._data._mem);

				int l = arr_a->size();
				if (arr_b->size() < l)
					_RETURN(false);
				for (int i = 0; i < l; i++) {
					if (!((*arr_a)[i] < (*arr_b)[i])) {
						_RETURN(true);
					}
				}

				_RETURN(false);
			}

			DEFAULT_OP_NUM(math, OP_LESS, INT, <, _int);
			DEFAULT_OP_NUM(math, OP_LESS, REAL, <, _real);
			DEFAULT_OP_STR(math, OP_LESS, STRING, <, String);

			DEFAULT_OP_ARRAY_LT(math, OP_LESS, POOL_BYTE_ARRAY, uint8_t);
			DEFAULT_OP_ARRAY_LT(math, OP_LESS, POOL_INT_ARRAY, int);
			DEFAULT_OP_ARRAY_LT(math, OP_LESS, POOL_REAL_ARRAY, real_t);
			DEFAULT_OP_ARRAY_LT(math, OP_LESS, POOL_STRING_ARRAY, String);

			CASE_TYPE(math, OP_LESS, NIL)
			CASE_TYPE(math, OP_LESS, STRING_NAME)
			CASE_TYPE(math, OP_LESS, DICTIONARY)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_LESS_EQUAL, p_a.type) {
			CASE_TYPE(math, OP_LESS_EQUAL, OBJECT) {
				if (p_b.type != OBJECT)
					_RETURN_FAIL;
				_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) <= _UNSAFE_OBJ_PROXY_PTR(p_b));
			}

			DEFAULT_OP_NUM(math, OP_LESS_EQUAL, INT, <=, _int);
			DEFAULT_OP_NUM(math, OP_LESS_EQUAL, REAL, <=, _real);
			DEFAULT_OP_STR(math, OP_LESS_EQUAL, STRING, <=, String);

			CASE_TYPE(math, OP_LESS_EQUAL, NIL)
			CASE_TYPE(math, OP_LESS_EQUAL, BOOL)
			CASE_TYPE(math, OP_LESS_EQUAL, STRING_NAME)
			CASE_TYPE(math, OP_LESS_EQUAL, DICTIONARY)
			CASE_TYPE(math, OP_LESS_EQUAL, ARRAY)
			CASE_TYPE(math, OP_LESS_EQUAL, POOL_BYTE_ARRAY);
			CASE_TYPE(math, OP_LESS_EQUAL, POOL_INT_ARRAY);
			CASE_TYPE(math, OP_LESS_EQUAL, POOL_REAL_ARRAY);
			CASE_TYPE(math, OP_LESS_EQUAL, POOL_STRING_ARRAY);
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_GREATER, p_a.type) {
			CASE_TYPE(math, OP_GREATER, BOOL) {
				if (p_b.type != BOOL)
					_RETURN_FAIL;

				if (p_a._data._bool == p_b._data._bool)
					_RETURN(false);

				if (!p_a._data._bool && p_b._data._bool)
					_RETURN(false);

				_RETURN(true);
			}

			CASE_TYPE(math, OP_GREATER, OBJECT) {
				if (p_b.type != OBJECT)
					_RETURN_FAIL;
				_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) > _UNSAFE_OBJ_PROXY_PTR(p_b));
			}

			CASE_TYPE(math, OP_GREATER, ARRAY) {
				if (p_b.type != ARRAY)
					_RETURN_FAIL;

				const Array *arr_a = reinterpret_cast<const Array *>(p_a._data._mem);
				const Array *arr_b = reinterpret_cast<const Array *>(p_b._data._mem);

				int l = arr_a->size();
				if (arr_b->size() > l)
					_RETURN(false);
				for (int i = 0; i < l; i++) {
					if (((*arr_a)[i] < (*arr_b)[i])) {
						_RETURN(false);
					}
				}

				_RETURN(true);
			}

			DEFAULT_OP_NUM(math, OP_GREATER, INT, >, _int);
			DEFAULT_OP_NUM(math, OP_GREATER, REAL, >, _real);
			DEFAULT_OP_STR_REV(math, OP_GREATER, STRING, <, String);
			DEFAULT_OP_ARRAY_GT(math, OP_GREATER, POOL_BYTE_ARRAY, uint8_t);
			DEFAULT_OP_ARRAY_GT(math, OP_GREATER, POOL_INT_ARRAY, int);
			DEFAULT_OP_ARRAY_GT(math, OP_GREATER, POOL_REAL_ARRAY, real_t);
			DEFAULT_OP_ARRAY_GT(math, OP_GREATER, POOL_STRING_ARRAY, String);

			CASE_TYPE(math, OP_GREATER, NIL)
			CASE_TYPE(math, OP_GREATER, STRING_NAME)
			CASE_TYPE(math, OP_GREATER, DICTIONARY)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_GREATER_EQUAL, p_a.type) {
			CASE_TYPE(math, OP_GREATER_EQUAL, OBJECT) {
				if (p_b.type != OBJECT)
					_RETURN_FAIL;
				_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) >= _UNSAFE_OBJ_PROXY_PTR(p_b));
			}

			DEFAULT_OP_NUM(math, OP_GREATER_EQUAL, INT, >=, _int);
			DEFAULT_OP_NUM(math, OP_GREATER_EQUAL, REAL, >=, _real);
			DEFAULT_OP_STR_REV(math, OP_GREATER_EQUAL, STRING, <=, String);

			CASE_TYPE(math, OP_GREATER_EQUAL, NIL)
			CASE_TYPE(math, OP_GREATER_EQUAL, BOOL)
			CASE_TYPE(math, OP_GREATER_EQUAL, DICTIONARY)
			CASE_TYPE(math, OP_GREATER_EQUAL, STRING_NAME)
			CASE_TYPE(math, OP_GREATER_EQUAL, ARRAY)
			CASE_TYPE(math, OP_GREATER_EQUAL, POOL_BYTE_ARRAY);
			CASE_TYPE(math, OP_GREATER_EQUAL, POOL_INT_ARRAY);
			CASE_TYPE(math, OP_GREATER_EQUAL, POOL_REAL_ARRAY);
			CASE_TYPE(math, OP_GREATER_EQUAL, POOL_STRING_ARRAY);
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_ADD, p_a.type) {
			CASE_TYPE(math, OP_ADD, ARRAY) {
				if (p_a.type != p_b.type)
					_RETURN_FAIL;

				const Array &array_a = *reinterpret_cast<const Array *>(p_a._data._mem);
				const Array &array_b = *reinterpret_cast<const Array *>(p_b._data._mem);
				Array sum;
				int asize = array_a.size();
				int bsize = array_b.size();
				sum.resize(asize + bsize);
				for (int i = 0; i < asize; i++) {
					sum[i] = array_a[i];
				}
				for (int i = 0; i < bsize; i++) {
					sum[i + asize] = array_b[i];
				}
				_RETURN(sum);
			}

			DEFAULT_OP_NUM(math, OP_ADD, INT, +, _int);
			DEFAULT_OP_NUM(math, OP_ADD, REAL, +, _real);
			DEFAULT_OP_STR(math, OP_ADD, STRING, +, String);

			DEFAULT_OP_ARRAY_ADD(math, OP_ADD, POOL_BYTE_ARRAY, uint8_t);
			DEFAULT_OP_ARRAY_ADD(math, OP_ADD, POOL_INT_ARRAY, int);
			DEFAULT_OP_ARRAY_ADD(math, OP_ADD, POOL_REAL_ARRAY, real_t);
			DEFAULT_OP_ARRAY_ADD(math, OP_ADD, POOL_STRING_ARRAY, String);

			CASE_TYPE(math, OP_ADD, NIL)
			CASE_TYPE(math, OP_ADD, BOOL)
			CASE_TYPE(math, OP_ADD, OBJECT)
			CASE_TYPE(math, OP_ADD, DICTIONARY)
			CASE_TYPE(math, OP_ADD, STRING_NAME)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_SUBTRACT, p_a.type) {
			DEFAULT_OP_NUM(math, OP_SUBTRACT, INT, -, _int);
			DEFAULT_OP_NUM(math, OP_SUBTRACT, REAL, -, _real);

			CASE_TYPE(math, OP_SUBTRACT, NIL)
			CASE_TYPE(math, OP_SUBTRACT, BOOL)
			CASE_TYPE(math, OP_SUBTRACT, STRING)
			CASE_TYPE(math, OP_SUBTRACT, OBJECT)
			CASE_TYPE(math, OP_SUBTRACT, STRING_NAME)
			CASE_TYPE(math, OP_SUBTRACT, DICTIONARY)
			CASE_TYPE(math, OP_SUBTRACT, ARRAY)
			CASE_TYPE(math, OP_SUBTRACT, POOL_BYTE_ARRAY);
			CASE_TYPE(math, OP_SUBTRACT, POOL_INT_ARRAY);
			CASE_TYPE(math, OP_SUBTRACT, POOL_REAL_ARRAY);
			CASE_TYPE(math, OP_SUBTRACT, POOL_STRING_ARRAY);
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_MULTIPLY, p_a.type) {
			DEFAULT_OP_NUM_VEC(math, OP_MULTIPLY, INT, *, _int);
			DEFAULT_OP_NUM_VEC(math, OP_MULTIPLY, REAL, *, _real);

			CASE_TYPE(math, OP_MULTIPLY, NIL)
			CASE_TYPE(math, OP_MULTIPLY, BOOL)
			CASE_TYPE(math, OP_MULTIPLY, STRING)
			CASE_TYPE(math, OP_MULTIPLY, OBJECT)
			CASE_TYPE(math, OP_MULTIPLY, STRING_NAME)
			CASE_TYPE(math, OP_MULTIPLY, DICTIONARY)
			CASE_TYPE(math, OP_MULTIPLY, ARRAY)
			CASE_TYPE(math, OP_MULTIPLY, POOL_BYTE_ARRAY);
			CASE_TYPE(math, OP_MULTIPLY, POOL_INT_ARRAY);
			CASE_TYPE(math, OP_MULTIPLY, POOL_REAL_ARRAY);
			CASE_TYPE(math, OP_MULTIPLY, POOL_STRING_ARRAY);
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_DIVIDE, p_a.type) {
			DEFAULT_OP_NUM_DIV(math, OP_DIVIDE, INT, _int);
			DEFAULT_OP_NUM_DIV(math, OP_DIVIDE, REAL, _real);

			CASE_TYPE(math, OP_DIVIDE, NIL)
			CASE_TYPE(math, OP_DIVIDE, BOOL)
			CASE_TYPE(math, OP_DIVIDE, STRING)
			CASE_TYPE(math, OP_DIVIDE, OBJECT)
			CASE_TYPE(math, OP_DIVIDE, STRING_NAME)
			CASE_TYPE(math, OP_DIVIDE, DICTIONARY)
			CASE_TYPE(math, OP_DIVIDE, ARRAY)
			CASE_TYPE(math, OP_DIVIDE, POOL_BYTE_ARRAY);
			CASE_TYPE(math, OP_DIVIDE, POOL_INT_ARRAY);
			CASE_TYPE(math, OP_DIVIDE, POOL_REAL_ARRAY);
			CASE_TYPE(math, OP_DIVIDE, POOL_STRING_ARRAY);
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_POSITIVE, p_a.type) {
			DEFAULT_OP_NUM_POS(math, OP_POSITIVE, INT, _int);
			DEFAULT_OP_NUM_POS(math, OP_POSITIVE, REAL, _real);

			CASE_TYPE(math, OP_POSITIVE, NIL)
			CASE_TYPE(math, OP_POSITIVE, BOOL)
			CASE_TYPE(math, OP_POSITIVE, STRING)
			CASE_TYPE(math, OP_POSITIVE, OBJECT)
			CASE_TYPE(math, OP_POSITIVE, STRING_NAME)
			CASE_TYPE(math, OP_POSITIVE, DICTIONARY)
			CASE_TYPE(math, OP_POSITIVE, ARRAY)
			CASE_TYPE(math, OP_POSITIVE, POOL_BYTE_ARRAY)
			CASE_TYPE(math, OP_POSITIVE, POOL_INT_ARRAY)
			CASE_TYPE(math, OP_POSITIVE, POOL_REAL_ARRAY)
			CASE_TYPE(math, OP_POSITIVE, POOL_STRING_ARRAY)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_NEGATE, p_a.type) {
			DEFAULT_OP_NUM_NEG(math, OP_NEGATE, INT, _int);
			DEFAULT_OP_NUM_NEG(math, OP_NEGATE, REAL, _real);

			CASE_TYPE(math, OP_NEGATE, NIL)
			CASE_TYPE(math, OP_NEGATE, BOOL)
			CASE_TYPE(math, OP_NEGATE, STRING)
			CASE_TYPE(math, OP_NEGATE, OBJECT)
			CASE_TYPE(math, OP_NEGATE, STRING_NAME)
			CASE_TYPE(math, OP_NEGATE, DICTIONARY)
			CASE_TYPE(math, OP_NEGATE, ARRAY)
			CASE_TYPE(math, OP_NEGATE, POOL_BYTE_ARRAY)
			CASE_TYPE(math, OP_NEGATE, POOL_INT_ARRAY)
			CASE_TYPE(math, OP_NEGATE, POOL_REAL_ARRAY)
			CASE_TYPE(math, OP_NEGATE, POOL_STRING_ARRAY)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_MODULE, p_a.type) {
			CASE_TYPE(math, OP_MODULE, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
#ifdef DEBUG_ENABLED
				if (p_b._data._int == 0) {
					r_valid = false;
					_RETURN("Division By Zero");
				}
#endif
				_RETURN(p_a._data._int % p_b._data._int);
			}

			CASE_TYPE(math, OP_MODULE, STRING) {
				const String *format = reinterpret_cast<const String *>(p_a._data._mem);

				String result;
				bool error;
				if (p_b.type == ARRAY) {
					// e.g. "frog %s %d" % ["fish", 12]
					const Array *args = reinterpret_cast<const Array *>(p_b._data._mem);
					result = args->sprintf(*format, &error);
				} else {
					// e.g. "frog %d" % 12
					Array args;
					args.push_back(p_b);
					result = args.sprintf(*format, &error);
				}
				r_valid = !error;
				_RETURN(result);
			}

			CASE_TYPE(math, OP_MODULE, NIL)
			CASE_TYPE(math, OP_MODULE, BOOL)
			CASE_TYPE(math, OP_MODULE, REAL)
			CASE_TYPE(math, OP_MODULE, OBJECT)
			CASE_TYPE(math, OP_MODULE, STRING_NAME)
			CASE_TYPE(math, OP_MODULE, DICTIONARY)
			CASE_TYPE(math, OP_MODULE, ARRAY)
			CASE_TYPE(math, OP_MODULE, POOL_BYTE_ARRAY)
			CASE_TYPE(math, OP_MODULE, POOL_INT_ARRAY)
			CASE_TYPE(math, OP_MODULE, POOL_REAL_ARRAY)
			CASE_TYPE(math, OP_MODULE, POOL_STRING_ARRAY)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_STRING_CONCAT, p_a.type) {
			CASE_TYPE_ALL(math, OP_STRING_CONCAT)

			_RETURN(p_a.operator String() + p_b.operator String());
		}

		SWITCH_OP(math, OP_SHIFT_LEFT, p_a.type) {
			CASE_TYPE(math, OP_SHIFT_LEFT, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
				if (p_b._data._int < 0 || p_b._data._int >= 64)
					_RETURN_FAIL;
				_RETURN(p_a._data._int << p_b._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_SHIFT_LEFT)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_SHIFT_RIGHT, p_a.type) {
			CASE_TYPE(math, OP_SHIFT_RIGHT, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
				if (p_b._data._int < 0 || p_b._data._int >= 64)
					_RETURN_FAIL;
				_RETURN(p_a._data._int >> p_b._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_SHIFT_RIGHT)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_BIT_AND, p_a.type) {
			CASE_TYPE(math, OP_BIT_AND, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
				_RETURN(p_a._data._int & p_b._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_BIT_AND)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_BIT_OR, p_a.type) {
			CASE_TYPE(math, OP_BIT_OR, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
				_RETURN(p_a._data._int | p_b._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_BIT_OR)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_BIT_XOR, p_a.type) {
			CASE_TYPE(math, OP_BIT_XOR, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
				_RETURN(p_a._data._int ^ p_b._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_BIT_XOR)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_BIT_NEGATE, p_a.type) {
			CASE_TYPE(math, OP_BIT_NEGATE, INT) {
				_RETURN(~p_a._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_BIT_NEGATE)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_AND, p_a.type) {
			CASE_TYPE_ALL(math, OP_AND) {
				bool l = p_a.booleanize();
				bool r = p_b.booleanize();

				_RETURN(l && r);
			}
		}

		SWITCH_OP(math, OP_OR, p_a.type) {
			CASE_TYPE_ALL(math, OP_OR) {
				bool l = p_a.booleanize();
				bool r = p_b.booleanize();

				_RETURN(l || r);
			}
		}

		SWITCH_OP(math, OP_XOR, p_a.type) {
			CASE_TYPE_ALL(math, OP_XOR) {
				bool l = p_a.booleanize();
				bool r = p_b.booleanize();

				_RETURN((l || r) && !(l && r));
			}
		}

		SWITCH_OP(math, OP_NOT, p_a.type) {
			CASE_TYPE_ALL(math, OP_NOT) {
				bool l = p_a.booleanize();
				_RETURN(!l);
			}
		}

		SWITCH_OP(math, OP_IN, p_a.type) {
			CASE_TYPE_ALL(math, OP_IN)
			_RETURN(p_b.in(p_a, &r_valid));
		}
	}
}

void Variant::set_named(const StringName &p_index, const Variant &p_value, bool *r_valid) {
	bool valid = false;
	switch (type) {
		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (unlikely(!obj)) {
#ifdef DEBUG_ENABLED
				if (_get_obj().rc) {
					ERR_PRINT("Attempted set on a deleted object.");
				}
#endif
				break;
			}
			obj->set(p_index, p_value, &valid);

		} break;
		default: {
			set(p_index.operator String(), p_value, &valid);
		} break;
	}

	if (r_valid) {
		*r_valid = valid;
	}
}

Variant Variant::get_named(const StringName &p_index, bool *r_valid) const {
	if (r_valid) {
		*r_valid = true;
	}
	switch (type) {
		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (unlikely(!obj)) {
				if (r_valid) {
					*r_valid = false;
				}
#ifdef DEBUG_ENABLED
				if (_get_obj().rc) {
					ERR_PRINT("Attempted get on a deleted object.");
				}
#endif
				return Variant();
			}

			return obj->get(p_index, r_valid);

		} break;
		case DICTIONARY: {
			const Dictionary *dic = reinterpret_cast<const Dictionary *>(_data._mem);
			const Variant *res = dic->getptr(p_index);
			if (!res) {
				// Backwards compatibility for before variants supported stringnames.
				const Variant *res2 = dic->getptr(p_index.operator String());

				if (res2) {
					if (r_valid) {
						*r_valid = true;
					}
					return *res2;
				}
			} else {
				if (r_valid) {
					*r_valid = true;
				}
				return *res;
			}
		} break;
		default: {
			return get(p_index.operator String(), r_valid);
		}
	}

	if (r_valid) {
		*r_valid = false;
	}
	return Variant();
}

#define DEFAULT_OP_ARRAY_CMD(m_name, m_type, skip_test, cmd)                             \
	case m_name: {                                                                       \
		skip_test;                                                                       \
                                                                                         \
		if (p_index.get_type() == Variant::INT || p_index.get_type() == Variant::REAL) { \
			int index = p_index;                                                         \
			m_type *arr = reinterpret_cast<m_type *>(_data._mem);                        \
                                                                                         \
			if (index < 0)                                                               \
				index += arr->size();                                                    \
			if (index >= 0 && index < arr->size()) {                                     \
				valid = true;                                                            \
				cmd;                                                                     \
			}                                                                            \
		}                                                                                \
	} break;

// clang-format 14 wants to add a space after the last return,
// and clang-format 15 removes it...
/* clang-format off */
#define DEFAULT_OP_DVECTOR_SET(m_name, dv_type, skip_cond) \
	DEFAULT_OP_ARRAY_CMD(m_name, PoolVector<dv_type>, if (skip_cond) return;, arr->set(index, p_value); return)
/* clang-format on */

#define DEFAULT_OP_DVECTOR_GET(m_name, dv_type) \
	DEFAULT_OP_ARRAY_CMD(m_name, const PoolVector<dv_type>, ;, return arr->get(index))

void Variant::set(const Variant &p_index, const Variant &p_value, bool *r_valid) {
	static bool _dummy = false;

	bool &valid = r_valid ? *r_valid : _dummy;
	valid = false;

	switch (type) {
		case NIL: {
			return;
		} break;
		case BOOL: {
			return;
		} break;
		case INT: {
			return;
		} break;
		case REAL: {
			return;
		} break;
		case STRING: {
			if (p_index.type != Variant::INT && p_index.type != Variant::REAL) {
				return;
			}

			int idx = p_index;
			String *str = reinterpret_cast<String *>(_data._mem);
			int len = str->length();
			if (idx < 0) {
				idx += len;
			}
			if (idx < 0 || idx >= len) {
				return;
			}

			String chr;
			if (p_value.type == Variant::INT || p_value.type == Variant::REAL) {
				chr = String::chr(p_value);
			} else if (p_value.type == Variant::STRING) {
				chr = p_value;
			} else {
				return;
			}

			*str = str->substr(0, idx) + chr + str->substr(idx + 1, len);
			valid = true;
			return;

		} break;

		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (unlikely(!obj)) {
				valid = false;
#ifdef DEBUG_ENABLED
				if (_get_obj().rc) {
					ERR_PRINT("Attempted set on a deleted object.");
				}
#endif
				return;
			}

			obj->set(p_index, p_value, r_valid);
			return;
		} break;
		case STRING_NAME: {
		} break;
		case DICTIONARY: {
			Dictionary *dic = reinterpret_cast<Dictionary *>(_data._mem);
			dic->operator[](p_index) = p_value;
			valid = true; //always valid, i guess? should this really be ok?
			return;
		} break;
			// clang-format 14 wants to add a space after the last return,
			// and clang-format 15 removes it...
			/* clang-format off */
			DEFAULT_OP_ARRAY_CMD(ARRAY, Array, ;, (*arr)[index] = p_value; return) // 20
			/* clang-format on */
			DEFAULT_OP_DVECTOR_SET(POOL_BYTE_ARRAY, uint8_t, p_value.type != Variant::REAL && p_value.type != Variant::INT)
			DEFAULT_OP_DVECTOR_SET(POOL_INT_ARRAY, int, p_value.type != Variant::REAL && p_value.type != Variant::INT)
			DEFAULT_OP_DVECTOR_SET(POOL_REAL_ARRAY, real_t, p_value.type != Variant::REAL && p_value.type != Variant::INT)
			DEFAULT_OP_DVECTOR_SET(POOL_STRING_ARRAY, String, p_value.type != Variant::STRING)
		default:
			return;
	}
}

Variant Variant::get(const Variant &p_index, bool *r_valid) const {
	static bool _dummy = false;

	bool &valid = r_valid ? *r_valid : _dummy;

	valid = false;

	switch (type) {
		case NIL: {
			return Variant();
		} break;
		case BOOL: {
			return Variant();
		} break;
		case INT: {
			return Variant();
		} break;
		case REAL: {
			return Variant();
		} break;
		case STRING: {
			if (p_index.get_type() == Variant::INT || p_index.get_type() == Variant::REAL) {
				//string index

				int idx = p_index;
				const String *str = reinterpret_cast<const String *>(_data._mem);
				if (idx < 0) {
					idx += str->length();
				}
				if (idx >= 0 && idx < str->length()) {
					valid = true;
					return str->substr(idx, 1);
				}
			}

		} break;
	
		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (unlikely(!obj)) {
				valid = false;
#ifdef DEBUG_ENABLED
				if (_get_obj().rc) {
					ERR_PRINT("Attempted get on a deleted object.");
				}
#endif
				return Variant();
			}

			return obj->get(p_index, r_valid);

		} break;
		case STRING_NAME: {
		} break;
		case DICTIONARY: {
			const Dictionary *dic = reinterpret_cast<const Dictionary *>(_data._mem);
			const Variant *res = dic->getptr(p_index);
			if (res) {
				valid = true;
				return *res;
			}
		} break;
			DEFAULT_OP_ARRAY_CMD(ARRAY, const Array, ;, return (*arr)[index]) // 20
			DEFAULT_OP_DVECTOR_GET(POOL_BYTE_ARRAY, uint8_t)
			DEFAULT_OP_DVECTOR_GET(POOL_INT_ARRAY, int)
			DEFAULT_OP_DVECTOR_GET(POOL_REAL_ARRAY, real_t)
			DEFAULT_OP_DVECTOR_GET(POOL_STRING_ARRAY, String)
		default:
			return Variant();
	}

	return Variant();
}

bool Variant::in(const Variant &p_index, bool *r_valid) const {
	if (r_valid) {
		*r_valid = true;
	}

	switch (type) {
		case STRING: {
			if (p_index.get_type() == Variant::STRING) {
				//string index
				String idx = p_index;
				const String *str = reinterpret_cast<const String *>(_data._mem);

				return str->find(idx) != -1;
			}

		} break;
		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (unlikely(!obj)) {
				if (r_valid) {
					*r_valid = false;
				}
#ifdef DEBUG_ENABLED
				if (_get_obj().rc) {
					ERR_PRINT("Attempted 'in' on a deleted object.");
				}
#endif
				return false;
			}

			bool result;
			obj->get(p_index, &result);
			return result;
		} break;
		case DICTIONARY: {
			const Dictionary *dic = reinterpret_cast<const Dictionary *>(_data._mem);
			return dic->has(p_index);

		} break; // 20
		case ARRAY: {
			const Array *arr = reinterpret_cast<const Array *>(_data._mem);
			int l = arr->size();
			if (l) {
				for (int i = 0; i < l; i++) {
					if (evaluate(OP_EQUAL, (*arr)[i], p_index)) {
						return true;
					}
				}
			}

			return false;

		} break;
		case POOL_BYTE_ARRAY: {
			if (p_index.get_type() == Variant::INT || p_index.get_type() == Variant::REAL) {
				int index = p_index;
				const PoolVector<uint8_t> *arr = reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
				int l = arr->size();
				if (l) {
					PoolVector<uint8_t>::Read r = arr->read();
					for (int i = 0; i < l; i++) {
						if (r[i] == index) {
							return true;
						}
					}
				}

				return false;
			}

		} break;
		case POOL_INT_ARRAY: {
			if (p_index.get_type() == Variant::INT || p_index.get_type() == Variant::REAL) {
				int index = p_index;
				const PoolVector<int> *arr = reinterpret_cast<const PoolVector<int> *>(_data._mem);
				int l = arr->size();
				if (l) {
					PoolVector<int>::Read r = arr->read();
					for (int i = 0; i < l; i++) {
						if (r[i] == index) {
							return true;
						}
					}
				}

				return false;
			}
		} break;
		case POOL_REAL_ARRAY: {
			if (p_index.get_type() == Variant::INT || p_index.get_type() == Variant::REAL) {
				real_t index = p_index;
				const PoolVector<real_t> *arr = reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
				int l = arr->size();
				if (l) {
					PoolVector<real_t>::Read r = arr->read();
					for (int i = 0; i < l; i++) {
						if (r[i] == index) {
							return true;
						}
					}
				}

				return false;
			}

		} break;
		case POOL_STRING_ARRAY: {
			if (p_index.get_type() == Variant::STRING) {
				String index = p_index;
				const PoolVector<String> *arr = reinterpret_cast<const PoolVector<String> *>(_data._mem);

				int l = arr->size();
				if (l) {
					PoolVector<String>::Read r = arr->read();
					for (int i = 0; i < l; i++) {
						if (r[i] == index) {
							return true;
						}
					}
				}

				return false;
			}

		} break; //25
	
		default: {
		}
	}

	if (r_valid) {
		*r_valid = false;
	}
	return false;
}

bool Variant::iter_init(Variant &r_iter, bool &valid) const {
	valid = true;
	switch (type) {
		case INT: {
			r_iter = 0;
			return _data._int > 0;
		} break;
		case REAL: {
			r_iter = 0;
			return _data._real > 0.0;
		} break;
		case STRING: {
			const String *str = reinterpret_cast<const String *>(_data._mem);
			if (str->empty()) {
				return false;
			}
			r_iter = 0;
			return true;
		} break;
		case DICTIONARY: {
			const Dictionary *dic = reinterpret_cast<const Dictionary *>(_data._mem);
			if (dic->empty()) {
				return false;
			}

			const Variant *next = dic->next(nullptr);
			r_iter = *next;
			return true;

		} break;
		case ARRAY: {
			const Array *arr = reinterpret_cast<const Array *>(_data._mem);
			if (arr->empty()) {
				return false;
			}
			r_iter = 0;
			return true;
		} break;
		case POOL_BYTE_ARRAY: {
			const PoolVector<uint8_t> *arr = reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
			if (arr->size() == 0) {
				return false;
			}
			r_iter = 0;
			return true;

		} break;
		case POOL_INT_ARRAY: {
			const PoolVector<int> *arr = reinterpret_cast<const PoolVector<int> *>(_data._mem);
			if (arr->size() == 0) {
				return false;
			}
			r_iter = 0;
			return true;

		} break;
		case POOL_REAL_ARRAY: {
			const PoolVector<real_t> *arr = reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
			if (arr->size() == 0) {
				return false;
			}
			r_iter = 0;
			return true;

		} break;
		case POOL_STRING_ARRAY: {
			const PoolVector<String> *arr = reinterpret_cast<const PoolVector<String> *>(_data._mem);
			if (arr->size() == 0) {
				return false;
			}
			r_iter = 0;
			return true;
		} break;
		default: {
		}
	}

	valid = false;
	return false;
}
bool Variant::iter_next(Variant &r_iter, bool &valid) const {
	valid = true;
	switch (type) {
		case INT: {
			int64_t idx = r_iter;
			idx++;
			if (idx >= _data._int) {
				return false;
			}
			r_iter = idx;
			return true;
		} break;
		case REAL: {
			int64_t idx = r_iter;
			idx++;
			if (idx >= _data._real) {
				return false;
			}
			r_iter = idx;
			return true;
		} break;
		case STRING: {
			const String *str = reinterpret_cast<const String *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= str->length()) {
				return false;
			}
			r_iter = idx;
			return true;
		} break;
		case DICTIONARY: {
			const Dictionary *dic = reinterpret_cast<const Dictionary *>(_data._mem);
			const Variant *next = dic->next(&r_iter);
			if (!next) {
				return false;
			}

			r_iter = *next;
			return true;

		} break;
		case ARRAY: {
			const Array *arr = reinterpret_cast<const Array *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= arr->size()) {
				return false;
			}
			r_iter = idx;
			return true;
		} break;
		case POOL_BYTE_ARRAY: {
			const PoolVector<uint8_t> *arr = reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= arr->size()) {
				return false;
			}
			r_iter = idx;
			return true;

		} break;
		case POOL_INT_ARRAY: {
			const PoolVector<int> *arr = reinterpret_cast<const PoolVector<int> *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= arr->size()) {
				return false;
			}
			r_iter = idx;
			return true;

		} break;
		case POOL_REAL_ARRAY: {
			const PoolVector<real_t> *arr = reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= arr->size()) {
				return false;
			}
			r_iter = idx;
			return true;

		} break;
		case POOL_STRING_ARRAY: {
			const PoolVector<String> *arr = reinterpret_cast<const PoolVector<String> *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= arr->size()) {
				return false;
			}
			r_iter = idx;
			return true;
		} break;
		default: {
		}
	}

	valid = false;
	return false;
}

Variant Variant::iter_get(const Variant &r_iter, bool &r_valid) const {
	r_valid = true;
	switch (type) {
		case INT: {
			return r_iter;
		} break;
		case REAL: {
			return r_iter;
		} break;
		case STRING: {
			const String *str = reinterpret_cast<const String *>(_data._mem);
			return str->substr(r_iter, 1);
		} break;
		case DICTIONARY: {
			return r_iter; //iterator is the same as the key

		} break;
		case ARRAY: {
			const Array *arr = reinterpret_cast<const Array *>(_data._mem);
			int idx = r_iter;
#ifdef DEBUG_ENABLED
			if (idx < 0 || idx >= arr->size()) {
				r_valid = false;
				return Variant();
			}
#endif
			return arr->get(idx);
		} break;
		case POOL_BYTE_ARRAY: {
			const PoolVector<uint8_t> *arr = reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
			int idx = r_iter;
#ifdef DEBUG_ENABLED
			if (idx < 0 || idx >= arr->size()) {
				r_valid = false;
				return Variant();
			}
#endif
			return arr->get(idx);
		} break;
		case POOL_INT_ARRAY: {
			const PoolVector<int> *arr = reinterpret_cast<const PoolVector<int> *>(_data._mem);
			int idx = r_iter;
#ifdef DEBUG_ENABLED
			if (idx < 0 || idx >= arr->size()) {
				r_valid = false;
				return Variant();
			}
#endif
			return arr->get(idx);
		} break;
		case POOL_REAL_ARRAY: {
			const PoolVector<real_t> *arr = reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
			int idx = r_iter;
#ifdef DEBUG_ENABLED
			if (idx < 0 || idx >= arr->size()) {
				r_valid = false;
				return Variant();
			}
#endif
			return arr->get(idx);
		} break;
		case POOL_STRING_ARRAY: {
			const PoolVector<String> *arr = reinterpret_cast<const PoolVector<String> *>(_data._mem);
			int idx = r_iter;
#ifdef DEBUG_ENABLED
			if (idx < 0 || idx >= arr->size()) {
				r_valid = false;
				return Variant();
			}
#endif
			return arr->get(idx);
		} break;
		default: {
		}
	}

	r_valid = false;
	return Variant();
}

Variant Variant::duplicate(bool deep) const {
	switch (type) {
		case OBJECT: {
			/*  breaks stuff :(
			if (deep && !_get_obj().ref.is_null()) {
				Ref<Resource> resource = _get_obj().ref;
				if (resource.is_valid()) {
					return resource->duplicate(true);
				}
			}
			*/
			return *this;
		} break;
		case DICTIONARY:
			return operator Dictionary().duplicate(deep);
		case ARRAY:
			return operator Array().duplicate(deep);
		default:
			return *this;
	}
}

void Variant::sub(const Variant &a, const Variant &b, Variant &r_dst) {
	if (a.type != b.type) {
		return;
	}

	switch (a.type) {
		case NIL: {
			r_dst = Variant();
		}
			return;
		case INT: {
			int64_t va = a._data._int;
			int64_t vb = b._data._int;
			r_dst = int(va - vb);
		}
			return;
		case REAL: {
			real_t ra = a._data._real;
			real_t rb = b._data._real;
			r_dst = ra - rb;
		}
			return;
		default: {
			r_dst = a;
		}
			return;
	}
}

void Variant::blend(const Variant &a, const Variant &b, float c, Variant &r_dst) {
	if (a.type != b.type) {
		if (a.is_num() && b.is_num()) {
			real_t va = a;
			real_t vb = b;
			r_dst = va + vb * c;
		} else {
			r_dst = a;
		}
		return;
	}

	switch (a.type) {
		case NIL: {
			r_dst = Variant();
		}
			return;
		case INT: {
			int64_t va = a._data._int;
			int64_t vb = b._data._int;
			r_dst = int(va + vb * c + 0.5);
		}
			return;
		case REAL: {
			double ra = a._data._real;
			double rb = b._data._real;
			r_dst = ra + rb * c;
		}
			return;
		default: {
			r_dst = c < 0.5 ? a : b;
		}
			return;
	}
}

void Variant::interpolate(const Variant &a, const Variant &b, float c, Variant &r_dst) {
	if (a.type != b.type) {
		if (a.is_num() && b.is_num()) {
			//not as efficient but..
			real_t va = a;
			real_t vb = b;
			r_dst = va + (vb - va) * c;

		} else {
			r_dst = a;
		}
		return;
	}

	switch (a.type) {
		case NIL: {
			r_dst = Variant();
		}
			return;
		case BOOL: {
			r_dst = a;
		}
			return;
		case INT: {
			int64_t va = a._data._int;
			int64_t vb = b._data._int;
			r_dst = int(va + (vb - va) * c);
		}
			return;
		case REAL: {
			real_t va = a._data._real;
			real_t vb = b._data._real;
			r_dst = va + (vb - va) * c;
		}
			return;
		case STRING: {
			//this is pretty funny and bizarre, but artists like to use it for typewritter effects
			String sa = *reinterpret_cast<const String *>(a._data._mem);
			String sb = *reinterpret_cast<const String *>(b._data._mem);
			String dst;
			int sa_len = sa.length();
			int sb_len = sb.length();
			int csize = sa_len + (sb_len - sa_len) * c;
			if (csize == 0) {
				r_dst = "";
				return;
			}
			dst.resize(csize + 1);
			dst[csize] = 0;
			int split = csize / 2;

			for (int i = 0; i < csize; i++) {
				CharType chr = ' ';

				if (i < split) {
					if (i < sa.length()) {
						chr = sa[i];
					} else if (i < sb.length()) {
						chr = sb[i];
					}

				} else {
					if (i < sb.length()) {
						chr = sb[i];
					} else if (i < sa.length()) {
						chr = sa[i];
					}
				}

				dst[i] = chr;
			}

			r_dst = dst;
		}
			return;
		case OBJECT: {
			r_dst = a;
		}
			return;
		case STRING_NAME: {
			r_dst = a;
		}
			return;
		case DICTIONARY: {
		}
			return;
		case ARRAY: {
			r_dst = a;
		}
			return;
		case POOL_BYTE_ARRAY: {
			r_dst = a;
		}
			return;
		case POOL_INT_ARRAY: {
			const PoolVector<int> *arr_a = reinterpret_cast<const PoolVector<int> *>(a._data._mem);
			const PoolVector<int> *arr_b = reinterpret_cast<const PoolVector<int> *>(b._data._mem);
			int sz = arr_a->size();
			if (sz == 0 || arr_b->size() != sz) {
				r_dst = a;
			} else {
				PoolVector<int> v;
				v.resize(sz);
				{
					PoolVector<int>::Write vw = v.write();
					PoolVector<int>::Read ar = arr_a->read();
					PoolVector<int>::Read br = arr_b->read();

					Variant va;
					for (int i = 0; i < sz; i++) {
						Variant::interpolate(ar[i], br[i], c, va);
						vw[i] = va;
					}
				}
				r_dst = v;
			}
		}
			return;
		case POOL_REAL_ARRAY: {
			const PoolVector<real_t> *arr_a = reinterpret_cast<const PoolVector<real_t> *>(a._data._mem);
			const PoolVector<real_t> *arr_b = reinterpret_cast<const PoolVector<real_t> *>(b._data._mem);
			int sz = arr_a->size();
			if (sz == 0 || arr_b->size() != sz) {
				r_dst = a;
			} else {
				PoolVector<real_t> v;
				v.resize(sz);
				{
					PoolVector<real_t>::Write vw = v.write();
					PoolVector<real_t>::Read ar = arr_a->read();
					PoolVector<real_t>::Read br = arr_b->read();

					Variant va;
					for (int i = 0; i < sz; i++) {
						Variant::interpolate(ar[i], br[i], c, va);
						vw[i] = va;
					}
				}
				r_dst = v;
			}
		}
			return;
		case POOL_STRING_ARRAY: {
			r_dst = a;
		}
			return;
		default: {
			r_dst = a;
		}
	}
}

static const char *_op_names[Variant::OP_MAX] = {
	"==",
	"!=",
	"<",
	"<=",
	">",
	">=",
	"+",
	"-",
	"*",
	"/",
	"- (negation)",
	"+ (positive)",
	"%",
	"+ (concatenation)",
	"<<",
	">>",
	"&",
	"|",
	"^",
	"~",
	"and",
	"or",
	"xor",
	"not",
	"in"

};

String Variant::get_operator_name(Operator p_op) {
	ERR_FAIL_INDEX_V(p_op, OP_MAX, "");
	return _op_names[p_op];
}

#undef CASE_TYPE_ALL
#undef CASE_TYPE_ALL_BUT_INT
#undef TYPE
#undef TYPES
#undef CASES
#undef SWITCH
#undef SWITCH_OP
#undef CASE_TYPE
#undef CASES
#undef SWITCH
#undef SWITCH_OP
#undef CASE_TYPE
#undef _RETURN
#undef _RETURN_FAIL
#undef DEFAULT_OP_NUM
#undef DEFAULT_OP_NUM_NULL
#undef DEFAULT_OP_NUM_DIV
#undef DEFAULT_OP_NUM_DIV
#undef DEFAULT_OP_NUM_NEG
#undef DEFAULT_OP_NUM_POS
#undef DEFAULT_OP_NUM_VEC
#undef DEFAULT_OP_STR_REV
#undef DEFAULT_OP_STR
#undef DEFAULT_OP_STR_NULL
#undef DEFAULT_OP_STR_NULL_NP
#undef DEFAULT_OP_STR_NULL_SN
#undef DEFAULT_OP_LOCALMEM_REV
#undef DEFAULT_OP_LOCALMEM
#undef DEFAULT_OP_LOCALMEM_NULL
#undef DEFAULT_OP_LOCALMEM_NEG
#undef DEFAULT_OP_LOCALMEM_POS
#undef DEFAULT_OP_LOCALMEM_NUM
#undef DEFAULT_OP_PTR
#undef DEFAULT_OP_PTRREF
#undef DEFAULT_OP_PTRREF_NULL
#undef DEFAULT_OP_ARRAY_EQ
#undef DEFAULT_OP_ARRAY_NEQ
#undef DEFAULT_OP_ARRAY_LT
#undef DEFAULT_OP_ARRAY_GT
#undef DEFAULT_OP_ARRAY_OP
#undef DEFAULT_OP_ARRAY_OP_BODY
#undef DEFAULT_OP_ARRAY_ADD
#undef DEFAULT_OP_ARRAY_CMD
#undef DEFAULT_OP_DVECTOR_SET
#undef DEFAULT_OP_DVECTOR_GET
