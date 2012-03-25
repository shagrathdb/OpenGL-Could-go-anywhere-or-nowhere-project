/**
 * @file mloader.cpp
 * @brief ModelLoader class implementation file.
 * @author Noel Waghorn
 * @version 0.4
 * @date 24/09/2010
 */

#include <sstream>

#include "ModelFactory.h"
#include "../Utility/tokenizer.h"

//-----------------------------------------------------
//Initialisation of static members block
///< The wf model factory instance
WFModelFactory* WFModelFactory::_instance = NULL;
///< The wf model factory vertices
std::vector<Vertex3f>* WFModelFactory::vertices = NULL;
///< The wf model factory tex coords
std::vector<TexCoord2f>* WFModelFactory::texCoords = NULL;
///< The wf model factory normals
std::vector<Vec3f>*    WFModelFactory::normals = NULL;
///< The wf model factory v indices
std::vector<unsigned int>*    WFModelFactory::v_indices = NULL;
///< The wf model factory t indices
std::vector<unsigned int>*    WFModelFactory::t_indices = NULL;
///< The wf model factory n indices
std::vector<unsigned int>*    WFModelFactory::n_indices = NULL;
///< Name of the wf model factory group
std::vector<std::string>* WFModelFactory::groupName = NULL;
///< Name of the wf model factory material
std::vector<std::string>* WFModelFactory::material_name = NULL;
///< The wf model factory model factory
FlyweightFactory<ThreeDeeModel>* WFModelFactory::model_factory = NULL;
///< Group the wf model factory faces per belongs to
std::vector<unsigned int>* WFModelFactory::faces_per_group = NULL;
///< Number of wf model factory faces
int WFModelFactory::face_count = 0;
///< The wf model factory model location
std::string WFModelFactory::model_loc;
///< The wf model factory tex location
std::string WFModelFactory::tex_loc;
//-----------------------------------------------------

/**
 * @fn	WFModelFactory* WFModelFactory::Instance()
 *
 * @brief	Gets the instance.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @return	null if it fails, else.
 */

WFModelFactory* WFModelFactory::Instance()
{
	if(_instance==NULL)
	{
		_instance = new WFModelFactory;
	}
	return _instance;
}

/**
 * @fn	WFModelFactory::WFModelFactory()
 *
 * @brief	Default constructor.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

WFModelFactory::WFModelFactory()
{
    Clear();
	model_factory = new FlyweightFactory<ThreeDeeModel>;
	model_factory->Register_callbacks(&Load_model);
}

/**
 * @fn	void WFModelFactory::Clear()
 *
 * @brief	Clears this object to its blank/initial state.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

void WFModelFactory::Clear()
{
    vertices		= new std::vector<Vertex3f>;
    texCoords		= new std::vector<TexCoord2f>;
    normals			= new std::vector<Vec3f>;
    groupName		= new std::vector<std::string>;
    material_name	= new std::vector<std::string>;
	v_indices		= new std::vector<unsigned int>;
	t_indices		= new std::vector<unsigned int>;
	n_indices		= new std::vector<unsigned int>;	
	faces_per_group = new std::vector<unsigned int>;
}

/**
 * @fn	ThreeDeeModel* WFModelFactory::Get_Model(std::string fname)
 *
 * @brief	Gets a model.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	fname	Filename of the file.
 *
 * @return	null if it fails, else the model.
 */

ThreeDeeModel* WFModelFactory::Get_Model(std::string fname)
{
	return model_factory->Get_data(model_loc+fname);
}

/**
 * @fn	bool WFModelFactory::Load_model(std::string file_name,ThreeDeeModel& model)
 *
 * @brief	Loads a model.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	file_name	 	Filename of the file.
 * @param [in,out]	model	The model.
 *
 * @return	true if it succeeds, false if it fails.
 */

bool WFModelFactory::Load_model(std::string file_name,ThreeDeeModel& model)
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
        Tokenise_Data(input);
    }

	Process_input(model);

    infile.close();

    return true;
}

/**
 * @fn	void WFModelFactory::Process_input(ThreeDeeModel& model)
 *
 * @brief	Process the input described by model.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param [in,out]	model	The model.
 */

