

#include "GLSLUniformUI.h"

/**
 * @fn	GLSLUniformUI::GLSLUniformUI(const unsigned int shader_ref, const std::string var_name,
 * 		unsigned int* ui)
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	shader_ref	The shader reference.
 * @param	var_name  	Name of the variable.
 * @param [in,out]	ui	If non-null, the user interface.
 */

GLSLUniformUI::GLSLUniformUI(const unsigned int shader_ref,
					const std::string var_name,unsigned int* ui)
{
	m_var_name = var_name;
	m_ui = ui;
	m_shader_ref = shader_ref;
}

/**
 * @fn	GLSLUniformUI::GLSLUniformUI(const std::string var_name,unsigned int* ui)
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	var_name  	Name of the variable.
 * @param [in,out]	ui	If non-null, the user interface.
 */

GLSLUniformUI::GLSLUniformUI(const std::string var_name,unsigned int* ui)
{
	m_var_name = var_name;
	m_ui = ui;
}

/**
 * @fn	GLSLUniformUI::~GLSLUniformUI()
 *
 * @brief	Destructor.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 */

GLSLUniformUI::~GLSLUniformUI()
{
	m_ui = NULL;
	delete [] m_ui;
}

/**
 * @fn	void GLSLUniformUI::Set_Uniform_data(unsigned int* ui)
 *
 * @brief	Sets a uniform data.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param [in,out]	ui	If non-null, the user interface.
 */

void GLSLUniformUI::Set_Uniform_data(unsigned int* ui)
{
	m_ui = ui;
}

/**
 * @fn	void GLSLUniformUI::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 */

void GLSLUniformUI::Update()
{
	glUniform1ui(Get_Uniform_loc(m_shader_ref),*m_ui);
}