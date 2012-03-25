
#ifndef __UNIFORMVEC3_H__
#define __UNIFORMVEC3_H__

#include "GLSLUniformVariable.h"

/**
 * @class	GLSLUniformVec3
 *
 * @brief	Uniform std::vector 3.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

class GLSLUniformVec3: public GLSLUniformVar, public UniformVec3
{
public:

	/**
	 * @fn	GLSLUniformVec3::GLSLUniformVec3(const unsigned int shader_ref,
	 * 		const std::string var_name,Vec3f* vec);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @param	shader_ref 	The shader reference.
	 * @param	var_name   	Name of the variable.
	 * @param [in,out]	vec	The std::vector.
	 */

	GLSLUniformVec3(const unsigned int shader_ref,
					const std::string var_name,Vec3f* vec);

	/**
	 * @fn	GLSLUniformVec3::GLSLUniformVec3(const std::string var_name,Vec3f* vec);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param	var_name   	Name of the variable.
	 * @param [in,out]	vec	If non-null, the std::vector.
	 */

	GLSLUniformVec3(const std::string var_name,Vec3f* vec);

	/**
	 * @fn	GLSLUniformVec3::~GLSLUniformVec3();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	~GLSLUniformVec3();

	/**
	 * @fn	virtual void GLSLUniformVec3::Set_Uniform_data(Vec3f* vec3);
	 *
	 * @brief	Sets a uniform data.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param [in,out]	vec3	If non-null, the third std::vector.
	 */

	virtual void Set_Uniform_data(Vec3f* vec3);

	/**
	 * @fn	virtual void GLSLUniformVec3::Update();
	 *
	 * @brief	Updates this object.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	virtual void Update();
private:
	///< The third m std::vector
	Vec3f* m_vec3;
};

#endif