void WFModelFactory::Process_input(ThreeDeeModel& model)
{
	//std::vector<Vec3f> v_inorder,n_inorder;
	//std::vector<Vec2f> t_inorder;

	unsigned int start_index = 0;
	unsigned int final_index = 0;

	for(unsigned int i=0;i<groupName->size();i++)      //loop the number of groups(objects)
    {
		ThreeDeeObject currentObject;
		
		Texture texToLoad((*material_name)[i]);//create the texture object with the texture name

        if(!(texToLoad.Load_Texture()))//if loaded succesfully
        {
			std::cout << "File DNE" << std::endl;
        }
        currentObject.Set_Texture(texToLoad);  //set the object's texture

		if(i>0)
		{
			start_index+=(*faces_per_group)[i-1]*3;
		}		

		final_index = (*faces_per_group)[i]*3+start_index;

        for(unsigned int j=start_index;j<final_index;j++)       //loop the number of faces in the object
        {
			currentObject.Add_Vertex((*vertices)[(*v_indices)[j]]);
			currentObject.Add_Normals((*normals)[(*n_indices)[j]]);
			currentObject.Add_TexCoords((*texCoords)[(*t_indices)[j]]);
        }
		currentObject.Create_VB0();
        model.Add_3DObject(currentObject);              //add the object to the model
        currentObject.Clear();
    }
    vertices->clear();
    texCoords->clear();
    normals->clear();
	faces_per_group->clear();
	v_indices->clear();
	n_indices->clear();
	t_indices->clear();
	groupName->clear();
	material_name->clear();
}

/**
 * @fn	void WFModelFactory::Tokenise_Data(std::string input)
 *
 * @brief	Tokenise data.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	input	The input.
 */

void WFModelFactory::Tokenise_Data(std::string input)
{
	StringTokens tokens(input,' ');

	if(tokens.First_token()=="v")              //if vertices
    {
		tokens.Next_token();

        float x = (float)atof(tokens.Next_token().c_str()); //x value
        float y = (float)atof(tokens.Next_token().c_str()); //y value
        float z = (float)atof(tokens.Next_token().c_str()); //z value

		Vertex3f vertex(x,y,z);

		vertices->push_back(vertex);
    }
    else if(tokens.First_token()=="vn")        //if normals
    {
		tokens.Next_token();

		float x = (float)atof(tokens.Next_token().c_str()); //x value
        float y = (float)atof(tokens.Next_token().c_str()); //y value
        float z = (float)atof(tokens.Next_token().c_str()); //z value

		Vec3f normal(x,y,z);

		normals->push_back(normal);
	}
    else if(tokens.First_token()=="vt")        //if texture coords
    {
        tokens.Next_token();

		float u = (float)atof(tokens.Next_token().c_str()); //u value
        float v = (float)atof(tokens.Next_token().c_str()); //v value

		TexCoord2f texCoord(u,v);

		texCoords->push_back(texCoord);
	}
	else if(tokens.First_token()=="f")         //if face
    {
		tokens.Next_token();
		Vec3f temp;
        for(int i=0;i<3;i++)        //get 3 vert indexes, text coord index, normals index
        {
			StringTokens faceTokens(tokens.Next_token(),'/');
			
			v_indices->push_back(atoi(faceTokens.Next_token().c_str())-1);    //store vertex index

			t_indices->push_back(atoi(faceTokens.Next_token().c_str())-1);
			
			n_indices->push_back(atoi(faceTokens.Next_token().c_str())-1);
		}
	}
	else if(tokens.First_token()=="g")         //if group
    {
		tokens.Next_token();
        groupName->push_back(tokens.Next_token()); //store the group name
    }
    else if(tokens.First_token()=="#")             //if a hash
    {
		tokens.Next_token();

		face_count = atoi(tokens.Next_token().c_str());
		
        if(tokens.Next_token()=="faces")          //check to see if it's followed by number of faces
        {
            faces_per_group->push_back(face_count); //store the number of faces for that group
        }
        face_count = 0;              //reset number of faces to 0
    }
	else if(tokens.First_token()=="mtllib")        //if material lib
    {
        std::string mtl = model_loc;      //mtl file location
        std::string image = tex_loc; //image file location
		std::string temp2;
		tokens.Next_token();
        mtl.append(tokens.Next_token());          //add it to the location
        std::ifstream material(mtl.c_str()); //create input filestream for MTL

        if(material)        //if material exists
        {
            while(std::getline(material, temp2)) //tokenize MTL
            {
                std::istringstream matName(temp2);
                getline(matName,temp2); //get image name
                image.append(temp2);    //add it to the location
                material_name->push_back(image);   //store it
                image = tex_loc;    //reset image to only location
            }
        }
        else                //if material DNE
        {
            std::cout << "material file " << temp2 << " DNE" << std::endl;
        }
    }
}

/**
 * @fn	void WFModelFactory::Set_Resource_loc(std::string model_loc,std::string tex_loc)
 *
 * @brief	Sets a resource location.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	model_loc	The model location.
 * @param	tex_loc  	The tex location.
 */

void WFModelFactory::Set_Resource_loc(std::string model_loc,std::string tex_loc)
{
	this->model_loc = model_loc;
	this->tex_loc   = tex_loc;
}