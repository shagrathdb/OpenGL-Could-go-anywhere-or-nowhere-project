
#include "ShaderFactory.h"
#include "../ShaderMode.h"
#include "../ShaderType/GLSLProgram.h"
#include <iostream>

ShaderFactory* ShaderFactory::_instance = NULL;

/**
 * @fn	ShaderFactory* ShaderFactory::Instance()
 *
 * @brief	Gets the instance.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @return	null if it fails, else.
 */

ShaderFactory* ShaderFactory::Instance()
{
	if(_instance==NULL)
	{
		_instance = new ShaderFactory;
	}
	return _instance;
}

/**
 * @fn	ShaderFactory::~ShaderFactory()
 *
 * @brief	Destructor.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 */

ShaderFactory::~ShaderFactory()
{
	_instance = NULL;
	delete [] _instance;
}

/**
 * @fn	ShaderProgram* ShaderFactory::Create(const char* vert_shader, const char* frag_shader)
 *
 * @brief	Creates this object.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param	vert_shader	The vertical shader.
 * @param	frag_shader	The fragment shader.
 *
 * @return	null if it fails, else.
 */

ShaderProgram* ShaderFactory::Create(const char* vert_shader, const char* frag_shader)
{
	switch(ShaderMode::Instance()->Get_ShaderMode())
	{
	case GLSL:
		return new GLSLProgram(vert_shader,frag_shader);
	default:
		std::cout << "Shader Mode not set yet, or doesn't exist" << std::endl;
		return NULL;
	}
}