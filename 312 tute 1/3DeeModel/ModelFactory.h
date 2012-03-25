

//-----------------------------------------------------------------------------
#ifndef __MODELFACTORY_H__
#define __MODELFACTORY_H__
//-----------------------------------------------------------------------------

#include "ThreeDeeModel.h"

#include "../Utility/FlyweightFactory.h"

/**
 * @class	WFModelFactory
 *
 * @brief	Wf model factory. 
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

class WFModelFactory
{
public:
	///< The model
	friend class Model;

	/**
	 * @fn	static WFModelFactory* WFModelFactory::Instance();
	 *
	 * @brief	Gets the instance.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @return	null if it fails, else.
	 */

	static WFModelFactory* Instance();

    /**
     * @fn	static void WFModelFactory::Clear();
     *
     * @brief	Clears this object to its blank/initial state.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     */

    static void Clear();

	/**
	 * @fn	static ThreeDeeModel* WFModelFactory::Get_Model(std::string fname);
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

	static ThreeDeeModel* Get_Model(std::string fname);

	/**
	 * @fn	void WFModelFactory::Set_Resource_loc(std::string model_loc,std::string tex_loc);
	 *
	 * @brief	Sets a resource location.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	model_loc	The model location.
	 * @param	tex_loc  	The tex location.
	 */

	void Set_Resource_loc(std::string model_loc,std::string tex_loc);
private:
	///< The instance
	static WFModelFactory* _instance;
    ///< The vertices
    static std::vector<Vertex3f>* vertices;
    ///< The tex coords
    static std::vector<TexCoord2f>* texCoords;
    ///< The normals
    static std::vector<Vec3f>* normals;
    ///< The v indices
    static std::vector<unsigned int>* v_indices;
    ///< The indices
    static std::vector<unsigned int>* t_indices;
    ///< The indices
    static std::vector<unsigned int>* n_indices;
    ///< Name of the group
    static std::vector<std::string>* groupName;
    ///< Name of the material
    static std::vector<std::string>* material_name;
	///< The model factory
	static FlyweightFactory<ThreeDeeModel>* model_factory;
	///< Group the faces per belongs to
	static std::vector<unsigned int>* faces_per_group;
	///< Number of faces
	static int face_count;
	///< The model location
	static std::string model_loc;
	///< The tex location
	static std::string tex_loc;

	/**
	 * @fn	WFModelFactory::WFModelFactory();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 */

	WFModelFactory();

	/**
	 * @fn	static bool WFModelFactory::Load_model(std::string file_name,ThreeDeeModel& model);
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

	static bool Load_model(std::string file_name,ThreeDeeModel& model);

	/**
	 * @fn	static void WFModelFactory::Tokenise_Data(std::string input);
	 *
	 * @brief	Tokenise data.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	input	The input.
	 */

	static void Tokenise_Data(std::string input);

	/**
	 * @fn	static void WFModelFactory::Process_input(ThreeDeeModel &model);
	 *
	 * @brief	Process the input described by model.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param [in,out]	model	The model.
	 */

	static void Process_input(ThreeDeeModel &model);

	/**
	 * @fn	void WFModelFactory::Create_VBO();
	 *
	 * @brief	Creates the vbo.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 */

	void Create_VBO();
};


//------------------------------------------------------------------------------
#endif  //__MLOAD_H__
//------------------------------------------------------------------------------
