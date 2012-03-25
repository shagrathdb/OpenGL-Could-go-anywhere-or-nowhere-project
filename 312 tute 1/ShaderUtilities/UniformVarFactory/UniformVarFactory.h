

#ifndef __UNIFORMVARFACTORY_H__
#define __UNIFORMVARFACTORY_H__

#include <iostream>
#include "../UniformType/UniformVariableAPI.h"
#include "../UniformType/GLSLUniformUI.h"
#include "../UniformType/GLSLUniform1f.h"
#include "../UniformType/GLSLUniformVec2.h"
#include "../UniformType/GLSLUniformVec3.h"
#include "../ShaderMode.h"

/**
 * @class	UniformVarFactory
 *
 * @brief	Uniform variable factory.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

class UniformVarFactory
{
public:

	/**
	 * @fn	static UniformVarFactory* UniformVarFactory::Instance();
	 *
	 * @brief	Gets the instance.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @return	null if it fails, else.
	 */

	static UniformVarFactory* Instance();

	/**
	 * @fn	UniformVarFactory::~UniformVarFactory();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	~UniformVarFactory();

	/**
	 * @fn	UniformVar* UniformVarFactory::Create(const std::string var_name,
	 * 		float* uniform_var)const;
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

	UniformVar* Create(const std::string var_name,
					   float* uniform_var)const;

	/**
	 * @fn	UniformVar* UniformVarFactory::Create(const std::string var_name,
	 * 		unsigned int* uniform_var)const;
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

	UniformVar* Create(const std::string var_name,
					   unsigned int* uniform_var)const;

	/**
	 * @fn	UniformVar* UniformVarFactory::Create(const std::string var_name,
	 * 		Vec2f* uniform_var)const;
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

	UniformVar* Create(const std::string var_name,
					   Vector2<float>* uniform_var)const;

	/**
	 * @fn	UniformVar* UniformVarFactory::Create(const std::string var_name,
	 * 		Vec3f* uniform_var)const;
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

	UniformVar* Create(const std::string var_name,
					   Vec3f* uniform_var)const;
private:
	///< The instance
	static UniformVarFactory* _instance;

	/**
	 * @fn	UniformVarFactory::UniformVarFactory()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	UniformVarFactory(){}
};

#endif