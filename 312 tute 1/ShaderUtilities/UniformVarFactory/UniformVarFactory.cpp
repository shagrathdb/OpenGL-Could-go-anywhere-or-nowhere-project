
#include "UniformVarFactory.h"



///< The uniform variable factory instance
UniformVarFactory* UniformVarFactory::_instance = NULL;

/**
 * @fn	UniformVarFactory* UniformVarFactory::Instance()
 *
 * @brief	Gets the instance.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @return	null if it fails, else.
 */

UniformVarFactory* UniformVarFactory::Instance()
{
	if(_instance==NULL)
	{
		_instance = new UniformVarFactory;
	}
	return _instance;
}

/**
 * @fn	UniformVarFactory::~UniformVarFactory()
 *
 * @brief	Destructor.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

UniformVarFactory::~UniformVarFactory()
{
	_instance = NULL;
	delete [] _instance;
}

/**
 * @fn	UniformVar* UniformVarFactory::Create(const std::string var_name, float* uniform_var)const
 *
 * @brief	Creates this object.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @param	var_name		   	Name of the variable.
 * @param [in,out]	uniform_var	The uniform variable.
 *
 * @return	null if it fails, else.
 */

UniformVar* UniformVarFactory::Create(const std::string var_name,
									  float* uniform_var)const
{
	switch(ShaderMode::Instance()->Get_ShaderMode())
	{
	case GLSL:
		return new GLSLUniform1f(var_name,uniform_var);
	default:
		std::cout << "Shader Mode not set yet, or doesn't exist" << std::endl;
		return NULL;
	}
}

/**
 * @fn	UniformVar* UniformVarFactory::Create(const std::string var_name,
 * 		unsigned int* uniform_var)const
 *
 * @brief	Creates this object.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	var_name		   	Name of the variable.
 * @param [in,out]	uniform_var	If non-null, the uniform variable.
 *
 * @return	null if it fails, else.
 */

UniformVar* UniformVarFactory::Create(const std::string var_name,
									  unsigned int* uniform_var)const
{
	switch(ShaderMode::Instance()->Get_ShaderMode())
	{
	case GLSL:
		return new GLSLUniformUI(var_name,uniform_var);
	default:
		std::cout << "Shader Mode not set yet, or doesn't exist" << std::endl;
		return NULL;
	}
}

/**
 * @fn	UniformVar* UniformVarFactory::Create(const std::string var_name, Vec2f* uniform_var)const
 *
 * @brief	Creates this object.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @param	var_name		   	Name of the variable.
 * @param [in,out]	uniform_var	The uniform variable.
 *
 * @return	null if it fails, else.
 */

UniformVar* UniformVarFactory::Create(const std::string var_name,
									  Vector2<float>* uniform_var)const
{
	switch(ShaderMode::Instance()->Get_ShaderMode())
	{
	case GLSL:
		return new GLSLUniformVec2(var_name,uniform_var);
	default:
		std::cout << "Shader Mode not set yet, or doesn't exist" << std::endl;
		return NULL;
	}
}

/**
 * @fn	UniformVar* UniformVarFactory::Create(const std::string var_name, Vec3f* uniform_var)const
 *
 * @brief	Creates this object.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @param	var_name		   	Name of the variable.
 * @param [in,out]	uniform_var	The uniform variable.
 *
 * @return	null if it fails, else.
 */

UniformVar* UniformVarFactory::Create(const std::string var_name,
									  Vec3f* uniform_var)const
{
	switch(ShaderMode::Instance()->Get_ShaderMode())
	{
	case GLSL:
		return new GLSLUniformVec3(var_name,uniform_var);
	default:
		std::cout << "Shader Mode not set yet, or doesn't exist" << std::endl;
		return NULL;
	}
}