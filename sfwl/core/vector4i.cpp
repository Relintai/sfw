/*************************************************************************/
/*  vector4i.cpp                                                         */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/vector4i.h"

#include "core/vector4.h"
#include "core/ustring.h"
//--STRIP

void Vector4i::set_axis(const int p_axis, const int32_t p_value) {
	ERR_FAIL_INDEX(p_axis, 4);
	coord[p_axis] = p_value;
}

int32_t Vector4i::get_axis(const int p_axis) const {
	ERR_FAIL_INDEX_V(p_axis, 4, 0);
	return operator[](p_axis);
}

Vector4i::Axis Vector4i::min_axis() const {
	uint32_t min_index = 0;
	int32_t min_value = x;
	for (uint32_t i = 1; i < 4; i++) {
		if (operator[](i) <= min_value) {
			min_index = i;
			min_value = operator[](i);
		}
	}
	return Vector4i::Axis(min_index);
}

Vector4i::Axis Vector4i::max_axis() const {
	uint32_t max_index = 0;
	int32_t max_value = x;
	for (uint32_t i = 1; i < 4; i++) {
		if (operator[](i) > max_value) {
			max_index = i;
			max_value = operator[](i);
		}
	}
	return Vector4i::Axis(max_index);
}

Vector4i Vector4i::clamp(const Vector4i &p_min, const Vector4i &p_max) const {
	return Vector4i(
			CLAMP(x, p_min.x, p_max.x),
			CLAMP(y, p_min.y, p_max.y),
			CLAMP(z, p_min.z, p_max.z),
			CLAMP(w, p_min.w, p_max.w));
}

Vector4i Vector4i::linear_interpolate(const Vector4i &p_to, const real_t p_weight) const {
	return Vector4i(
			x + (p_weight * (p_to.x - x)),
			y + (p_weight * (p_to.y - y)),
			z + (p_weight * (p_to.z - z)),
			w + (p_weight * (p_to.w - w)));
}

Vector4 Vector4i::to_vector4() const {
	return Vector4(x, y, z, w);
}

Vector4i::operator String() const {
	return "(" + itos(x) + ", " + itos(y) + ", " + itos(z) + ", " + itos(w) + ")";
}

Vector4i::operator Vector4() const {
	return Vector4(x, y, z, w);
}

/*
Vector4i::Vector4i(const Vector4 &p_vec4) {
	x = p_vec4.x;
	y = p_vec4.y;
	z = p_vec4.z;
	w = p_vec4.w;
}
*/
