/**
 * @class Vec2f
 * @brief Basic 2D std::vector class.
 * 
 * Used for storing and returning 2D points and std::vectors.
 *
 * @author Simon Manning
 * @version 0.a
 * @date 12-04-2011
 */

#ifndef _VEC2F_H_
#define _VEC2F_H_


class Vec2f
{
  public:
    Vec2f() {}
	Vec2f(float a,float b);
    float x;
    float y;
	void operator=(const Vec2f& vec);
	bool operator==(const Vec2f& vec);
	bool operator!=(const Vec2f& vec);
	operator float*(){ return (float*) this; } 
};


#endif