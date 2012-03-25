/**
 * @class Mat4f
 * @brief 4x4 Matrix class.
 * @author Simon Manning
 * @version 0.2
 * @date 07-04-2011
 */

#ifndef __MAT4F_H__
#define __MAT4F_H__

#include "../utility/Vec3f.h"
#include <cmath>

class Mat4f
{
  public:
    /** Constructors. */
    Mat4f() {};
    Mat4f(float n11, float n12, float n13, float n14,
         float n21, float n22, float n23, float n24,
         float n31, float n32, float n33, float n34,
         float n41, float n42, float n43, float n44);
    ~Mat4f() {};
    
    /** Set matrix to identity matrix. */
    void Identity();
    
    /** Perform a matrix rotation.
     *  @param rotAxis Axis to rotate on.
     *  @param deg Rotation amount in degrees.
     */
    void Rotate(const Vec3f& rotAxis, float deg);
    
    /** @name Operator overloading. */
    /*@{*/
    Mat4f operator + (const Mat4f &op) const;
    Mat4f operator - (const Mat4f &op) const;
    Mat4f operator * (const Mat4f &op) const;
    Mat4f operator * (const float scalar) const;
    Mat4f operator / (const float scalar) const;
    
    Mat4f& operator += (const Mat4f& op);
    Mat4f& operator -= (const Mat4f& op);
    Mat4f& operator *= (const Mat4f& op);
    Mat4f& operator *= (const float scalar);
    Mat4f& operator /= (const float scalar);
    
    float* operator[] (int row);
    const float* operator[] (int row) const;
    
    friend Vec3f  operator * (const Vec3f& v, const Mat4f& m);
    friend Mat4f operator * (float s, const Mat4f& m);
    /*@}*/
    
    static const Mat4f IMatrix;

	operator float*() { return (float*) mat; }
	operator const float*() const { return (const float*) mat; }

    float mat[4][4];
};

inline Vec3f operator * (const Vec3f& v, const Mat4f& m)
{
    return Vec3f((v.x * m.mat[0][0]) + (v.y * m.mat[1][0]) + (v.z * m.mat[2][0]),
        (v.x * m.mat[0][1]) + (v.y * m.mat[1][1]) + (v.z * m.mat[2][1]),
        (v.x * m.mat[0][2]) + (v.y * m.mat[1][2]) + (v.z * m.mat[2][2]));
}

inline Mat4f operator * (float s, const Mat4f& m)
{
    return m * s;
}


#endif