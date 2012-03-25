
#ifndef __RHOMBIC_H__
#define __RHOMBIC_H__

#include "SimpleModel.h"

class RhombicDodecahedron : public SimpleModel
{
public:
	virtual void Render()
	{
		glPushMatrix();
			glutSolidRhombicDodecahedron();
		glPopMatrix();
	}

	virtual float Get_Bounding_Sphere_radius()const
	{
		return 0.2;
	}
};


#endif