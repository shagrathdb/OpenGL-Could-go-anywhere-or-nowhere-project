
#ifndef __SHADERMODE_H__
#define __SHADERMODE_H__

/**
 * @enum	ShaderType
 *
 * @brief	Values that represent EWType.
 */

static enum ShaderType
{
	///< GLSL Shader Type 
	GLSL,
	///< No shader
	NONE
};

/**
 * @class	ShaderMode
 *
 * @brief	Ew mode.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

class ShaderMode
{
public:

	/**
	 * @fn	static ShaderMode* ShaderMode::Instance();
	 *
	 * @brief	Gets the instance.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @return	null if it fails, else.
	 */

	static ShaderMode* Instance();

	/**
	 * @fn	ShaderMode::~ShaderMode();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	~ShaderMode();

	/**
	 * @fn	bool ShaderMode::Set_ShaderMode(const ShaderType type);
	 *
	 * @brief	Sets a shader mode.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	type	The type.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	bool Set_ShaderMode(const ShaderType type);

	/**
	 * @fn	ShaderType ShaderMode::Get_ShaderMode()const;
	 *
	 * @brief	Gets the shader mode.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @return	The shader mode.
	 */

	ShaderType Get_ShaderMode()const;
private:
	///< The instance
	static ShaderMode* _instance;
	///< Type of the shader
	ShaderType shader_type;

	/**
	 * @fn	ShaderMode::ShaderMode()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	ShaderMode(){}

};

#endif