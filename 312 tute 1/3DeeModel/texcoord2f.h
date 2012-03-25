

#ifndef _TEX2F_H_
#define _TEX2F_H_

/**
 * @class	TexCoord2f
 *
 * @brief	Tex coordinate 2f. 
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

class TexCoord2f
{
  public:

    /**
     * @fn	TexCoord2f::TexCoord2f()
     *
     * @brief	Default constructor.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     */

    TexCoord2f():u(0),v(0) {}

	/**
	 * @fn	TexCoord2f::TexCoord2f(const float u,const float v);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	u	a.
	 * @param	v	The.
	 */

	TexCoord2f(const float u,const float v);

	/**
	 * @fn	void TexCoord2f::operator=(const TexCoord2f& texcoord);
	 *
	 * @brief	Assignment operator.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	texcoord	The texcoord.
	 */

	void operator=(const TexCoord2f& texcoord);

	/**
	 * @fn	operator TexCoord2f::float*()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 */

	operator float*(){ return (float*) this; }
	///< The u
	float u;
    ///< The v
    float v;
};


#endif