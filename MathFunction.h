#pragma once
#include"Matrix4x4.h"
#include"Vector3.h"


	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	Matrix4x4 MakeRotateXMatrix(float radian);

	Matrix4x4 MakeRotateYMatrix(float radian);

	Matrix4x4 MakeRotateZMatrix(float radian);

	Matrix4x4
	    MakeAffineMatrix(const Vector3& scale, const Vector3 rotate, const Vector3& translate);

	Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

	Matrix4x4 Inverse(Matrix4x4& m);

	Matrix4x4 Multiply2(const Vector3& v, const Matrix4x4& m);

	Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

	Matrix4x4 MakeViewportMatrix(
	    float left, float top, float width, float height, float minDepth, float maxDepth);

	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

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

	Vector3 Multiply(float scalar, float scalar2);

	float Add3(Vector3 v, const Vector3& v2);

	Vector3 Division(Vector3 v, int num);

	float Length(const Vector3& v);

