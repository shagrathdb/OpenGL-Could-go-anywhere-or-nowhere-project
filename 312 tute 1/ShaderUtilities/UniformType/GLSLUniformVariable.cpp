

#include "GLSLUniformVariable.h"

/**
 * @fn	int GLSLUniformVar::Get_Uniform_loc(const unsigned int program)
 *
 * @brief	Gets a uni location.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @param	program	The program.
 *
 * @return	The uni location.
 */

int GLSLUniformVar::Get_Uniform_loc(const unsigned int program)
{
    int loc;

    loc = glGetUniformLocation(program, m_var_name.c_str());

    if (loc == -1)
	{
        printf("No such uniform named \"%s\"\n", m_var_name);
	}
    //printOpenGLError();  // Check for OpenGL errors
    return loc;
}

/**
 * @fn	void GLSLUniformVar::Set_Uniform_ref(const unsigned int uni_ref)
 *
 * @brief	Sets a uniform reference.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param	uni_ref	The uni reference.
 */

void GLSLUniformVar::Set_Uniform_ref(const unsigned int uni_ref)
{
	m_shader_ref = uni_ref;
}