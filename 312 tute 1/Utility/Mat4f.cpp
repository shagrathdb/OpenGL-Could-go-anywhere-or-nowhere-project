/**
 * @file mat4.cpp
 * @brief Matrix class implementation file.
 * @author Simon Manning
 * @version 0.1
 * @date 26-08-2010
 */

#include "../utility/Mat4f.h"
#include <cmath>


const Mat4f Mat4f::IMatrix(1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);

Mat4f::Mat4f(float n11, float n12, float n13, float n14,
           float n21, float n22, float n23, float n24,
           float n31, float n32, float n33, float n34,
           float n41, float n42, float n43, float n44)
{
    mat[0][0] = n11, mat[0][1] = n12, mat[0][2] = n13, mat[0][3] = n14;
    mat[1][0] = n21, mat[1][1] = n22, mat[1][2] = n23, mat[1][3] = n24;
    mat[2][0] = n31, mat[2][1] = n32, mat[2][2] = n33, mat[2][3] = n34;
    mat[3][0] = n41, mat[3][1] = n42, mat[3][2] = n43, mat[3][3] = n44;
}

void Mat4f::Identity()
{
    mat[0][0] = 1.0f, mat[0][1] = 0.0f, mat[0][2] = 0.0f, mat[0][3] = 0.0f;
    mat[1][0] = 0.0f, mat[1][1] = 1.0f, mat[1][2] = 0.0f, mat[1][3] = 0.0f;
    mat[2][0] = 0.0f, mat[2][1] = 0.0f, mat[2][2] = 1.0f, mat[2][3] = 0.0f;
    mat[3][0] = 0.0f, mat[3][1] = 0.0f, mat[3][2] = 0.0f, mat[3][3] = 1.0f;
}

void Mat4f::Rotate(const Vec3f& rotAxis, float deg)
{
    float x, y, z;
    float cosD, sinD;
    
    /// Convert degrees to radians
    deg = (deg * 3.14159265358f) / 180.0f;
    
    x = rotAxis.x;
    y = rotAxis.y;
    z = rotAxis.z;
    
    cosD = cosf(deg);
    sinD = sinf(deg);
    
    mat[0][0] = (x * x) * (1.0f - cosD) + cosD;
    mat[0][1] = (x * y) * (1.0f - cosD) + (z * sinD);
    mat[0][2] = (x * z) * (1.0f - cosD) - (y * sinD);
    mat[0][3] = 0.0f;

    mat[1][0] = (y * x) * (1.0f - cosD) - (z * sinD);
    mat[1][1] = (y * y) * (1.0f - cosD) + cosD;
    mat[1][2] = (y * z) * (1.0f - cosD) + (x * sinD);
    mat[1][3] = 0.0f;

    mat[2][0] = (z * x) * (1.0f - cosD) + (y * sinD);
    mat[2][1] = (z * y) * (1.0f - cosD) - (x * sinD);
    mat[2][2] = (z * z) * (1.0f - cosD) + cosD;
    mat[2][3] = 0.0f;

    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
}

Mat4f Mat4f::operator + (const Mat4f &op) const
{
    Mat4f temp(*this);
    temp += op;
    
    return temp;
}

Mat4f Mat4f::operator - (const Mat4f &op) const
{
    Mat4f temp(*this);
    temp -= op;
    
    return temp;
}

Mat4f Mat4f::operator * (const Mat4f &op) const
{
    Mat4f temp(*this);
    temp *= op;
    
    return temp;
}

Mat4f Mat4f::operator * (const float scalar) const
{
    Mat4f temp(*this);
    temp *= scalar;
    
    return temp;
}

Mat4f Mat4f::operator / (const float scalar) const
{
    Mat4f temp(*this);
    temp /= scalar;
    
    return temp;
}

Mat4f& Mat4f::operator += (const Mat4f& op)
{
    int i, j;
    
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            mat[i][j] += op.mat[i][j];
        }
    }

    return *this;
}

Mat4f& Mat4f::operator -= (const Mat4f& op)
{
    int i, j;
    
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            mat[i][j] -= op.mat[i][j];
        }
    }

    return *this;    
}

