

#include "GLSLUniformVec3.h"

/**
 * @fn	GLSLUniformVec3::GLSLUniformVec3(const unsigned int shader_ref,
 * 		const std::string var_name,Vec3f* vec)
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

GLSLUniformVec3::GLSLUniformVec3(const unsigned int shader_ref,
								 const std::string var_name,Vec3f* vec)
{
	m_var_name = var_name;
	m_vec3 = vec;
	m_shader_ref = shader_ref;	
}

/**
 * @fn	GLSLUniformVec3::GLSLUniformVec3(const std::string var_name,Vec3f* vec)
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param	var_name   	Name of the variable.
 * @param [in,out]	vec	If non-null, the std::vector.
 */

GLSLUniformVec3::GLSLUniformVec3(const std::string var_name,Vec3f* vec)
{
	m_var_name = var_name;
	m_vec3 = vec;	
}

/**
 * @fn	GLSLUniformVec3::~GLSLUniformVec3()
 *
 * @brief	Destructor.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

GLSLUniformVec3::~GLSLUniformVec3()
{
	m_vec3 = NULL;
	delete [] m_vec3;
}

/**
 * @fn	void GLSLUniformVec3::Set_Uniform_data(Vec3f* vec3)
 *
 * @brief	Sets a uniform data.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param [in,out]	vec3	If non-null, the third std::vector.
 */

void GLSLUniformVec3::Set_Uniform_data(Vec3f* vec3)
{
	m_vec3 = vec3;
}

/**
 * @fn	void GLSLUniformVec3::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

void GLSLUniformVec3::Update()
{
	glUniform3f(Get_Uniform_loc(m_shader_ref),m_vec3->x,m_vec3->y,m_vec3->z);
}