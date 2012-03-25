
#include "threedeeobject.h"
#include "../Utility/Mat4f.h"

/**
 * @fn	ThreeDeeObject::ThreeDeeObject()
 *
 * @brief	Default constructor.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 */

ThreeDeeObject::ThreeDeeObject()
	:RENDERSTYLE(STATIC)
{
    Clear();
}

/**
 * @fn	void ThreeDeeObject::Add_Vertex(const Vertex3f& vertex)
 *
 * @brief	Adds a vertex.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	vertex	The vertex.
 */

void ThreeDeeObject::Add_Vertex(const Vertex3f& vertex)
{
	vertices.push_back(vertex);
}

/**
 * @fn	void ThreeDeeObject::Add_Normals(const Vec3f& normal)
 *
 * @brief	Adds a normals.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	normal	The normal.
 */

void ThreeDeeObject::Add_Normals(const Vec3f& normal)
{
	normals.push_back(normal);
}

/**
 * @fn	void ThreeDeeObject::Add_TexCoords(const TexCoord2f& texCoord)
 *
 * @brief	Adds a tex coords.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	texCoord	The tex coordinate.
 */

void ThreeDeeObject::Add_TexCoords(const TexCoord2f& texCoord)
{
	texCoords.push_back(texCoord);
}

/**
 * @fn	void ThreeDeeObject::Clear()
 *
 * @brief	Clears this object to its blank/initial state.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

void ThreeDeeObject::Clear()
{
    vertices.clear();
	normals.clear();
	texCoords.clear();
	texture.Clear();
}

/**
 * @fn	void ThreeDeeObject::Create_VB0()
 *
 * @brief	Creates the vb 0.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

void ThreeDeeObject::Create_VB0()
{
	//Generate and bind VBO buffers
	glGenBuffers(1,&n_VBOHandle);
	glBindBuffer(GL_ARRAY_BUFFER, n_VBOHandle);

	glGenBuffers(1,&t_VBOHandle);
	glBindBuffer(GL_ARRAY_BUFFER, t_VBOHandle);

	glGenBuffers(1, &v_VBOHandle);
	glBindBuffer(GL_ARRAY_BUFFER, n_VBOHandle);
}

/**
 * @fn	void ThreeDeeObject::Render()
 *
 * @brief	Renders this object.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

void ThreeDeeObject::Render()
{
	//Enable VBO pointers
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	//Bind data
	glBindBuffer(GL_ARRAY_BUFFER, n_VBOHandle);
	glNormalPointer(GL_FLOAT, 0, NULL);
	glBufferData
		(GL_ARRAY_BUFFER, normals.size()*sizeof(Vec3f), 
		 &normals[0], RENDERSTYLE);

	glBindBuffer(GL_ARRAY_BUFFER, t_VBOHandle);
	glTexCoordPointer(2,GL_FLOAT, 0,NULL);
	glBufferData
		(GL_ARRAY_BUFFER, texCoords.size()*sizeof(TexCoord2f), 
		 &texCoords[0].u, RENDERSTYLE);

	glBindBuffer(GL_ARRAY_BUFFER, n_VBOHandle);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBufferData
		(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex3f), 
		 &vertices[0], RENDERSTYLE);

	//Bind texture
	glBindTexture(GL_TEXTURE_2D, texture.Get_texhandle());
	//Render
	glDrawArrays(GL_TRIANGLES,0,vertices.size());
	
	//Disable VBO pointers
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * @fn	void ThreeDeeObject::Set_Texture(const Texture& tex)
 *
 * @brief	Sets a texture.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	tex	The tex.
 */

void ThreeDeeObject::Set_Texture(const Texture& tex)
{
    texture = tex;
}

/**
 * @fn	void ThreeDeeObject::operator=(const ThreeDeeObject& object)
 *
 * @brief	= casting operator.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	object	The object.
 */

void ThreeDeeObject::operator=(const ThreeDeeObject& object)
{
	for(unsigned int i = 0; i<(unsigned int)object.vertices.size();i++)
	{
		vertices[i] = object.vertices[i];
	}

	for(unsigned int i = 0; i<(unsigned int)object.normals.size();i++)
	{
		normals[i] = object.normals[i];
	}

	for(unsigned int i = 0; i<(unsigned int)object.texCoords.size();i++)
	{
		texCoords[i] = object.texCoords[i];
	}

	v_VBOHandle = object.v_VBOHandle;
	n_VBOHandle = object.n_VBOHandle;
	t_VBOHandle = object.t_VBOHandle;

	texture = object.texture;
}

/**
 * @fn	void ThreeDeeObject::Translate(const Vec3f& delta)
 *
 * @brief	Translates.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	delta	The delta.
 */

void ThreeDeeObject::Translate(const Vec3f& delta)
{
	Translate(delta.x,delta.y,delta.z);
}

/**
 * @fn	void ThreeDeeObject::Translate(const float x,const float y,const float z)
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

void ThreeDeeObject::Translate(const float x,const float y,const float z)
{
	for(unsigned int i = 0;i<(unsigned int)vertices.size();i++)
	{
		vertices[i].x += x;
		vertices[i].y += y;
		vertices[i].z += z;
	}
}

/**
 * @fn	void ThreeDeeObject::Rotate(const float deg, const Vec3f& rotation)
 *
 * @brief	Rotates.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	deg			The degrees.
 * @param	rotation	The rotation.
 */

void ThreeDeeObject::Rotate(const float deg, const Vec3f& rotation)
{
	// Create matrix for rotation
	Mat4f mat;
	mat.Rotate(rotation,deg);
	//Roate vertices
	for(unsigned int i = 0;i<(unsigned int)vertices.size();i++)
	{
		Vec3f vertex(vertices[i].x,vertices[i].y,vertices[i].z);
		Vec3f delta = vertex*mat;
		vertices[i] = delta;
	}
	// Rotate normals
	for(unsigned int i = 0;i<(unsigned int)normals.size();i++)
	{
		normals[i] = normals[i]*mat;
	}
}

/**
 * @fn	void ThreeDeeObject::Rotate(const float deg, const float x, const float y, const float z)
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

void ThreeDeeObject::Rotate(const float deg, const float x, const float y, const float z)
{
	Rotate(deg,Vec3f(x,y,z));
}

/**
 * @fn	void ThreeDeeObject::Scale(const Vec3f& scale)
 *
 * @brief	Scales.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	scale	The scale.
 */

void ThreeDeeObject::Scale(const Vec3f& scale)
{
	for(unsigned int i = 0;i<(unsigned int)vertices.size();i++)
	{
		vertices[i] *= scale;
	}
}

/**
 * @fn	void ThreeDeeObject::Scale(const float x,const float y,const float z)
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

void ThreeDeeObject::Scale(const float x,const float y,const float z)
{
	Scale(Vec3f(x,y,z));
}

/**
 * @fn	void ThreeDeeObject::Set_VBO_Render(VBOMODE RENDERSTYLE)
 *
 * @brief	Sets a vbo render.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	RENDERSTYLE	The renderstyle.
 */

void ThreeDeeObject::Set_VBO_Render(VBOMODE RENDERSTYLE)
{
	this->RENDERSTYLE = RENDERSTYLE;
}