#pragma once

#include <cmath>
#include <array>

class Vector3
{
public:
    union
    {
        struct {
            float x;
            float y;
            float z;
        };
        std::array<float, 3> v;
    };

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float s) : x(s), y(s), z(s) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    Vector3 operator-() const { return { -x, -y, -z }; }
    Vector3 operator+(const Vector3& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
    Vector3 operator-(const Vector3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
    Vector3 operator*(float s) const { return { x * s, y * s, z * s }; }
    Vector3 operator/(float s) const { return { x / s, y / s, z / s }; }

    Vector3& operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
    Vector3& operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }

    float MagnitudeSquared() const { return (x * x) + (y * y) + (z * z); }
    float Magnitude() const { return sqrtf(MagnitudeSquared()); }

    float DistanceSquared(const Vector3& rhs) const
    {
        float dx = x - rhs.x;
        float dy = y - rhs.y;
        float dz = z - rhs.z;
        return dx * dx + dy * dy + dz * dz;
    }

    float Distance(const Vector3& rhs) const { return sqrtf(DistanceSquared(rhs)); }
};
