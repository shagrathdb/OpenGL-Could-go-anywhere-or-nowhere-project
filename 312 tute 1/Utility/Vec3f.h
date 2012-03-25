/**
 * @class Vec3f
 * @brief 3D std::vector math class and utilities.
 * @author Simon Manning
 * @version 0.2
 * @date 17-03-2011
 */

#ifndef _VEC3F_H_
#define _VEC3F_H_

#include <iostream>


class Vec3f
{
  public:
    /** std::vector dimensions: public due to mass use. */
    float x;
    float y;
    float z;
    
    /** Default constructor: initialises to zero-length std::vector. */
    Vec3f();
    /** Constructor for initialisation with given dimensions. */
    Vec3f(float newX, float newY, float newZ);
    
    /** Copy constructor. */
    Vec3f(const Vec3f& copy);
    
    /** Normalise the std::vector. */
    void Normalise();
    /** Caluclates normalised value without changing the std::vectors values. */
    static Vec3f Normalise(const Vec3f& vec);
    
    /**
     * Gets absolute magnitude of the std::vector.
     * @return Length (magnitude) of std::vector
     */
    float Magnitude();
    
    /**
     * Gets squared magnitude of the std::vector.
     * Useful for std::vector length comparison (faster).
     * @return Length (magnitude) squared of std::vector
     */
    float MagnitudeSq();
    
    /**
     * Gets the distance between two points in 3D space.
     * @param vec1 First point
     * @param vec2 Second point
     * @return Distance between the two points
     */
    static float Distance(const Vec3f& vec1, const Vec3f& vec2);

    /**
     * Gets the distance between two points in 3D space as magnitude^2.
     * @param vec1 First point
     * @param vec2 Second point
     * @return Distance between the two points
     */
    static float DistanceSq(const Vec3f& vec1, const Vec3f& vec2);
    
    /**
     * Calculates the dot product of two std::vectors.
     * @param vec1 First std::vector
     * @param vec2 Second std::vector
     * @return Dot product of the two std::vectors
     */
    static float Dot(const Vec3f& vec1, const Vec3f& vec2);
     
    /**
     * Calculates the cross product of two std::vectors.
     * @param vec1 First std::vector
     * @param vec2 Second std::vector
     * @return Cross product of the two std::vectors.
     */
    static Vec3f Cross(const Vec3f& vec1, const Vec3f& vec2);


	Vec3f Cross(const Vec3f& opVec);
	void Clear();
    
    /** @name Operator overloading. */
    /*@{*/
    bool operator == (const Vec3f& v) const;
    bool operator != (const Vec3f& v) const;
    
    Vec3f operator - (const Vec3f& v) const;
    Vec3f operator + (const Vec3f& v) const;
    Vec3f operator / (float f) const;
    Vec3f operator * (float f) const;
    
    Vec3f& operator += (const Vec3f& v);
    Vec3f& operator -= (const Vec3f& v);
    Vec3f& operator *= (float f);
    Vec3f& operator /= (float f);
    
    friend Vec3f operator - (const Vec3f& v);
    /*@}*/
	operator float*(){ return (float*) this; } 
};

inline Vec3f operator - (const Vec3f &v)
{
    return Vec3f(-v.x, -v.y, -v.z);
}


#endif