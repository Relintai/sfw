/*************************************************************************/
/*  quaternion.cpp                                                       */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/quaternion.h"

#include "core/basis.h"
//--STRIP

real_t Quaternion::angle_to(const Quaternion &p_to) const {
	real_t d = dot(p_to);

	// acos does clamping.
	return Math::acos(d * d * 2 - 1);
}

// set_euler_xyz expects a vector containing the Euler angles in the format
// (ax,ay,az), where ax is the angle of rotation around x axis,
// and similar for other axes.
// This implementation uses XYZ convention (Z is the first rotation).
void Quaternion::set_euler_xyz(const Vector3 &p_euler) {
	real_t half_a1 = p_euler.x * 0.5f;
	real_t half_a2 = p_euler.y * 0.5f;
	real_t half_a3 = p_euler.z * 0.5f;

	// R = X(a1).Y(a2).Z(a3) convention for Euler angles.
	// Conversion to quaternion as listed in https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770024290.pdf (page A-2)
	// a3 is the angle of the first rotation, following the notation in this reference.

	real_t cos_a1 = Math::cos(half_a1);
	real_t sin_a1 = Math::sin(half_a1);
	real_t cos_a2 = Math::cos(half_a2);
	real_t sin_a2 = Math::sin(half_a2);
	real_t cos_a3 = Math::cos(half_a3);
	real_t sin_a3 = Math::sin(half_a3);

	set(sin_a1 * cos_a2 * cos_a3 + sin_a2 * sin_a3 * cos_a1,
			-sin_a1 * sin_a3 * cos_a2 + sin_a2 * cos_a1 * cos_a3,
			sin_a1 * sin_a2 * cos_a3 + sin_a3 * cos_a1 * cos_a2,
			-sin_a1 * sin_a2 * sin_a3 + cos_a1 * cos_a2 * cos_a3);
}

// get_euler_xyz returns a vector containing the Euler angles in the format
// (ax,ay,az), where ax is the angle of rotation around x axis,
// and similar for other axes.
// This implementation uses XYZ convention (Z is the first rotation).
Vector3 Quaternion::get_euler_xyz() const {
	Basis m(*this);
	return m.get_euler_xyz();
}

// set_euler_yxz expects a vector containing the Euler angles in the format
// (ax,ay,az), where ax is the angle of rotation around x axis,
// and similar for other axes.
// This implementation uses YXZ convention (Z is the first rotation).
void Quaternion::set_euler_yxz(const Vector3 &p_euler) {
	real_t half_a1 = p_euler.y * 0.5f;
	real_t half_a2 = p_euler.x * 0.5f;
	real_t half_a3 = p_euler.z * 0.5f;

	// R = Y(a1).X(a2).Z(a3) convention for Euler angles.
	// Conversion to quaternion as listed in https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770024290.pdf (page A-6)
	// a3 is the angle of the first rotation, following the notation in this reference.

	real_t cos_a1 = Math::cos(half_a1);
	real_t sin_a1 = Math::sin(half_a1);
	real_t cos_a2 = Math::cos(half_a2);
	real_t sin_a2 = Math::sin(half_a2);
	real_t cos_a3 = Math::cos(half_a3);
	real_t sin_a3 = Math::sin(half_a3);

	set(sin_a1 * cos_a2 * sin_a3 + cos_a1 * sin_a2 * cos_a3,
			sin_a1 * cos_a2 * cos_a3 - cos_a1 * sin_a2 * sin_a3,
			-sin_a1 * sin_a2 * cos_a3 + cos_a1 * cos_a2 * sin_a3,
			sin_a1 * sin_a2 * sin_a3 + cos_a1 * cos_a2 * cos_a3);
}

// get_euler_yxz returns a vector containing the Euler angles in the format
// (ax,ay,az), where ax is the angle of rotation around x axis,
// and similar for other axes.
// This implementation uses YXZ convention (Z is the first rotation).
Vector3 Quaternion::get_euler_yxz() const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!is_normalized(), Vector3(0, 0, 0), "The quaternion must be normalized.");
#endif
	Basis m(*this);
	return m.get_euler_yxz();
}

void Quaternion::operator*=(const Quaternion &p_q) {
	set(w * p_q.x + x * p_q.w + y * p_q.z - z * p_q.y,
			w * p_q.y + y * p_q.w + z * p_q.x - x * p_q.z,
			w * p_q.z + z * p_q.w + x * p_q.y - y * p_q.x,
			w * p_q.w - x * p_q.x - y * p_q.y - z * p_q.z);
}

