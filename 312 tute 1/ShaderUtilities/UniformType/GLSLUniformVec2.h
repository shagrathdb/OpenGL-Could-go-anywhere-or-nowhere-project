
#ifndef __UNIFORMVEC2_H__
#define __UNIFORMVEC2_H__

#include "GLSLUniformVariable.h"

/**
 * @class	GLSLUniformVec2
 *
 * @brief	Uniform std::vector 2.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

class GLSLUniformVec2: public GLSLUniformVar, public UniformVec2
{
public:

	/**
	 * @fn	GLSLUniformVec2::GLSLUniformVec2(const unsigned int shader_ref,
	 * 		const std::string var_name,Vec2f* vec);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 *
	 * @param	shader_ref 	The shader reference.
	 * @param	var_name   	Name of the variable.
	 * @param [in,out]	vec	The std::vector.
	 */

	GLSLUniformVec2(const unsigned int shader_ref,
					const std::string var_name,Vector2<float>* vec);

	/**
	 * @fn	GLSLUniformVec2::GLSLUniformVec2(const std::string var_name,Vec2f* vec);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param	var_name   	Name of the variable.
	 * @param [in,out]	vec	If non-null, the std::vector.
	 */

	GLSLUniformVec2(const std::string var_name,Vector2<float>* vec);

	/**
	 * @fn	GLSLUniformVec2::~GLSLUniformVec2();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 */

	~GLSLUniformVec2();

	/**
	 * @fn	virtual void GLSLUniformVec2::Set_Uniform_data(Vec2f* vec2);
	 *
	 * @brief	Sets a uniform data.
	 *
	 * @author	Noel Waghorn
	 * @date	5/09/2011
	 *
	 * @param [in,out]	vec2	If non-null, the second std::vector.
	 */

	virtual void Set_Uniform_data(Vector2<float>* vec2);

	/**
	 * @fn	virtual void GLSLUniformVec2::Update();
	 *
	 * @brief	Updates this object.
	 *
	 * @author	Noel Waghorn
	 * @date	2/09/2011
	 */

	virtual void Update();
private:
	///< The second m std::vector
	Vector2<float>* m_vec2;
};

#endif