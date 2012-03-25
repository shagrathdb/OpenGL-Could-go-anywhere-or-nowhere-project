

#include "ThreeDeeModel.h"
#include "ModelFactory.h"

/**
 * @fn	ThreeDeeModel::ThreeDeeModel(const std::string file_name) :_DRAW(POLYGONAL),_SWITCH(ON),
 * 		_SM(ShaderManager::Instance())
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	file_name	Filename of the file.
 */

ThreeDeeModel::ThreeDeeModel(const std::string file_name)
	:_DRAW(POLYGONAL),_SWITCH(ON),_SM(ShaderManager::Instance())
{
	*this = *WFModelFactory::Instance()->Get_Model(file_name);
}

/**
 * @fn	void ThreeDeeModel::Render()
 *
 * @brief	Renders this object.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

void ThreeDeeModel::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK,_DRAW);
	
	_SWITCH?
		_SM->Enable_shader(shader):
		_SM->Disable_shader(shader);
	
	for(unsigned int i=0;i<(unsigned int)threeDeeObjects.size();i++)
	{
		threeDeeObjects[i].Render();
	}
	
	ShaderManager::Instance()->Disable_shader(shader);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

/**
 * @fn	void ThreeDeeModel::Clear()
 *
 * @brief	Clears this object to its blank/initial state.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 */

void ThreeDeeModel::Clear()
{
	threeDeeObjects.clear();
}

/**
 * @fn	void ThreeDeeModel::Add_3DObject(const ThreeDeeObject& object)
 *
 * @brief	Adds a 3 d object.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	object	The object.
 */

void ThreeDeeModel::Add_3DObject(const ThreeDeeObject& object)
{
	threeDeeObjects.push_back(object);
}

/**
 * @fn	void ThreeDeeModel::operator= (const ThreeDeeModel& model)
 *
 * @brief	= casting operator.
 *
 * @author	Noel Waghorn
 * @date	17/09/2011
 *
 * @param	model	The model.
 */

void ThreeDeeModel::operator = (const ThreeDeeModel& model)
{
	threeDeeObjects = model.threeDeeObjects;

	for(unsigned int i = 0;i<(unsigned int)model.threeDeeObjects.size();i++)
	{
		threeDeeObjects[i] = model.threeDeeObjects[i];
	}
}

/**
 * @fn	void ThreeDeeModel::Set_Shader(std::string shader)
 *
 * @brief	Sets a shader.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	shader	The shader.
 */

void ThreeDeeModel::Set_Shader(std::string shader)
{
	this->shader = shader;
}

/**
 * @fn	void ThreeDeeModel::Set_DrawStyle(const DRAWSTYLE DRAW)
 *
 * @brief	Sets a draw style.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	DRAW	The draw.
 */

void ThreeDeeModel::Set_DrawStyle(const DRAWSTYLE DRAW)
{
	_DRAW = DRAW;
}

/**
 * @fn	void ThreeDeeModel::Translate(const Vec3f& delta)
 *
 * @brief	Translates.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	delta	The delta.
 */

void ThreeDeeModel::Translate(const Vec3f& delta)
{
	for(unsigned int i = 0;i<(unsigned int)threeDeeObjects.size();i++)
	{
		threeDeeObjects[i].Translate(delta);
	}
}

/**
 * @fn	void ThreeDeeModel::Translate(const float x,const float y,const float z)
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

void ThreeDeeModel::Translate(const float x,const float y,const float z)
{
	Translate(Vec3f(x,y,z));
}

/**
 * @fn	void ThreeDeeModel::Rotate(const float deg,Vec3f rotation)
 *
 * @brief	Rotates.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	deg			The degrees.
 * @param	rotation	The rotation.
 */

void ThreeDeeModel::Rotate(const float deg,Vec3f rotation)
{
	for(unsigned int i = 0;i<(unsigned int)threeDeeObjects.size();i++)
	{
		threeDeeObjects[i].Rotate(deg,rotation);
	}
}

/**
 * @fn	void ThreeDeeModel::Rotate(float deg, const float x,const float y,const float z)
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

void ThreeDeeModel::Rotate(float deg, const float x,const float y,const float z)
{
	Rotate(deg, Vec3f(x,y,z));
}

/**
 * @fn	void ThreeDeeModel::Scale(const Vec3f& scale)
 *
 * @brief	Scales.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	scale	The scale.
 */

void ThreeDeeModel::Scale(const Vec3f& scale)
{
	for(unsigned int i = 0;i<(unsigned int)threeDeeObjects.size();i++)
	{
		threeDeeObjects[i].Scale(scale);
	}
}

/**
 * @fn	void ThreeDeeModel::Scale(const float x, const float y, const float z)
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

void ThreeDeeModel::Scale(const float x, const float y, const float z)
{
	Scale(Vec3f(x,y,z));
}

/**
 * @fn	void ThreeDeeModel::Shader_Switch(const SHADERSWITCH SWITCH)
 *
 * @brief	Shader switch.
 *
 * @author	Noel Waghorn
 * @date	18/09/2011
 *
 * @param	SWITCH	The switch.
 */

void ThreeDeeModel::Shader_Switch(const SHADERSWITCH SWITCH)
{
	_SWITCH = SWITCH;
}