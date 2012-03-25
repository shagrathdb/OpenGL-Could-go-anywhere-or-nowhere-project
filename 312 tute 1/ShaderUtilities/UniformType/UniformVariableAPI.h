

#ifndef __UNIFORMVARAPI_H__
#define __UNIFORMVARAPI_H__

#include "../../Utility/ImpVector2.h"
#include "../../Utility/Vec3f.h"


/**
 * @class	UniformVar
 *
 * @brief	Uniform variable. 
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

class UniformVar
{
public:

	/**
	 * @fn	virtual void UniformVar::Update() = 0;
	 *
	 * @brief	Updates this object.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	virtual void Update() = 0;

	/**
	 * @fn	virtual int UniformVar::Get_Uniform_loc(const unsigned int program)=0;
	 *
	 * @brief	Gets a uniform location.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param	program	The program.
	 *
	 * @return	The uniform location.
	 */

	virtual int Get_Uniform_loc(const unsigned int program)=0;

	/**
	 * @fn	virtual void UniformVar::Set_Uniform_ref(const unsigned int uni_ref)=0;
	 *
	 * @brief	Sets a uniform reference.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param	uni_ref	The uni reference.
	 */

	virtual void Set_Uniform_ref(const unsigned int uni_ref)=0;
};

/**
 * @class	Uniform1f
 *
 * @brief	Uniform 1f. 
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

class Uniform1f
{
	/**
	 * @fn	virtual void Uniform1f::Set_Uniform_data(float* onef)=0;
	 *
	 * @brief	Sets a uniform data.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param [in,out]	onef	If non-null, the onef.
	 */

	virtual void Set_Uniform_data(float* onef)=0;
};

/**
 * @class	UniformVec2
 *
 * @brief	Uniform std::vector 2. 
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

class UniformVec2
{
	/**
	 * @fn	virtual void UniformVec2::Set_Uniform_data(Vec2f* vec2)=0;
	 *
	 * @brief	Sets a uniform data.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param [in,out]	vec2	If non-null, the second std::vector.
	 */

	virtual void Set_Uniform_data(Vector2<float>* vec2)=0;
};

/**
 * @class	UniformVec3
 *
 * @brief	Uniform std::vector 3. 
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

class UniformVec3
{
	/**
	 * @fn	virtual void UniformVec3::Set_Uniform_data(Vec3f* vec3)=0;
	 *
	 * @brief	Sets a uniform data.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param [in,out]	vec3	If non-null, the third std::vector.
	 */

	virtual void Set_Uniform_data(Vec3f* vec3)=0;
};

/**
 * @class	UniformUI
 *
 * @brief	Uniform unsigned int. 
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 */

class UniformUI
{

	virtual void Set_Uniform_data(unsigned int* ui)=0;
};

#endif