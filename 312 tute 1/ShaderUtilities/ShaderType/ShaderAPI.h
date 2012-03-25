
#ifndef __SHADERAPI_H__
#define __SHADERAPI_H__

#include <iostream>
#include <vector>

#include "../UniformType/UniformVariableAPI.h"

/**
 * @struct	Shader_info
 *
 * @brief	Information about the shader.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

struct Shader_info
{
	/**
	 * @fn	Shader_info()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	9/1/2011
	 */

	Shader_info(){Clear();}

	/**
	 * @fn	void Clear()
	 *
	 * @brief	Clears this object to its blank/initial state.
	 *
	 * @author	Noel Waghorn
	 * @date	9/1/2011
	 */

	void Clear()
	{
		ID = 0;
		Compiled = false;
	}

	/**
	 * @fn	~Shader_info()
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	9/1/2011
	 */

	~Shader_info(){Clear();}

	///< The identifier
	unsigned int ID;
	///< true to compiled
	bool Compiled;
};

/**
 * @class	ShaderProgram
 *
 * @brief	Shader program.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

class ShaderProgram
{
	public:

	/**
	 * @fn	virtual void ShaderProgram::Bind()=0;
	 *
	 * @brief	Binds this object.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	virtual void Bind()=0;

	/**
	 * @fn	virtual void ShaderProgram::Unbind()=0;
	 *
	 * @brief	Unbinds this object.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	virtual void Unbind()=0;

	/**
	 * @fn	virtual unsigned int ShaderProgram::Get_Shader_ref()const=0;
	 *
	 * @brief	Gets the shader reference.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @return	The shader reference.
	 */

	virtual unsigned int Get_Shader_ref()const=0;

	/**
	 * @fn	virtual void ShaderProgram::Add_Uniform_var(UniformVar* uni_var)=0;
	 *
	 * @brief	Adds a uniform variable. 
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param [in,out]	uni_var	If non-null, the uni variable.
	 */

	virtual void Add_Uniform_var(UniformVar* uni_var)=0;

	/**
	 * @fn	virtual void ShaderProgram::Update_Uniform_vars()=0;
	 *
	 * @brief	Updates the uniform variables.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	virtual void Update_Uniform_vars()=0;

	/**
	 * @fn	virtual void ShaderProgram::operator=(ShaderProgram* program)=0;
	 *
	 * @brief	Assignment operator.
	 *
	 * @author	Noel Waghorn
	 * @date	19/09/2011
	 *
	 * @param [in,out]	program	If non-null, the program.
	 */

	virtual void operator=(ShaderProgram* program)=0;

protected:

	///< The uniform variables
	std::vector<UniformVar*> m_uniform_vars;


	/**
	 * @fn	virtual std::string ShaderProgram::Get_log(const unsigned int handle)const=0;
	 *
	 * @brief	Gets a log.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param	handle	The handle.
	 *
	 * @return	The log.
	 */

	virtual std::string	Get_log(const unsigned int handle)const=0;

	/**
	 * @fn	virtual bool ShaderProgram::Load_shader(const char* shader_src,
	 * 		const unsigned int shader_type)const=0;
	 *
	 * @brief	Loads a shader.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param	shader_src 	The shader source.
	 * @param	shader_type	Type of the shader.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	virtual bool Load_shader(const char* shader_src, const unsigned int shader_type)const=0;

	/**
	 * @fn	virtual void ShaderProgram::Link()=0;
	 *
	 * @brief	Links this object.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	virtual void Link()=0;

};

#endif