//--STRIP
#ifndef VECTOR2I_H
#define VECTOR2I_H
//--STRIP

/*************************************************************************/
/*  vector2i.h                                                           */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/error_macros.h"
#include "core/math_funcs.h"

#include "core/vector2.h"
//--STRIP

class String;

struct _NO_DISCARD_CLASS_ Vector2i {
	enum Axis {
		AXIS_X,
		AXIS_Y,
	};

	union {
		struct {
			union {
				int x;
				int width;
			};
			union {
				int y;
				int height;
			};
		};

		int coord[2];
	};

	_FORCE_INLINE_ int &operator[](int p_idx) {
		DEV_ASSERT((unsigned int)p_idx < 2);
		return coord[p_idx];
	}
	_FORCE_INLINE_ const int &operator[](int p_idx) const {
		DEV_ASSERT((unsigned int)p_idx < 2);
		return coord[p_idx];
	}

	_FORCE_INLINE_ void set_all(int p_value) {
		x = y = p_value;
	}

	_FORCE_INLINE_ int min_axis() const {
		return x < y ? 0 : 1;
	}

	_FORCE_INLINE_ int max_axis() const {
		return x < y ? 1 : 0;
	}

	Vector2i min(const Vector2i &p_vector2i) const {
		return Vector2i(MIN(x, p_vector2i.x), MIN(y, p_vector2i.y));
	}

	Vector2i max(const Vector2i &p_vector2i) const {
		return Vector2i(MAX(x, p_vector2i.x), MAX(y, p_vector2i.y));
	}

	_FORCE_INLINE_ static Vector2i linear_interpolate(const Vector2i &p_a, const Vector2i &p_b, real_t p_weight);
	_FORCE_INLINE_ Vector2i linear_interpolate(const Vector2i &p_to, real_t p_weight) const;

	Vector2i operator+(const Vector2i &p_v) const;
	void operator+=(const Vector2i &p_v);
	Vector2i operator-(const Vector2i &p_v) const;
	void operator-=(const Vector2i &p_v);
	Vector2i operator*(const Vector2i &p_v1) const;

	Vector2i operator*(const int &rvalue) const;
	void operator*=(const int &rvalue);

	Vector2i operator/(const Vector2i &p_v1) const;

	Vector2i operator/(const int &rvalue) const;

	void operator/=(const int &rvalue);

	Vector2i operator-() const;
	bool operator<(const Vector2i &p_vec2) const { return (x == p_vec2.x) ? (y < p_vec2.y) : (x < p_vec2.x); }
	bool operator>(const Vector2i &p_vec2) const { return (x == p_vec2.x) ? (y > p_vec2.y) : (x > p_vec2.x); }
	bool operator<=(const Vector2 &p_vec2) const { return x == p_vec2.x ? (y <= p_vec2.y) : (x < p_vec2.x); }
	bool operator>=(const Vector2 &p_vec2) const { return x == p_vec2.x ? (y >= p_vec2.y) : (x > p_vec2.x); }

	bool operator==(const Vector2i &p_vec2) const;
	bool operator!=(const Vector2i &p_vec2) const;

	int64_t length_squared() const;
	double length() const;

	real_t aspect() const { return width / (real_t)height; }
	Vector2i sign() const { return Vector2i(SGN(x), SGN(y)); }
	Vector2i abs() const { return Vector2i(ABS(x), ABS(y)); }
	Vector2i clamp(const Vector2i &p_min, const Vector2i &p_max) const;

	Vector2 to_vector2() const { return Vector2(x, y); }

	operator String() const;
	operator Vector2() const { return Vector2(x, y); }

	inline Vector2i(int p_x, int p_y) {
		x = p_x;
		y = p_y;
	}
	inline Vector2i() {
		x = 0;
		y = 0;
	}
};

Vector2i Vector2i::linear_interpolate(const Vector2i &p_a, const Vector2i &p_b, real_t p_weight) {
	Vector2i res = p_a;

	res.x += (p_weight * (p_b.x - p_a.x));
	res.y += (p_weight * (p_b.y - p_a.y));

	return res;
}

Vector2i Vector2i::linear_interpolate(const Vector2i &p_to, real_t p_weight) const {
	Vector2 res = *this;

	res.x += (p_weight * (p_to.x - x));
	res.y += (p_weight * (p_to.y - y));

	return res;
}

typedef Vector2i Size2i;
typedef Vector2i Point2i;

//--STRIP
#endif // VECTOR2_H
//--STRIP
