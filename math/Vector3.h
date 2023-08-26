#pragma once

//#include "Matrix4x4.h"
/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
};

Vector3 Add(const Vector3& v1, const Vector3& v2);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Vector3 Normalize(const Vector3& v);

Vector3 Multiply(float scalar, const Vector3& v);

bool CollisionDot(
    const Vector3& v1, const Vector3& v2, const Vector3& radius, const Vector3& radius2);

float Dot(const Vector3& v1, const Vector3& v2);

float Add2(const Vector3& v1, const Vector3& v2);

Vector3 Multiply2(const Vector3& v1, const Vector3& v2);

Vector3 Subtract2(float position, const Vector3& v);