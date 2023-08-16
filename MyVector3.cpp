#include "Matrix4x4.h"
#include "Vector3.h"
#include <cassert>
#include <cmath>
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 Normalize(const Vector3& v) {
	Vector3 result;
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	assert(length != 0.0f);
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return result;
}

Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

bool CollisionDot(
    const Vector3& v1, const Vector3& v2, const Vector3& radius, const Vector3& radius2) {

	float distance = Dot(v1, v2);
	float distance2 = Add2(radius, radius2);
	if (distance <= distance2) {
		return true;
	}

	return false;
}

float Dot(const Vector3& v1, const Vector3& v2) {

	float x = (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) +
	          (v2.z - v1.z) * (v2.z - v1.z);
	return x;
}
float Add2(const Vector3& v1, const Vector3& v2) {
	float x = (v1.x + v1.y + v1.z + v2.x + v2.y + v2.z);

	return x;
}