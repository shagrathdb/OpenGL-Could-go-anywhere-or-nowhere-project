
#include "texcoord2f.h"

/**
 * @fn	TexCoord2f::TexCoord2f(const float u, const float v)
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	u	The u.
 * @param	v	The v.
 */

TexCoord2f::TexCoord2f(const float u, const float v)
{
	this->u=u;
	this->v=v;
}

/**
 * @fn	void TexCoord2f::operator=(const TexCoord2f& texcoord)
 *
 * @brief	= casting operator.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	texcoord	The texcoord.
 */

void TexCoord2f::operator=(const TexCoord2f& texcoord)
{
	u = texcoord.u;
	v = texcoord.v;
}

