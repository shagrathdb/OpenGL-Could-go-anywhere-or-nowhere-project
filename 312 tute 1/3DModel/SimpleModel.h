
#ifndef __SIMPLE_MODEL_H__
#define __SIMPLE_MODEL_H__

#include "3DModel.h"

class SimpleModel : public FreeDeeModel
{
public:
	virtual void Render() = 0;
	virtual float Get_Bounding_Sphere_radius()const=0;
	//virtual Vec3f* Get_Bounding_Box_Coords()const=0;
};

#endif