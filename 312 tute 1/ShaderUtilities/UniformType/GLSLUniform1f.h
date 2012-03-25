
#ifndef __UNIFORM1F_H__
#define __UNIFORM1F_H__

#include "GLSLUniformVariable.h"

/**
 * @class	GLSLUniform1f
 *
 * @brief	Uniform 1f.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

class GLSLUniform1f: public GLSLUniformVar, public Uniform1f
{
public:

	/**
	 * @fn	GLSLUniform1f::GLSLUniform1f(const unsigned int shader_ref,const std::string var_name,
	 * 		float* onef);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @param	shader_ref  	The shader reference.
	 * @param	var_name		Name of the variable.
	 * @param [in,out]	onef	The onef.
	 */

	GLSLUniform1f(const unsigned int shader_ref,const std::string var_name, float* onef);

	/**
	 * @fn	GLSLUniform1f::GLSLUniform1f(const std::string var_name, float* onef);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param	var_name		Name of the variable.
	 * @param [in,out]	onef	If non-null, the onef.
	 */

	GLSLUniform1f(const std::string var_name, float* onef);

	/**
	 * @fn	GLSLUniform1f::~GLSLUniform1f();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	~GLSLUniform1f();

	/**
	 * @fn	virtual void GLSLUniform1f::Set_Uniform_data(float* onef);
	 *
	 * @brief	Sets a uniform data.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param [in,out]	onef	If non-null, the onef.
	 */

	virtual void Set_Uniform_data(float* onef);

	/**
	 * @fn	virtual void GLSLUniform1f::Update();
	 *
	 * @brief	Updates this object.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	virtual void Update();
private:
	///< The onef
	float* m_onef;
};

#endif