Quaternion Quaternion::operator*(const Quaternion &p_q) const {
	Quaternion r = *this;
	r *= p_q;
	return r;
}

bool Quaternion::is_equal_approx(const Quaternion &p_quat) const {
	return Math::is_equal_approx(x, p_quat.x) && Math::is_equal_approx(y, p_quat.y) && Math::is_equal_approx(z, p_quat.z) && Math::is_equal_approx(w, p_quat.w);
}

real_t Quaternion::length() const {
	return Math::sqrt(length_squared());
}

void Quaternion::normalize() {
	*this /= length();
}

Quaternion Quaternion::normalized() const {
	return *this / length();
}

bool Quaternion::is_normalized() const {
	return Math::is_equal_approx(length_squared(), 1, (real_t)UNIT_EPSILON); //use less epsilon
}

Quaternion Quaternion::inverse() const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!is_normalized(), Quaternion(), "The quaternion must be normalized.");
#endif
	return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::log() const {
	Quaternion src = *this;
	Vector3 src_v = src.get_axis() * src.get_angle();
	return Quaternion(src_v.x, src_v.y, src_v.z, 0);
}

Quaternion Quaternion::exp() const {
	Quaternion src = *this;
	Vector3 src_v = Vector3(src.x, src.y, src.z);
	float theta = src_v.length();
	if (theta < CMP_EPSILON) {
		return Quaternion(0, 0, 0, 1);
	}
	return Quaternion(src_v.normalized(), theta);
}

Quaternion Quaternion::slerp(const Quaternion &p_to, const real_t &p_weight) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!is_normalized(), Quaternion(), "The start quaternion must be normalized.");
	ERR_FAIL_COND_V_MSG(!p_to.is_normalized(), Quaternion(), "The end quaternion must be normalized.");
#endif
	Quaternion to1;
	real_t omega, cosom, sinom, scale0, scale1;

	// calc cosine
	cosom = dot(p_to);

	// adjust signs (if necessary)
	if (cosom < 0) {
		cosom = -cosom;
		to1.x = -p_to.x;
		to1.y = -p_to.y;
		to1.z = -p_to.z;
		to1.w = -p_to.w;
	} else {
		to1.x = p_to.x;
		to1.y = p_to.y;
		to1.z = p_to.z;
		to1.w = p_to.w;
	}

	// calculate coefficients

	if ((1 - cosom) > (real_t)CMP_EPSILON) {
		// standard case (slerp)
		omega = Math::acos(cosom);
		sinom = Math::sin(omega);
		scale0 = Math::sin((1 - p_weight) * omega) / sinom;
		scale1 = Math::sin(p_weight * omega) / sinom;
	} else {
		// "from" and "to" quaternions are very close
		//  ... so we can do a linear interpolation
		scale0 = 1 - p_weight;
		scale1 = p_weight;
	}
	// calculate final values
	return Quaternion(
			scale0 * x + scale1 * to1.x,
			scale0 * y + scale1 * to1.y,
			scale0 * z + scale1 * to1.z,
			scale0 * w + scale1 * to1.w);
}

Quaternion Quaternion::slerpni(const Quaternion &p_to, const real_t &p_weight) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!is_normalized(), Quaternion(), "The start quaternion must be normalized.");
	ERR_FAIL_COND_V_MSG(!p_to.is_normalized(), Quaternion(), "The end quaternion must be normalized.");
#endif
	const Quaternion &from = *this;

	real_t dot = from.dot(p_to);

	if (Math::absf(dot) > 0.9999f) {
		return from;
	}

	real_t theta = Math::acos(dot),
		   sinT = 1 / Math::sin(theta),
		   newFactor = Math::sin(p_weight * theta) * sinT,
		   invFactor = Math::sin((1 - p_weight) * theta) * sinT;

	return Quaternion(invFactor * from.x + newFactor * p_to.x,
			invFactor * from.y + newFactor * p_to.y,
			invFactor * from.z + newFactor * p_to.z,
			invFactor * from.w + newFactor * p_to.w);
}

Quaternion Quaternion::cubic_slerp(const Quaternion &p_b, const Quaternion &p_pre_a, const Quaternion &p_post_b, const real_t &p_weight) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!is_normalized(), Quaternion(), "The start quaternion must be normalized.");
	ERR_FAIL_COND_V_MSG(!p_b.is_normalized(), Quaternion(), "The end quaternion must be normalized.");
