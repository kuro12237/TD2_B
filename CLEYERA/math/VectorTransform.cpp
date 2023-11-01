#include "VectorTransform.h"

float VectorTransform::Length(const Vector3& v)
{
	float result{};
	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

Vector3 VectorTransform::Add(const Vector3 &v1, const Vector3 &v2)
{
	Vector3 result{};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 VectorTransform::Subtruct(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 VectorTransform::Multiply(const Vector3& v1, const float& v2)
{
	Vector3 result{};
	result.x = v1.x * v2;
	result.y = v1.y * v2;
	result.z = v1.z * v2;
	return result;
}

Vector3 VectorTransform::Multiply(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return result;
}

Vector3 VectorTransform::TransformNormal(const Vector3& v, const Matrix4x4& m)
{
	Vector3 result
	{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};

	return result;

}

Vector3 VectorTransform::Normalize(const Vector3& v)
{
	Vector3 result{};
	float length = Length(v);
	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	return result;
}

Vector3 VectorTransform::Lerp(const Vector3& v1, const Vector3& v2, float t)
{
	Vector3 result{};
	result.x = v1.x + t * (v2.x - v1.x);
	result.y = v1.y + t * (v2.y - v1.y);
	result.z = v1.z + t * (v2.z - v1.z);
	return result;
}

float VectorTransform::Dot(const Vector3& v1, const Vector3& v2) {
	float result;
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

Vector3 VectorTransform::SlerpFanc(Vector3 start, Vector3 end, float t)
{
	float dot = start.x * end.x + start.y * end.y + start.z * end.z;
	float theta = std::acos(dot) * t;
	Vector3 relative = { end.x - start.x * dot, end.y - start.y * dot, end.z - start.z * dot };
	relative = Normalize(relative);
	Vector3 result = {
		start.x * std::cosf(theta) + relative.x * std::sinf(theta),
		start.y * std::cosf(theta) + relative.y * std::sinf(theta),
		start.z * std::cosf(theta) + relative.z * std::sinf(theta)
	};

	return result;
}

Vector4 VectorTransform::Subtruct(const Vector4& v1, const Vector4& v2)
{
	Vector4 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	result.w = v1.w - v2.w;
	return result;
}

