
#ifndef __3DMODEL_H__
#define __3DMODEL_H__

#include "../includes.h"

class FreeDeeModel
{
public:
	virtual void Render() = 0;
	virtual float Get_Bounding_Sphere_radius()const=0;
	//virtual Vec3f* Get_Bounding_Box_Coords()const=0;
};

#endif