#endif
	//the only way to do slerp :|
	real_t t2 = (1 - p_weight) * p_weight * 2;
	Quaternion sp = this->slerp(p_b, p_weight);
	Quaternion sq = p_pre_a.slerpni(p_post_b, p_weight);
	return sp.slerpni(sq, t2);
}

Quaternion Quaternion::spherical_cubic_interpolate(const Quaternion &p_b, const Quaternion &p_pre_a, const Quaternion &p_post_b, const real_t &p_weight) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!is_normalized(), Quaternion(), "The start quaternion must be normalized.");
	ERR_FAIL_COND_V_MSG(!p_b.is_normalized(), Quaternion(), "The end quaternion must be normalized.");
#endif
	Quaternion from_q = *this;
	Quaternion pre_q = p_pre_a;
	Quaternion to_q = p_b;
	Quaternion post_q = p_post_b;

	// Align flip phases.
	from_q = Basis(from_q).get_rotation_quaternion();
	pre_q = Basis(pre_q).get_rotation_quaternion();
	to_q = Basis(to_q).get_rotation_quaternion();
	post_q = Basis(post_q).get_rotation_quaternion();

	// Flip quaternions to shortest path if necessary.
	bool flip1 = signbit(from_q.dot(pre_q));
	pre_q = flip1 ? -pre_q : pre_q;
	bool flip2 = signbit(from_q.dot(to_q));
	to_q = flip2 ? -to_q : to_q;
	bool flip3 = flip2 ? to_q.dot(post_q) <= 0 : signbit(to_q.dot(post_q));
	post_q = flip3 ? -post_q : post_q;

	// Calc by Expmap in from_q space.
	Quaternion ln_from = Quaternion(0, 0, 0, 0);
	Quaternion ln_to = (from_q.inverse() * to_q).log();
	Quaternion ln_pre = (from_q.inverse() * pre_q).log();
	Quaternion ln_post = (from_q.inverse() * post_q).log();
	Quaternion ln = Quaternion(0, 0, 0, 0);
	ln.x = Math::cubic_interpolate(ln_from.x, ln_to.x, ln_pre.x, ln_post.x, p_weight);
	ln.y = Math::cubic_interpolate(ln_from.y, ln_to.y, ln_pre.y, ln_post.y, p_weight);
	ln.z = Math::cubic_interpolate(ln_from.z, ln_to.z, ln_pre.z, ln_post.z, p_weight);
	Quaternion q1 = from_q * ln.exp();

	// Calc by Expmap in to_q space.
	ln_from = (to_q.inverse() * from_q).log();
	ln_to = Quaternion(0, 0, 0, 0);
	ln_pre = (to_q.inverse() * pre_q).log();
	ln_post = (to_q.inverse() * post_q).log();
	ln = Quaternion(0, 0, 0, 0);
	ln.x = Math::cubic_interpolate(ln_from.x, ln_to.x, ln_pre.x, ln_post.x, p_weight);
	ln.y = Math::cubic_interpolate(ln_from.y, ln_to.y, ln_pre.y, ln_post.y, p_weight);
	ln.z = Math::cubic_interpolate(ln_from.z, ln_to.z, ln_pre.z, ln_post.z, p_weight);
	Quaternion q2 = to_q * ln.exp();

	// To cancel error made by Expmap ambiguity, do blends.
	return q1.slerp(q2, p_weight);
}

Vector3 Quaternion::get_axis() const {
	if (Math::abs(w) > 1 - CMP_EPSILON) {
		return Vector3(x, y, z);
	}
	real_t r = ((real_t)1) / Math::sqrt(1 - w * w);
	return Vector3(x * r, y * r, z * r);
}

float Quaternion::get_angle() const {
	return 2 * Math::acos(w);
}

Quaternion::operator String() const {
	return "(" + String::num_real(x) + ", " + String::num_real(y) + ", " + String::num_real(z) + ", " + String::num_real(w) + ")";
}

void Quaternion::set_axis_angle(const Vector3 &axis, const real_t &angle) {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_MSG(!axis.is_normalized(), "The axis Vector3 must be normalized.");
#endif
	real_t d = axis.length();
	if (d == 0) {
		set(0, 0, 0, 0);
	} else {
		real_t sin_angle = Math::sin(angle * 0.5f);
		real_t cos_angle = Math::cos(angle * 0.5f);
		real_t s = sin_angle / d;
		set(axis.x * s, axis.y * s, axis.z * s,
				cos_angle);
	}
}
