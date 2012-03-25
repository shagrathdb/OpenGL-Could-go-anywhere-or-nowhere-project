

#ifndef __SHADERMANAGER_H__
#define __SHADERMANAGER_H__
#include "../ShaderType/ShaderAPI.h"
#include <map>
#include <string>

/**
 * @class	ShaderManager
 *
 * @brief	Manager for glsl.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

class ShaderManager
{
public:

	/**
	 * @fn	static ShaderManager* ShaderManager::Instance();
	 *
	 * @brief	Gets the instance.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @return	null if it fails, else.
	 */

	static ShaderManager* Instance();

	/**
	 * @fn	ShaderManager::~ShaderManager();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	~ShaderManager();

	/**
	 * @fn	void ShaderManager::Add_Shader_program(std::string name,ShaderProgram* prog);
	 *
	 * @brief	Adds a glsl program.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @param	name			The name.
	 * @param [in,out]	prog	The prog.
	 */

	void Add_Shader_program(std::string name,ShaderProgram* prog);

	/**
	 * @fn	void ShaderManager::Set_Shader_uni_var(std::string name, UniformVar* uni_var);
	 *
	 * @brief	Sets a shader uni variable.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param	name		   	The index.
	 * @param [in,out]	uni_var	If non-null, the uni variable.
	 */

	void Set_Shader_uni_var(std::string name, UniformVar* uni_var);

	/**
	 * @fn	unsigned int ShaderManager::Get_shader_ref( std::string name);
	 *
	 * @brief	Gets a shader reference.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @param	name	Zero-based index of the.
	 *
	 * @return	The shader reference.
	 */

	unsigned int Get_shader_ref( std::string name);

	/**
	 * @fn	void ShaderManager::Enable_shader(std::string name);
	 *
	 * @brief	Enables the shader.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	name	The name.
	 */

	void Enable_shader(std::string name);

	/**
	 * @fn	void ShaderManager::Disable_shader(std::string name);
	 *
	 * @brief	Disables the shader.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	name	The name.
	 */

	void Disable_shader(std::string name);

private:
	///< The instance
	static ShaderManager* _instance;
	///< The glsl programs
	std::map<std::string,ShaderProgram*> m_Shader_programs; 

	/**
	 * @fn	ShaderManager::ShaderManager()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	ShaderManager(){}
};


#endif