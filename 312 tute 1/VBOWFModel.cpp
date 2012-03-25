

#include "VBOWFModel.h"

#include <fstream>
#include <sstream>
#include "Utility\tokenizer.h"

VBOWFModel::VBOWFModel(const std::string root, const std::string file_name)
{
	std::string fname = root+file_name;
	if(!Load_model(root,fname))
	{
		std::cout << "File DNE" << std::endl;
	}
}



bool VBOWFModel::Load_model(const std::string root, const std::string file_name)
{
	std::ifstream infile(file_name.c_str());
	std::string input;

    if(!infile)
    {
        return false;
    }
    std::cout << "Proceed to load obj file..." << std::endl;

	while(std::getline(infile, input))   //get each line of the obj file
    {
        //tokenize each line
        Tokenise_Data(input);
    }

	for(int i=0;i<m_Tindices.size();i++)
	{
		m_texcoords.push_back(tex[m_Tindices[i]]);
	}
	

	for(int i=0;i<m_Vindices.size();i++)
	{
		m_vertices.push_back(verts[m_Vindices[i]]);
	}

	for(int i=0;i<m_Nindices.size();i++)
	{
		m_normals.push_back(norms[m_Nindices[i]]);
	}


    infile.close();

	Create_VBO();

    return true;
}


void VBOWFModel::Tokenise_Data(std::string input)
{
	float tempfloat[3];         //temporary float array of 3
	StringTokens tokens(input,' ');
	

	if(tokens.First_token()=="v")              //if vertices
    {
		tokens.Next_token();

        tempfloat[0] = (float)atof(tokens.Next_token().c_str()); //x value
		
        tempfloat[1] = (float)atof(tokens.Next_token().c_str()); //y value

        tempfloat[2] = (float)atof(tokens.Next_token().c_str()); //z value

		verts.push_back(Vec3f(tempfloat[0],tempfloat[1],tempfloat[2]));
    }
    else if(tokens.First_token()=="vn")        //if normals
    {
		tokens.Next_token();
        tempfloat[0] = (float)atof(tokens.Next_token().c_str()); //x value

        tempfloat[1] = (float)atof(tokens.Next_token().c_str()); //y value

        tempfloat[2] = (float)atof(tokens.Next_token().c_str()); //z value

		norms.push_back(Vec3f(tempfloat[0],tempfloat[1],tempfloat[2]));
	}
    else if(tokens.First_token()=="vt")        //if texture coords
    {
        tokens.Next_token();
		tempfloat[0] = (float)atof(tokens.Next_token().c_str()); //x value

        tempfloat[1] = (float)atof(tokens.Next_token().c_str()); //y value

        tempfloat[2] = (float)atof(tokens.Next_token().c_str()); //z value

		tex.push_back(Vec2f(tempfloat[0],tempfloat[1]));		
	}
	else if(tokens.First_token()=="f")         //if face
    {
		tokens.Next_token();
		Vec3f temp;
        for(int i=0;i<3;i++)        //get 3 vert indexes, text coord index, normals index
        {
			StringTokens faceTokens(tokens.Next_token(),'/');
			
			m_Vindices.push_back(atoi(faceTokens.Next_token().c_str())-1);    //store vertex index

			m_Tindices.push_back(atoi(faceTokens.Next_token().c_str())-1);
			
			m_Nindices.push_back(atoi(faceTokens.Next_token().c_str())-1);
		}
	}
	else if(tokens.First_token()=="mtllib")        //if material lib
    {
        string mtl = "Model/";      //mtl file location
        string image = "textures/wdworld/"; //image file location
		string temp2;
		tokens.Next_token();
        mtl.append(tokens.Next_token());          //add it to the location
        ifstream material(mtl.c_str()); //create input filestream for MTL

        if(material)        //if material exists
        {
            while(std::getline(material, temp2)) //tokenize MTL
            {
                istringstream matName(temp2);
                getline(matName,temp2); //get image name
                image.append(temp2);    //add it to the location
                mtlName.push_back(image);   //store it
                image = "textures/wdworld/";    //reset image to only location
            }
			m_texture = Texture(mtlName.back());
			if(!(m_texture.LoadTexture()))//if loaded succesfully
			{
				cout << "File DNE" << endl;
			}
        }
        else                //if material DNE
        {
            cout << "material file " << temp2 << " DNE" << endl;
        }
    }
}

void VBOWFModel::Create_VBO()
{
	glGenBuffers(1,&m_NVBO_handle);
	glBindBuffer(GL_ARRAY_BUFFER, m_NVBO_handle);

	glGenBuffers(1,&m_TVBO_handle);
	glBindBuffer(GL_ARRAY_BUFFER, m_TVBO_handle);

	glGenBuffers(1, &m_VVBO_handle);
	glBindBuffer(GL_ARRAY_BUFFER, m_VVBO_handle);
}


void VBOWFModel::Render(RenderMode mode)
{
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_NVBO_handle);
	glNormalPointer(GL_FLOAT, 0, NULL);
	glBufferData
		(GL_ARRAY_BUFFER, m_normals.size()*sizeof(Vec3f), 
		 &m_normals[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_TVBO_handle);
	glTexCoordPointer(2,GL_FLOAT, 0,NULL);
	glBufferData
		(GL_ARRAY_BUFFER, m_texcoords.size()*sizeof(Vec2f), 
		 &m_texcoords[0].x, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_VVBO_handle);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBufferData
		(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(Vec3f), 
		 &m_vertices[0], GL_STATIC_DRAW);

	
	if(mode==WIREFRAME)
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}

	glBindTexture(GL_TEXTURE_2D, m_texture.GetTextID());

	glDrawArrays(GL_TRIANGLES,0,m_Vindices.size());
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	/*int i;
	for(i=0;i<poo;i+=3)
    {
        glPushMatrix();
            //-----------------------------------------------------------------
		glBegin(GL_TRIANGLE_STRIP);  //draw triangles
            //-----------------------------------------------------------------

                glNormal3fv(m_normals[i]);
				glTexCoord2fv(m_texcoords[i]);
                glVertex3fv(m_vertices[i]);
				glTexCoord2fv(m_texcoords[i+1]);
				glVertex3fv(m_vertices[i+1]);
				glTexCoord2fv(m_texcoords[i+2]);
				glVertex3fv(m_vertices[i+2]);
           //---------------------------------------------------------

                
            //-----------------------------------------------------------------
            glEnd();                //end draw
            //-----------------------------------------------------------------
        glPopMatrix();
    }*/
}


