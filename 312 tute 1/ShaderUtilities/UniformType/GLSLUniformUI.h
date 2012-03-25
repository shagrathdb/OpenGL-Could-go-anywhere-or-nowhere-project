

#ifndef __UNIFORMUI_H__
#define __UNIFORMUI_H__

#include "GLSLUniformVariable.h"

/**
 * @class	GLSLUniformUI
 *
 * @brief	Glsl uniform unsigned int. 
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 */

class GLSLUniformUI: public GLSLUniformVar, public UniformUI
{
public:

	/**
	 * @fn	GLSLUniformUI::GLSLUniformUI(const unsigned int shader_ref, const std::string var_name,
	 * 		unsigned int* ui);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	shader_ref	The shader reference.
	 * @param	var_name  	Name of the variable.
	 * @param [in,out]	ui	If non-null, the unsigned int.
	 */

	GLSLUniformUI(const unsigned int shader_ref,
					const std::string var_name,unsigned int* ui);

	/**
	 * @fn	GLSLUniformUI::GLSLUniformUI(const std::string var_name,unsigned int* ui);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	var_name  	Name of the variable.
	 * @param [in,out]	ui	If non-null, the unsigned int.
	 */

	GLSLUniformUI(const std::string var_name,unsigned int* ui);

	/**
	 * @fn	GLSLUniformUI::~GLSLUniformUI();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 */

	~GLSLUniformUI();

	/**
	 * @fn	virtual void GLSLUniformUI::Set_Uniform_data(unsigned int* ui);
	 *
	 * @brief	Sets a uniform data.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param [in,out]	ui	If non-null, the unsigned int.
	 */

	virtual void Set_Uniform_data(unsigned int* ui);

	/**
	 * @fn	virtual void GLSLUniformUI::Update();
	 *
	 * @brief	Updates this object.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 */

	virtual void Update();
private:
	///< The unsigned integer
	unsigned int* m_ui;
};

#endif