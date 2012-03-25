
#ifndef __VBOWFMODEL_H__
#define __VBOWFMODEL_H__

#include "includes.h"
#include "3DeeModel\texture.h"

static enum RenderMode
{
	WIREFRAME,
	FILL
};

class VBOWFModel
{
public:
	VBOWFModel(){}
	VBOWFModel(const std::string root, const std::string file_name);
	void Render(RenderMode mode);
private:
	std::vector<Vec3f> m_vertices;
	std::vector<Vec3f> m_normals;
	std::vector<Vec2f> m_texcoords;
	std::vector<unsigned int> m_Vindices;
	std::vector<unsigned int> m_Nindices;
	std::vector<unsigned int> m_Tindices;
	unsigned int m_VVBO_handle;
	unsigned int m_NVBO_handle;
	unsigned int m_TVBO_handle;
	Texture m_texture;

	std::vector<Vec2f> tex;
	std::vector<Vec3f> verts;
	std::vector<Vec3f> norms;

	std::vector<std::string> mtlName;

	bool Load_model(const std::string root, const std::string file_name);
	void Tokenise_Data(std::string input);
	void Create_VBO();
};


#endif