#pragma once

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3() : x(0), y(0), z(0)
	{
	}
	Vector3(float value) : x(value), y(value), z(value)
	{
	}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{
	}

	float DistanceSquared(const Vector3& rhs) const
	{
		return (x - rhs.x) * (x - rhs.x) +
			(y - rhs.y) * (y - rhs.y) +
			(z - rhs.z) * (z - rhs.z);
	}

	const float* Data() const
	{
		return &x;
	}
};