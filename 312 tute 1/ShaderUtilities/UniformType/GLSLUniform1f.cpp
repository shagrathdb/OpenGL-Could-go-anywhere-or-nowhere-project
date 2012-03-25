
#include "GLSLUniform1f.h"

/**
 * @fn	GLSLUniform1f::GLSLUniform1f(const unsigned int shader_ref,const std::string var_name,
 * 		float* onef)
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

GLSLUniform1f::GLSLUniform1f(const unsigned int shader_ref,const std::string var_name, float* onef)
{
	m_var_name = var_name;
	m_onef = onef;
	m_shader_ref = shader_ref;
}

/**
 * @fn	GLSLUniform1f::GLSLUniform1f(const std::string var_name, float* onef)
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param	var_name		Name of the variable.
 * @param [in,out]	onef	If non-null, the onef.
 */

GLSLUniform1f::GLSLUniform1f(const std::string var_name, float* onef)
{
	m_var_name = var_name;
	m_onef = onef;
}

/**
 * @fn	GLSLUniform1f::~GLSLUniform1f()
 *
 * @brief	Destructor.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

GLSLUniform1f::~GLSLUniform1f()
{
	m_onef = NULL;
	delete [] m_onef;
}

/**
 * @fn	void GLSLUniform1f::Set_Uniform_data(float* onef)
 *
 * @brief	Sets a uniform data.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param [in,out]	onef	If non-null, the onef.
 */

void GLSLUniform1f::Set_Uniform_data(float* onef)
{
	m_onef = onef;
}

/**
 * @fn	void GLSLUniform1f::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

void GLSLUniform1f::Update()
{
	glUniform1f(Get_Uniform_loc(m_shader_ref),*m_onef);
}