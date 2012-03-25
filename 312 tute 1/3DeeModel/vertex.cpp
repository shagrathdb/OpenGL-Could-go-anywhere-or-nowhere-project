
#include "vertex.h"

/**
 * @fn	Vertex3f::Vertex3f(const float x, const float y, const float z)
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

Vertex3f::Vertex3f(const float x, const float y, const float z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}

/**
 * @fn	void Vertex3f::operator=(const Vertex3f& vertex)
 *
 * @brief	= casting operator.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	vertex	The vertex.
 */

void Vertex3f::operator=(const Vertex3f& vertex)
{
	x=vertex.x;
	y=vertex.y;
	z=vertex.z;
}

/**
 * @fn	void Vertex3f::operator=(const Vec3f& vec)
 *
 * @brief	= casting operator.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	vec	The vector.
 */

void Vertex3f::operator=(const Vec3f& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

/**
 * @fn	void Vertex3f::operator*=(const Vec3f& vec)
 *
 * @brief	*= casting operator.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	vec	The vector.
 */

void Vertex3f::operator*=(const Vec3f& vec)
{
	x*=vec.x;
	y*=vec.y;
	z*=vec.z;
}