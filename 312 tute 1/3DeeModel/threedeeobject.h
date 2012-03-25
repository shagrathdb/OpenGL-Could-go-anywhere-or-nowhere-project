

//-----------------------------------------------------------------------------
#ifndef __3DOBJECT_H__
#define __3DOBJECT_H__
//-----------------------------------------------------------------------------

#include "../includes.h"
#include "texture.h"
#include "../Utility/Vec3f.h"
#include "texcoord2f.h"
#include "vertex.h"
#include "../Utility/Mat4f.h"

/**
 * @enum	VBOMODE
 *
 * @brief	Values that represent VBOMODE. 
 */

enum VBOMODE
{
	///< Static Draw Mode
	STATIC  = GL_STATIC_DRAW,
	///< Dynamic Draw Mode
	DYNAMIC = GL_DYNAMIC_DRAW,
	///< Stream Draw Mode
	STREAM  = GL_STREAM_DRAW
};

/**
 * @class	ThreeDeeObject
 *
 * @brief	Three dee object.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

class ThreeDeeObject
{
 public:

    /**
     * @fn	ThreeDeeObject::ThreeDeeObject();
     *
     * @brief	Default constructor.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     */

    ThreeDeeObject();

    /**
     * @fn	void ThreeDeeObject::Clear();
     *
     * @brief	Clears this object to its blank/initial state.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     */

    void Clear();

    /**
     * @fn	void ThreeDeeObject::Add_Vertex(const Vertex3f& vertex);
     *
     * @brief	Adds a vertex.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     *
     * @param	vertex	The vertex.
     */

    void Add_Vertex(const Vertex3f& vertex);

	/**
	 * @fn	void ThreeDeeObject::Add_Normals(const Vec3f& normal);
	 *
	 * @brief	Adds a normals.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	normal	The normal.
	 */

	void Add_Normals(const Vec3f& normal);

	/**
	 * @fn	void ThreeDeeObject::Add_TexCoords(const TexCoord2f& texCoord);
	 *
	 * @brief	Adds a tex coords.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	texCoord	The tex coordinate.
	 */

	void Add_TexCoords(const TexCoord2f& texCoord);

	/**
	 * @fn	void ThreeDeeObject::Create_VB0();
	 *
	 * @brief	Creates the vb 0.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 */

	void Create_VB0();

    /**
     * @fn	void ThreeDeeObject::Set_Texture(const Texture& tex);
     *
     * @brief	Sets a texture.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     *
     * @param	tex	The.
     */

    void Set_Texture(const Texture& tex);

	/**
	 * @fn	void ThreeDeeObject::Render();
	 *
	 * @brief	Renders this object.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 */

	void Render();

	/**
	 * @fn	void ThreeDeeObject::Translate(const Vec3f& delta);
	 *
	 * @brief	Translates.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	delta	The delta.
	 */

	void Translate(const Vec3f& delta);

	/**
	 * @fn	void ThreeDeeObject::Translate(const float x,const float y,const float z);
	 *
	 * @brief	Translates.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 * @param	z	The z coordinate.
	 */

	void Translate(const float x,const float y,const float z);

	/**
	 * @fn	void ThreeDeeObject::Rotate(const float deg, const Vec3f& rotation);
	 *
	 * @brief	Rotates.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	deg			The degrees.
	 * @param	rotation	The rotation.
	 */

	void Rotate(const float deg, const Vec3f& rotation);

	/**
	 * @fn	void ThreeDeeObject::Rotate(const float deg, const float x, const float y, const float z);
	 *
	 * @brief	Rotates.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	deg	The degrees.
	 * @param	x  	The x coordinate.
	 * @param	y  	The y coordinate.
	 * @param	z  	The z coordinate.
	 */

	void Rotate(const float deg, const float x, const float y, const float z);

	/**
	 * @fn	void ThreeDeeObject::Scale(const Vec3f& scale);
	 *
	 * @brief	Scales.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	scale	The scale.
	 */

	void Scale(const Vec3f& scale);

	/**
	 * @fn	void ThreeDeeObject::Scale(const float x,const float y,const float z);
	 *
	 * @brief	Scales.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 * @param	z	The z coordinate.
	 */

	void Scale(const float x,const float y,const float z);

	/**
	 * @fn	void ThreeDeeObject::Set_VBO_Render(VBOMODE RENDERSTYLE);
	 *
	 * @brief	Sets a vbo render.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	RENDERSTYLE	The renderstyle.
	 */

	void Set_VBO_Render(VBOMODE RENDERSTYLE);

	/**
	 * @fn	void ThreeDeeObject::operator=(const ThreeDeeObject& object);
	 *
	 * @brief	Assignment operator.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	object	The.
	 */

	void operator=(const ThreeDeeObject& object);
 private:
    ///< The vertices
    std::vector<Vertex3f> vertices;
	///< The normals
	std::vector<Vec3f> normals;
	///< The tex coords
	std::vector<TexCoord2f> texCoords;
	///< The texture
	Texture texture;
	///< Handle of the v vbo
	unsigned int v_VBOHandle;
	///< Handle of the vbo
	unsigned int n_VBOHandle;
	///< Handle of the vbo
	unsigned int t_VBOHandle;
	///< The renderstyle
	VBOMODE RENDERSTYLE;
};

//-----------------------------------------------------------------------------
#endif  
//-----------------------------------------------------------------------------
