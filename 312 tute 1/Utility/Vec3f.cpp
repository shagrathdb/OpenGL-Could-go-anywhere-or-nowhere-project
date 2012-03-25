#include "../utility/Vec3f.h"
#include "../utility/HMath.h"

#include <cmath>
#include <iostream>


Vec3f::Vec3f()
{
    x = 0;
    y = 0;
    z = 0;
}

Vec3f::Vec3f(float newX, float newY, float newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}

Vec3f::Vec3f(const Vec3f& copy)
{
    x = copy.x;
    y = copy.y;
    z = copy.z;
}

void Vec3f::Normalise()
{
    /*if (x == 0 && y == 0 && z == 0) return;
    
    float length = Magnitude();
    
    *this = *this / length;*/
    float magInv = 1.0f / Magnitude();

    x *= magInv;
    y *= magInv;
    z *= magInv;
}

/* static */ Vec3f Vec3f::Normalise(const Vec3f& vec)
{
    Vec3f tempVec(vec);
    tempVec.Normalise();
    return tempVec;
}

float Vec3f::Magnitude()
{
    return sqrtf((x * x) + (y * y) + (z * z));
    //return Math::FastSqrt(MagnitudeSq());
}

float Vec3f::MagnitudeSq()
{
    return (x * x) + (y * y) + (z * z);
}

/* static */ float Vec3f::Distance(const Vec3f& vec1, const Vec3f& vec2)
{
    return Vec3f(vec1 - vec2).Magnitude();
}

/* static */ float Vec3f::DistanceSq(const Vec3f& vec1, const Vec3f& vec2)
{
    return Vec3f(vec1 - vec2).MagnitudeSq();
}

/* static */ float Vec3f::Dot(const Vec3f& vec1, const Vec3f& vec2)
{
    return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

/* static */ Vec3f Vec3f::Cross(const Vec3f& vec1, const Vec3f& vec2)
{
    Vec3f cross(0, 0, 0);
    
    if (vec1.x == 0 && vec1.y == 0 && vec1.z == 0) return cross;
    if (vec2.x == 0 && vec2.y == 0 && vec2.z == 0) return cross;
    
    cross.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
    cross.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
    cross.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
    
    return cross;
}

Vec3f Vec3f::Cross(const Vec3f& opVec)
{
	Vec3f cross(0, 0, 0);
    
	if (x == 0 && y == 0 && z == 0) return cross;
    
	cross.x = (y * opVec.z) - (z * opVec.y);
	cross.y = (z * opVec.x) - (x * opVec.z);
	cross.z = (x * opVec.y) - (y * opVec.x);
    
	return cross;
}

void Vec3f::Clear()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

bool Vec3f::operator == (const Vec3f& v) const
{
    return x == v.x && y == v.y && z == v.z;
}

bool Vec3f::operator != (const Vec3f& v) const
{
    return !(*this == v);
}

Vec3f Vec3f::operator - (const Vec3f& v) const
{
    return Vec3f(x - v.x, y - v.y, z - v.z);
}

Vec3f Vec3f::operator + (const Vec3f& v) const
{
    return Vec3f(x + v.x, y + v.y, z + v.z);
}

Vec3f Vec3f::operator / (float f) const
{
    return Vec3f(x / f, y / f, z / f);
}

Vec3f Vec3f::operator * (float f) const
{
    return Vec3f(x * f, y * f, z * f);
}

Vec3f& Vec3f::operator += (const Vec3f& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    
    return *this;
}

Vec3f& Vec3f::operator -= (const Vec3f& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    
    return *this;
}

Vec3f& Vec3f::operator *= (float f)
{
    x *= f;
    y *= f;
    z *= f;
    
    return *this;
}

Vec3f& Vec3f::operator /= (float f)
{
    x /= f;
    y /= f;
    z /= f;
    
    return *this;
}