

//-----------------------------------------------------------------------------
#ifndef __TEX_H__
#define __TEX_H__
//-----------------------------------------------------------------------------

#include <fstream>

#include "../includes.h"
#include "../soil/SOIL.h"

/**
 * @class	Texture
 *
 * @brief	Texture class
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

class Texture
{
 public:

    /**
     * @fn	Texture::Texture();
     *
     * @brief	Default constructor.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     */

    Texture();

    /**
     * @fn	Texture::Texture(const std::string file_name);
     *
     * @brief	Constructor.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     *
     * @param	file_name	Filename of the file.
     */

    Texture(const std::string file_name);

    /**
     * @fn	Texture::Texture(const Texture& tex);
     *
     * @brief	Copy constructor.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     *
     * @param	tex	The tex.
     */

    Texture(const Texture& tex);

	/**
	 * @fn	void Texture::Clear();
	 *
	 * @brief	Clears this object to its blank/initial state.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 */

	void Clear();

	/**
	 * @fn	void Texture::Set_File_name(const std::string file_name);
	 *
	 * @brief	Sets a file name.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	file_name	Filename of the file.
	 */

	void Set_File_name(const std::string file_name);

	/**
	 * @fn	bool Texture::Load_Texture();
	 *
	 * @brief	Loads the texture.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	bool Load_Texture();

	/**
	 * @fn	unsigned int Texture::Get_texhandle()const
	 *
	 * @brief	Gets the texhandle.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @return	The texhandle.
	 */

	unsigned int Get_texhandle()const{return tex_handle;}

	/**
	 * @fn	void Texture::operator= (const Texture& tex);
	 *
	 * @brief	Assignment operator.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	tex	The tex.
	 */

	void operator = (const Texture& tex);

 private:
    ///< Filename of the file
    std::string file_name;
    ///< Handle of the tex
    unsigned int tex_handle;
};


//-----------------------------------------------------------------------------
#endif  //__TEX_H__
//-----------------------------------------------------------------------------
