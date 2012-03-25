

//-----------------------------------------------------------------------------
#ifndef __THREEDEEMODEL_H__
#define __THREEDEEMODEL_H__
//-----------------------------------------------------------------------------

#include "../includes.h"

#include "threedeeobject.h"
#include "../ShaderUtilities/ShaderManager/ShaderManager.h"

/**
 * @enum	DRAWSTYLE
 *
 * @brief	Values that represent DRAWSTYLE. 
 */

enum DRAWSTYLE
{
	///< Wireframe Drawstyle 
	WIREFRAME = GL_LINE,
	///< Polgyon Drawstyle 
	POLYGONAL = GL_FILL
};

/**
 * @enum	SHADERSWITCH
 *
 * @brief	Values that represent SHADERSWITCH. 
 */

enum SHADERSWITCH
{
	///< Shaders on
	ON  = true,
	///< Shaders off
	OFF = false
};

/**
 * @class	ThreeDeeModel
 *
 * @brief	Three dee model.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

class ThreeDeeModel
{
public:

	/**
	 * @fn	ThreeDeeModel::ThreeDeeModel()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 */

	ThreeDeeModel(){Clear();}

	/**
	 * @fn	ThreeDeeModel::ThreeDeeModel(const std::string file_name);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 *
	 * @param	file_name	Filename of the file.
	 */

	ThreeDeeModel(const std::string file_name);

    /**
     * @fn	void ThreeDeeModel::Clear();
     *
     * @brief	Clears this object to its blank/initial state.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     */

    void Clear();

    /**
     * @fn	void ThreeDeeModel::Add_3DObject(const ThreeDeeObject& object);
     *
     * @brief	Adds a 3 d object.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     *
     * @param	object	The object.
     */

    void Add_3DObject(const ThreeDeeObject& object);

	/**
	 * @fn	void ThreeDeeModel::Translate(const Vec3f& delta);
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
	 * @fn	void ThreeDeeModel::Translate(const float x,const float y,const float z);
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
	 * @fn	void ThreeDeeModel::Rotate(const float deg,Vec3f rotation);
	 *
	 * @brief	Rotates.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	deg			The degrees.
	 * @param	rotation	The rotation.
	 */

	void Rotate(const float deg,Vec3f rotation);

	/**
	 * @fn	void ThreeDeeModel::Rotate(float deg, const float x,const float y,const float z);
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

	void Rotate(float deg, const float x,const float y,const float z);

	/**
	 * @fn	void ThreeDeeModel::Scale(const Vec3f& scale);
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
	 * @fn	void ThreeDeeModel::Scale(const float x, const float y, const float z);
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

	void Scale(const float x, const float y, const float z);

	/**
	 * @fn	void ThreeDeeModel::Render();
	 *
	 * @brief	Renders this object.
	 *
	 * @author	Noel Waghorn
	 * @date	17/09/2011
	 */

	void Render();

	/**
	 * @fn	void ThreeDeeModel::Set_Shader(std::string shader);
	 *
	 * @brief	Sets a shader.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	shader	The shader.
	 */

	void Set_Shader(std::string shader);

	/**
	 * @fn	void ThreeDeeModel::Set_DrawStyle(const DRAWSTYLE DRAW);
	 *
	 * @brief	Sets a draw style.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	DRAW	The draw.
	 */

	void Set_DrawStyle(const DRAWSTYLE DRAW);

	/**
	 * @fn	void ThreeDeeModel::Shader_Switch(const SHADERSWITCH SWITCH);
	 *
	 * @brief	Shader switch.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param	SWITCH	The switch.
	 */

	void Shader_Switch(const SHADERSWITCH SWITCH);

    /**
     * @fn	void ThreeDeeModel::operator= (const ThreeDeeModel& model);
     *
     * @brief	Assignment operator.
     *
     * @author	Noel Waghorn
     * @date	17/09/2011
     *
     * @param	model	The model.
     */

    void operator = (const ThreeDeeModel& model);
private:
	///< The three dee objects
    std::vector<ThreeDeeObject> threeDeeObjects;
	///< The shader
	std::string shader;
	///< The sm
	ShaderManager* _SM;
	///< The switch
	SHADERSWITCH _SWITCH;
	///< The draw
	DRAWSTYLE _DRAW;
};



//-----------------------------------------------------------------------------
#endif  //__THREEDEEMODEL_H__
//-----------------------------------------------------------------------------
