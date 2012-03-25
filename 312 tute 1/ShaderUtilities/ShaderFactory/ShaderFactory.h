
#ifndef __SHADERFACTORY_H__
#define __SHADERFACTORY_H__

#include "../ShaderType/ShaderAPI.h"

/**
 * @class	ShaderFactory
 *
 * @brief	Shader factory. 
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

class ShaderFactory
{
public:

	/**
	 * @fn	static ShaderFactory* ShaderFactory::Instance();
	 *
	 * @brief	Gets the instance.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @return	null if it fails, else.
	 */

	static ShaderFactory* Instance();

	/**
	 * @fn	ShaderFactory::~ShaderFactory();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	~ShaderFactory();

	/**
	 * @fn	ShaderProgram* ShaderFactory::Create(const char* vert_shader, const char* frag_shader);
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

	ShaderProgram* Create(const char* vert_shader, const char* frag_shader);

private:
	///< The instance
	static ShaderFactory* _instance;

	/**
	 * @fn	ShaderFactory::ShaderFactory()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	ShaderFactory(){}
};

#endif