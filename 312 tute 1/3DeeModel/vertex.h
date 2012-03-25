

#ifndef __VERTEX_H__
#define __VERTEX_H__


#include "../Utility/Vec3f.h"

/**
 * @class	Vertex3f
 *
 * @brief	Vertex 3f. 
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 */

class Vertex3f
{
	public:

    /**
     * @fn	Vertex3f::Vertex3f()
     *
     * @brief	Default constructor.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     */

    Vertex3f():x(0),y(0),z(0) {}

	/**
	 * @fn	Vertex3f::Vertex3f(const float x,const float y,const float z);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 * @param	z	The z coordinate.
	 */

	Vertex3f(const float x,const float y,const float z);
    ///< The x coordinate
    float x;
    ///< The y coordinate
    float y;
	///< The z coordinate
	float z;

	/**
	 * @fn	void Vertex3f::operator=(const Vertex3f& vertex);
	 *
	 * @brief	Assignment operator.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	vertex	The vertex.
	 */

	void operator=(const Vertex3f& vertex);

	/**
	 * @fn	operator Vertex3f::float*()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 */

	operator float*(){ return (float*) this; } 

	/**
	 * @fn	void Vertex3f::operator=(const Vec3f& vec);
	 *
	 * @brief	Assignment operator.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	vec	The vector.
	 */

	void operator=(const Vec3f& vec);

	/**
	 * @fn	void Vertex3f::operator*=(const Vec3f& vec);
	 *
	 * @brief	Multiplication assignment operator.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	vec	The vector.
	 */

	void operator*=(const Vec3f& vec);
};

#endif