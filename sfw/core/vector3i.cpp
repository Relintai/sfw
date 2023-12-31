/*************************************************************************/
/*  vector3i.cpp                                                         */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#include "core/vector3i.h"

#include "core/vector3.h"
#include "core/ustring.h"

void Vector3i::set_axis(const int p_axis, const int32_t p_value) {
	ERR_FAIL_INDEX(p_axis, 3);
	coord[p_axis] = p_value;
}

int32_t Vector3i::get_axis(const int p_axis) const {
	ERR_FAIL_INDEX_V(p_axis, 3, 0);
	return operator[](p_axis);
}

Vector3i::Axis Vector3i::min_axis() const {
	return x < y ? (x < z ? Vector3i::AXIS_X : Vector3i::AXIS_Z) : (y < z ? Vector3i::AXIS_Y : Vector3i::AXIS_Z);
}

Vector3i::Axis Vector3i::max_axis() const {
	return x < y ? (y < z ? Vector3i::AXIS_Z : Vector3i::AXIS_Y) : (x < z ? Vector3i::AXIS_Z : Vector3i::AXIS_X);
}

Vector3i Vector3i::clamp(const Vector3i &p_min, const Vector3i &p_max) const {
	return Vector3i(
			CLAMP(x, p_min.x, p_max.x),
			CLAMP(y, p_min.y, p_max.y),
			CLAMP(z, p_min.z, p_max.z));
}

Vector3 Vector3i::to_vector3() const {
	return Vector3(x, y, z);
}

Vector3i::operator String() const {
	return "(" + itos(x) + ", " + itos(y) + ", " + itos(z) + ")";
}

Vector3i::operator Vector3() const {
	return Vector3(x, y, z);
}
