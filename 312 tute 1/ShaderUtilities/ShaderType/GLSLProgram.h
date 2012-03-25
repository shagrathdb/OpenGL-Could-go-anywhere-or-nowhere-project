

#ifndef __GLSLPROGRAM_H__
#define __GLSLPROGRAM_H__

#include <GL\glew.h>
#include <iostream>
#include <exception>

#include "ShaderAPI.h"

/**
 * @class	GLSLProgram
 *
 * @brief	Glsl program.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

class GLSLProgram : public ShaderProgram
{
public:

	/**
	 * @fn	GLSLProgram::GLSLProgram(const char* vert_shader, const char* frag_shader);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @param	vert_shader	The vertical shader.
	 * @param	frag_shader	The fragment shader.
	 */

	GLSLProgram(const char* vert_shader, const char* frag_shader);

	/**
	 * @fn	GLSLProgram::~GLSLProgram();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	~GLSLProgram();

	/**
	 * @fn	virtual void GLSLProgram::Bind();
	 *
	 * @brief	Binds this object.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	virtual void Bind();

	/**
	 * @fn	virtual void GLSLProgram::Unbind();
	 *
	 * @brief	Unbinds this object.
	 *
	 * @author	Noel Waghorn
	 * @date	3/09/2011
	 */

	virtual void Unbind();

	/**
	 * @fn	virtual unsigned int GLSLProgram::Get_Shader_ref()const;
	 *
	 * @brief	Gets the shader reference.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @return	The shader reference.
	 */

	virtual unsigned int Get_Shader_ref()const;

	/**
	 * @fn	virtual void GLSLProgram::Add_Uniform_var(UniformVar* uni_var);
	 *
	 * @brief	Adds a uniform variable.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param [in,out]	uni_var	If non-null, the uni variable.
	 */

	virtual void Add_Uniform_var(UniformVar* uni_var);

	/**
	 * @fn	virtual void GLSLProgram::Update_Uniform_vars();
	 *
	 * @brief	Updates the uniform variables.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	virtual void Update_Uniform_vars();

	/**
	 * @fn	virtual void GLSLProgram::operator=(ShaderProgram* program)
	 *
	 * @brief	Assignment operator.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param [in,out]	program	If non-null, the program.
	 */

	virtual void operator=(ShaderProgram* program)
	{
		*this = program;
	}

private:
	///< Information describing the shader
	Shader_info* m_shader_info;
	///< true to enable, false to disable
	bool m_Enabled;

	/**
	 * @fn	GLSLProgram::GLSLProgram()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	GLSLProgram()
		:m_shader_info(NULL),m_Enabled(false)
	{
		m_shader_info = new Shader_info;
	}

	/**
	 * @fn	virtual std::string GLSLProgram::Get_log(const unsigned int handle) const;
	 *
	 * @brief	Gets a shader log.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @param	handle	The handle.
	 *
	 * @return	The shader log.
	 */

	virtual std::string	Get_log(const unsigned int handle) const;

	/**
	 * @fn	virtual bool GLSLProgram::Load_shader(const char* shader_src,
	 * 		const unsigned int shader_type)const;
	 *
	 * @brief	Loads a shader.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @param	shader_src 	The shader source.
	 * @param	shader_type	Type of the shader.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	virtual bool Load_shader(const char* shader_src, 
						     const unsigned int shader_type)const;

	/**
	 * @fn	virtual void GLSLProgram::Link();
	 *
	 * @brief	Links this object.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	virtual void Link();
};

/**
 * @class	GlslProgCompileExc
 *
 * @brief	Glsl prog compile exc. 
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

class GlslProgCompileExc : public std::exception 
{
 public:	

	/**
	 * @fn	:::GlslProgCompileExc(const std::string &log, const int aShaderType ) throw();
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @param	log		   	The log.
	 * @param	aShaderType	Type of a shader.
	 */

	GlslProgCompileExc(const std::string &log, const int aShaderType ) throw();

	/**
	 * @fn	virtual const char* :::what() const throw()
	 *
	 * @brief	Gets the what.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @return	null if it fails, else.
	 */

	virtual const char* what() const throw()
	{
		return m_message.c_str();
	}

 private:
	///< The message
	std::string m_message;
	///< Type of the shader
	int	mShaderType;
};

/**
 * @class	GlslNullProgramExc
 *
 * @brief	Glsl null program exc. 
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

class GlslNullProgramExc : public std::exception 
{
 public:	

	/**
	 * @fn	virtual const char* :::what() const throw()
	 *
	 * @brief	Gets the what.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @return	null if it fails, else.
	 */

	virtual const char* what() const throw()
	{
		return "Glsl: Attempt to use null shader";
	}

};
#endif