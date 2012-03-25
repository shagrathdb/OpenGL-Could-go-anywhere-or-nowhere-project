
#include "GLSLProgram.h"

#include <fstream>
#include <string>

/**
 * @fn	GLSLProgram::GLSLProgram(const char* vert_shader, const char* frag_shader)
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @param	vert_shader	The vertical shader.
 * @param	frag_shader	The fragment shader.
 */

GLSLProgram::GLSLProgram(const char* vert_shader, 
						 const char* frag_shader)
{	
	bool vert_compiled = true;
	bool frag_compiled = false;

	*this = GLSLProgram();
	m_shader_info->ID = glCreateProgram();

	if(vert_shader)
	{
		vert_compiled = Load_shader(vert_shader,GL_VERTEX_SHADER_ARB);
	}

	if(frag_shader)
	{
		frag_compiled = Load_shader(frag_shader,GL_FRAGMENT_SHADER_ARB);
	}

	if(vert_compiled&&frag_compiled)
	{
		m_shader_info->Compiled = true;
		Link();
	}	

	Bind();
}

/**
 * @fn	GlslProgCompileExc::GlslProgCompileExc(const std::string &log, int shader_type) throw()
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @param	log		   	The log.
 * @param	shader_type	Type of a shader.
 */

GlslProgCompileExc::GlslProgCompileExc(const std::string &log, 
									   int shader_type) throw()
	: mShaderType(shader_type)
{
	if(mShaderType == GL_VERTEX_SHADER_ARB)
	{
		m_message = "VERTEX: ";
	}
	else if(mShaderType == GL_FRAGMENT_SHADER_ARB)
	{
		m_message = "FRAGMENT: ";
	}
	else
	{
		m_message = "UNKNOWN: ";
	}
	m_message = log;

	std::cout << m_message.c_str() << std::endl;
}

/**
 * @fn	std::string GLSLProgram::Get_log(unsigned int shader_ref) const
 *
 * @brief	Gets a shader log.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @param	shader_ref	The handle.
 *
 * @return	The shader log.
 */

std::string GLSLProgram::Get_log(unsigned int shader_ref) const
{
	std::string log;
	
	char *debug_log;
	int debug_length = 0, chars_written = 0;
	glGetShaderiv(shader_ref, GL_INFO_LOG_LENGTH, &debug_length );

	if( debug_length > 0 ) 
	{
		debug_log = new char[debug_length];
		glGetShaderInfoLog(shader_ref, debug_length, &chars_written, debug_log );
		log.append(debug_log,0,debug_length);
		delete [] debug_log;
	}
	
	return log;
}

/**
 * @fn	unsigned int GLSLProgram::Get_Shader_ref()const
 *
 * @brief	Gets the shader reference.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @return	The shader reference.
 */

unsigned int GLSLProgram::Get_Shader_ref()const
{
	return m_shader_info->ID;
}

/**
 * @fn	void Read_Shader_src(const std::string file_name, std::string* shader_src)
 *
 * @brief	Reads a shader.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @param	file_name		  	Filename of the file.
 * @param [in,out]	shader_src	If non-null, the shader text.
 */

void Read_Shader_src(const std::string file_name, 
					 std::string* shader_src)
{
	std::string completefilepath = file_name;
	std::ifstream file;
    std::string line;
	file.open(file_name.c_str());
	if (!file)
	{
		std::cout << file_name << " DNE" << std::endl;
		return;
	}
	while (std::getline(file, line))
	{
		*shader_src += line + "\n";
	}
}

/**
 * @fn	bool GLSLProgram::Load_shader(const char* shader_src, unsigned int shader_type)const
 *
 * @brief	Loads a shader.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 *
 * @exception	GlslProgCompileExc	Thrown when glsl prog compile exc.
 *
 * @param	shader_src 	The shader source.
 * @param	shader_type	Type of the shader.
 *
 * @return	true if it succeeds, false if it fails.
 */

bool GLSLProgram::Load_shader(const char* shader_src, 
							  unsigned int shader_type)const
{
	std::string shader;

	Read_Shader_src(shader_src,&shader);

	std::cout << shader << std::endl;

	unsigned int shaderID = glCreateShader(shader_type);

	const char* files[1] = {(const char*)(shader.c_str())};

	glShaderSource(shaderID,1,files,NULL);
	glCompileShader(shaderID);
	int status;
	glGetShaderiv((unsigned int)shaderID,GL_COMPILE_STATUS,&status);
	if( status != GL_TRUE ) 
	{
		std::string log = Get_log( (unsigned int)shaderID );
		std::cout << log.c_str() << std::endl;
		throw GlslProgCompileExc(log,shader_type);
		
		return false;
	}
	glAttachShader(m_shader_info->ID, shaderID);
	return true;
}

/**
 * @fn	GLSLProgram::~GLSLProgram()
 *
 * @brief	Destructor.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

GLSLProgram::~GLSLProgram()
{
	m_shader_info = NULL;
	delete [] m_shader_info;
	m_Enabled = false;
}

/**
 * @fn	void GLSLProgram::Bind()
 *
 * @brief	Binds this object.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

void GLSLProgram::Bind()
{
	glUseProgram(m_shader_info->ID);
}

/**
 * @fn	void GLSLProgram::Unbind()
 *
 * @brief	Unbinds this object.
 *
 * @author	Noel Waghorn
 * @date	3/09/2011
 */

void GLSLProgram::Unbind()
{
	glUseProgram(NULL);
}

/**
 * @fn	void GLSLProgram::Link()
 *
 * @brief	Links this object.
 *
 * @author	Noel Waghorn
 * @date	2/09/2011
 */

void GLSLProgram::Link()
{
	glLinkProgram(m_shader_info->ID);	
}

/**
 * @fn	void GLSLProgram::Add_Uniform_var(UniformVar* uni_var)
 *
 * @brief	Adds a uniform variable.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 *
 * @param [in,out]	uni_var	If non-null, the uni variable.
 */

void GLSLProgram::Add_Uniform_var(UniformVar* uni_var)
{
	m_uniform_vars.push_back(uni_var);
}

/**
 * @fn	void GLSLProgram::Update_Uniform_vars()
 *
 * @brief	Updates the uniform variables.
 *
 * @author	Noel Waghorn
 * @date	5/09/2011
 */

void GLSLProgram::Update_Uniform_vars()
{
	for(int i = 0; i < (int)m_uniform_vars.size(); i++)
	{
		m_uniform_vars[i]->Update();
	}
}