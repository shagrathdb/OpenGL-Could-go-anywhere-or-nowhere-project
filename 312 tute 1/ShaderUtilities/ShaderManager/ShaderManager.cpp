

#include "ShaderManager.h"

///< The glsl manager instance
ShaderManager* ShaderManager::_instance = NULL;

/**
 * @fn	ShaderManager* ShaderManager::Instance()
 *
 * @brief	Gets the instance.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @return	null if it fails, else.
 */

ShaderManager* ShaderManager::Instance()
{
	if(_instance==NULL)
	{
		_instance = new ShaderManager;
	}
	return _instance;
}

/**
 * @fn	ShaderManager::~ShaderManager()
 *
 * @brief	Destructor.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

ShaderManager::~ShaderManager()
{
	_instance = NULL;
	delete [] _instance;
}

/**
 * @fn	void ShaderManager::Add_Shader_program(std::string name, ShaderProgram* prog)
 *
 * @brief	Adds a glsl program.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @param	name			The name.
 * @param [in,out]	prog	The prog.
 */

void ShaderManager::Add_Shader_program(std::string name,
									   ShaderProgram* prog)
{
	m_Shader_programs[name] = prog;
}

/**
 * @fn	unsigned int ShaderManager::Get_shader_ref( std::string name)
 *
 * @brief	Gets a shader reference.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param	name	Zero-based index of the.
 *
 * @return	The shader reference.
 */

unsigned int ShaderManager::Get_shader_ref( std::string name)
{
	if(m_Shader_programs[name]!=NULL)
	{
		return m_Shader_programs[name]->Get_Shader_ref();
	}
	return NULL;
}

/**
 * @fn	void ShaderManager::Set_Shader_uni_var(std::string name, UniformVar* uni_var)
 *
 * @brief	Sets a shader uni variable.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param	name		   	The index.
 * @param [in,out]	uni_var	If non-null, the uni variable.
 */

void ShaderManager::Set_Shader_uni_var(std::string name, 
									   UniformVar* uni_var)
{
	if(m_Shader_programs[name]!=NULL)
	{
		uni_var->Set_Uniform_ref(m_Shader_programs[name]->Get_Shader_ref());
		m_Shader_programs[name]->Add_Uniform_var(uni_var);
	}
}

/**
 * @fn	void ShaderManager::Enable_shader(std::string name)
 *
 * @brief	Enables the shader.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	name	The name.
 */

void ShaderManager::Enable_shader(std::string name)
{
	if(m_Shader_programs[name]!=NULL)
	{
		m_Shader_programs[name]->Bind();
		m_Shader_programs[name]->Update_Uniform_vars();
	}
}

/**
 * @fn	void ShaderManager::Disable_shader(std::string name)
 *
 * @brief	Disables the shader.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	name	The name.
 */

void ShaderManager::Disable_shader(std::string name)
{
	if(m_Shader_programs[name]!=NULL)
	{
		m_Shader_programs[name]->Unbind();
	}
}