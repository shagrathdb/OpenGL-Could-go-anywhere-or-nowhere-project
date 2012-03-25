
#include "ShaderMode.h"

#include <iostream>

///< The shader mode instance
ShaderMode* ShaderMode::_instance = NULL;

/**
 * @fn	ShaderMode* ShaderMode::Instance()
 *
 * @brief	Gets the instance.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @return	null if it fails, else.
 */

ShaderMode* ShaderMode::Instance()
{
	if(_instance==NULL)
	{
		_instance = new ShaderMode;
	}
	return _instance;
}

/**
 * @fn	ShaderMode::~ShaderMode()
 *
 * @brief	Destructor.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

ShaderMode::~ShaderMode()
{
	_instance = NULL;
	delete [] _instance;
}

/**
 * @fn	bool ShaderMode::Set_ShaderMode(const ShaderType type)
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

bool ShaderMode::Set_ShaderMode(const ShaderType type)
{
	shader_type = type;

	return true;
}

/**
 * @fn	ShaderType ShaderMode::Get_ShaderMode()const
 *
 * @brief	Gets the shader mode.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @return	The shader mode.
 */

ShaderType ShaderMode::Get_ShaderMode()const
{
	return shader_type;
}