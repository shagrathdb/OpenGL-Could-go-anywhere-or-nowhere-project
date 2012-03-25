

#include "texture.h"

/**
 * @fn	Texture::Texture()
 *
 * @brief	Default constructor.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

Texture::Texture()
{
    Clear();
}

/**
 * @fn	Texture::Texture(const std::string file_name)
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	file_name	Filename of the file.
 */

Texture::Texture(const std::string file_name)
{
    this->file_name = file_name;
}

/**
 * @fn	Texture::Texture(const Texture& tex)
 *
 * @brief	Copy constructor.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	tex	The tex.
 */

Texture::Texture(const Texture& tex)
{
    file_name = tex.file_name;
    tex_handle = tex.tex_handle;
}

/**
 * @fn	void Texture::Clear()
 *
 * @brief	Clears this object to its blank/initial state.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

void Texture::Clear()
{
    tex_handle = 0;
    file_name.clear();
}

/**
 * @fn	void Texture::Set_File_name(const std::string file_name)
 *
 * @brief	Sets a file name.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	file_name	Filename of the file.
 */

void Texture::Set_File_name(const std::string file_name)
{
    this->file_name = file_name;
}

/**
 * @fn	void Texture::operator= (const Texture& tex)
 *
 * @brief	= casting operator.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	tex	The tex.
 */

void Texture::operator = (const Texture& tex)
{
    file_name   = tex.file_name;
    tex_handle  = tex.tex_handle;
}

/**
 * @fn	bool Texture::Load_Texture()
 *
 * @brief	Loads the texture.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @return	true if it succeeds, false if it fails.
 */

bool Texture::Load_Texture()
{
    if(file_name!= "") //if the filename has been set
    {
        tex_handle = SOIL_load_OGL_texture
        (
            file_name.c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS 
			| SOIL_FLAG_NTSC_SAFE_RGB 
			| SOIL_FLAG_COMPRESS_TO_DXT
			| SOIL_FLAG_TEXTURE_REPEATS
        );  //load the texture
        return true;
    }
    else    //else return false, didnt load a texture
    {
        return false;
    }
}

