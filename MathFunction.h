#pragma once
#include"Matrix4x4.h"
#include"Vector3.h"
class MathFunction {

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



};