Mat4f& Mat4f::operator *= (const Mat4f& op)
{
    Mat4f temp;
    
    temp.mat[0][0] = (mat[0][0] * op.mat[0][0]) + (mat[0][1] * op.mat[1][0]) + (mat[0][2] * op.mat[2][0]) + (mat[0][3] * op.mat[3][0]);
    temp.mat[0][1] = (mat[0][0] * op.mat[0][1]) + (mat[0][1] * op.mat[1][1]) + (mat[0][2] * op.mat[2][1]) + (mat[0][3] * op.mat[3][1]);
    temp.mat[0][2] = (mat[0][0] * op.mat[0][2]) + (mat[0][1] * op.mat[1][2]) + (mat[0][2] * op.mat[2][2]) + (mat[0][3] * op.mat[3][2]);
    temp.mat[0][3] = (mat[0][0] * op.mat[0][3]) + (mat[0][1] * op.mat[1][3]) + (mat[0][2] * op.mat[2][3]) + (mat[0][3] * op.mat[3][3]);

    temp.mat[1][0] = (mat[1][0] * op.mat[0][0]) + (mat[1][1] * op.mat[1][0]) + (mat[1][2] * op.mat[2][0]) + (mat[1][3] * op.mat[3][0]);
    temp.mat[1][1] = (mat[1][0] * op.mat[0][1]) + (mat[1][1] * op.mat[1][1]) + (mat[1][2] * op.mat[2][1]) + (mat[1][3] * op.mat[3][1]);
    temp.mat[1][2] = (mat[1][0] * op.mat[0][2]) + (mat[1][1] * op.mat[1][2]) + (mat[1][2] * op.mat[2][2]) + (mat[1][3] * op.mat[3][2]);
    temp.mat[1][3] = (mat[1][0] * op.mat[0][3]) + (mat[1][1] * op.mat[1][3]) + (mat[1][2] * op.mat[2][3]) + (mat[1][3] * op.mat[3][3]);

    temp.mat[2][0] = (mat[2][0] * op.mat[0][0]) + (mat[2][1] * op.mat[1][0]) + (mat[2][2] * op.mat[2][0]) + (mat[2][3] * op.mat[3][0]);
    temp.mat[2][1] = (mat[2][0] * op.mat[0][1]) + (mat[2][1] * op.mat[1][1]) + (mat[2][2] * op.mat[2][1]) + (mat[2][3] * op.mat[3][1]);
    temp.mat[2][2] = (mat[2][0] * op.mat[0][2]) + (mat[2][1] * op.mat[1][2]) + (mat[2][2] * op.mat[2][2]) + (mat[2][3] * op.mat[3][2]);
    temp.mat[2][3] = (mat[2][0] * op.mat[0][3]) + (mat[2][1] * op.mat[1][3]) + (mat[2][2] * op.mat[2][3]) + (mat[2][3] * op.mat[3][3]);

    temp.mat[3][0] = (mat[3][0] * op.mat[0][0]) + (mat[3][1] * op.mat[1][0]) + (mat[3][2] * op.mat[2][0]) + (mat[3][3] * op.mat[3][0]);
    temp.mat[3][1] = (mat[3][0] * op.mat[0][1]) + (mat[3][1] * op.mat[1][1]) + (mat[3][2] * op.mat[2][1]) + (mat[3][3] * op.mat[3][1]);
    temp.mat[3][2] = (mat[3][0] * op.mat[0][2]) + (mat[3][1] * op.mat[1][2]) + (mat[3][2] * op.mat[2][2]) + (mat[3][3] * op.mat[3][2]);
    temp.mat[3][3] = (mat[3][0] * op.mat[0][3]) + (mat[3][1] * op.mat[1][3]) + (mat[3][2] * op.mat[2][3]) + (mat[3][3] * op.mat[3][3]);
    
    *this = temp;
    return *this;
}

Mat4f& Mat4f::operator *= (const float scalar)
{
    int i, j;
    
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            mat[i][j] *= scalar;
        }
    }

    return *this;    
}

Mat4f& Mat4f::operator /= (const float scalar)
{
    int i, j;
    
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            mat[i][j] /= scalar;
        }
    }

    return *this;    
}

float* Mat4f::operator[] (int row)
{
    return mat[row];
}

const float* Mat4f::operator[] (int row) const
{
    return mat[row];
}
