/*************************************************************************/
/*  vector2.cpp                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/vector2.h"
#include "core/vector2i.h"

#include "core/ustring.h"
//--STRIP

real_t Vector2::angle() const {
	return Math::atan2(y, x);
}

real_t Vector2::length() const {
	return Math::sqrt(x * x + y * y);
}

real_t Vector2::length_squared() const {
	return x * x + y * y;
}

void Vector2::normalize() {
	real_t l = x * x + y * y;
	if (l != 0) {
		l = Math::sqrt(l);
		x /= l;
		y /= l;
	}
}

Vector2 Vector2::normalized() const {
	Vector2 v = *this;
	v.normalize();
	return v;
}

bool Vector2::is_normalized() const {
	// use length_squared() instead of length() to avoid sqrt(), makes it more stringent.
	return Math::is_equal_approx(length_squared(), 1, (real_t)UNIT_EPSILON);
}

real_t Vector2::distance_to(const Vector2 &p_vector2) const {
	return Math::sqrt((x - p_vector2.x) * (x - p_vector2.x) + (y - p_vector2.y) * (y - p_vector2.y));
}

real_t Vector2::distance_squared_to(const Vector2 &p_vector2) const {
	return (x - p_vector2.x) * (x - p_vector2.x) + (y - p_vector2.y) * (y - p_vector2.y);
}

real_t Vector2::angle_to(const Vector2 &p_vector2) const {
	return Math::atan2(cross(p_vector2), dot(p_vector2));
}

real_t Vector2::angle_to_point(const Vector2 &p_vector2) const {
	return Math::atan2(y - p_vector2.y, x - p_vector2.x);
}

real_t Vector2::dot(const Vector2 &p_other) const {
	return x * p_other.x + y * p_other.y;
}

real_t Vector2::cross(const Vector2 &p_other) const {
	return x * p_other.y - y * p_other.x;
}

Vector2 Vector2::sign() const {
	return Vector2(SGN(x), SGN(y));
}

Vector2 Vector2::floor() const {
	return Vector2(Math::floor(x), Math::floor(y));
}

Vector2 Vector2::ceil() const {
	return Vector2(Math::ceil(x), Math::ceil(y));
}

Vector2 Vector2::round() const {
	return Vector2(Math::round(x), Math::round(y));
}

Vector2 Vector2::rotated(real_t p_by) const {
	Vector2 v;
	v.set_rotation(angle() + p_by);
	v *= length();
	return v;
}

Vector2 Vector2::posmod(const real_t p_mod) const {
	return Vector2(Math::fposmod(x, p_mod), Math::fposmod(y, p_mod));
}

Vector2 Vector2::posmodv(const Vector2 &p_modv) const {
	return Vector2(Math::fposmod(x, p_modv.x), Math::fposmod(y, p_modv.y));
}

Vector2 Vector2::project(const Vector2 &p_to) const {
	return p_to * (dot(p_to) / p_to.length_squared());
}

Vector2 Vector2::snapped(const Vector2 &p_by) const {
	return Vector2(
			Math::stepify(x, p_by.x),
			Math::stepify(y, p_by.y));
}

Vector2 Vector2::limit_length(const real_t p_len) const {
	const real_t l = length();
	Vector2 v = *this;
	if (l > 0 && p_len < l) {
		v /= l;
		v *= p_len;
	}

	return v;
}

Vector2 Vector2::move_toward(const Vector2 &p_to, const real_t p_delta) const {
	Vector2 v = *this;
	Vector2 vd = p_to - v;
	real_t len = vd.length();
	return len <= p_delta || len < (real_t)CMP_EPSILON ? p_to : v + vd / len * p_delta;
}

// slide returns the component of the vector along the given plane, specified by its normal vector.
Vector2 Vector2::slide(const Vector2 &p_normal) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!p_normal.is_normalized(), Vector2(), "The normal Vector2 must be normalized.");
#endif
	return *this - p_normal * this->dot(p_normal);
}

Vector2 Vector2::bounce(const Vector2 &p_normal) const {
	return -reflect(p_normal);
}

Vector2 Vector2::reflect(const Vector2 &p_normal) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!p_normal.is_normalized(), Vector2(), "The normal Vector2 must be normalized.");
#endif
	return 2 * p_normal * this->dot(p_normal) - *this;
}

bool Vector2::is_equal_approx(const Vector2 &p_v) const {
	return Math::is_equal_approx(x, p_v.x) && Math::is_equal_approx(y, p_v.y);
}

bool Vector2::is_zero_approx() const {
	return Math::is_zero_approx(x) && Math::is_zero_approx(y);
}

Vector2::operator String() const {
	return "(" + String::num_real(x) + ", " + String::num_real(y) + ")";
}

Vector2::operator Vector2i() const {
	return Vector2i(x, y);
}
