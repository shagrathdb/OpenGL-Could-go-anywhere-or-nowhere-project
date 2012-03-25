
#include "GLSLUniformVec2.h"

/**
 * @fn	GLSLUniformVec2::GLSLUniformVec2(const unsigned int shader_ref,
 * 		const std::string var_name,Vec2f* vec)
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

GLSLUniformVec2::GLSLUniformVec2(const unsigned int shader_ref,
								 const std::string var_name,Vector2<float>* vec)
{
	m_var_name = var_name;
	m_vec2 = vec;
	m_shader_ref = shader_ref;
}

/**
 * @fn	GLSLUniformVec2::GLSLUniformVec2(const std::string var_name,Vec2f* vec)
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param	var_name   	Name of the variable.
 * @param [in,out]	vec	If non-null, the std::vector.
 */

GLSLUniformVec2::GLSLUniformVec2(const std::string var_name,Vector2<float>* vec)
{
	m_var_name = var_name;
	m_vec2 = vec;
}

/**
 * @fn	GLSLUniformVec2::~GLSLUniformVec2()
 *
 * @brief	Destructor.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

GLSLUniformVec2::~GLSLUniformVec2()
{
	m_vec2 = NULL;
	delete [] m_vec2;
}

/**
 * @fn	void GLSLUniformVec2::Set_Uniform_data(Vec2f* vec2)
 *
 * @brief	Sets a uniform data.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param [in,out]	vec2	If non-null, the second std::vector.
 */

void GLSLUniformVec2::Set_Uniform_data(Vector2<float>* vec2)
{
	m_vec2 = vec2;
}

/**
 * @fn	void GLSLUniformVec2::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

void GLSLUniformVec2::Update()
{
	glUniform2f(Get_Uniform_loc(m_shader_ref),m_vec2->x,m_vec2->y);
}