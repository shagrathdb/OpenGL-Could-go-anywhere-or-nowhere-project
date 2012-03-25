

#ifndef __UNIFORMVAR_H__
#define __UNIFORMVAR_H__
#include <string>

#include <GL\glew.h>

#include "UniformVariableAPI.h"

/**
 * @class	GLSLUniformVar
 *
 * @brief	Uniform variable.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

class GLSLUniformVar : public UniformVar
{
public:

	/**
	 * @fn	virtual void GLSLUniformVar::Update() = 0;
	 *
	 * @brief	Updates this object.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	virtual void Update() = 0;

	/**
	 * @fn	virtual int GLSLUniformVar::Get_Uniform_loc(const unsigned int program);
	 *
	 * @brief	Gets a uni location.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @param	program	The program.
	 *
	 * @return	The uni location.
	 */

	virtual int Get_Uniform_loc(const unsigned int program);

	/**
	 * @fn	virtual void GLSLUniformVar::Set_Uniform_ref(const unsigned int uni_ref);
	 *
	 * @brief	Sets a uniform reference.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param	uni_ref	The uni reference.
	 */

	virtual void Set_Uniform_ref(const unsigned int uni_ref);
protected:
	///< The shader reference
	unsigned int m_shader_ref;
	///< Name of the variable
	std::string m_var_name;
};

#endif