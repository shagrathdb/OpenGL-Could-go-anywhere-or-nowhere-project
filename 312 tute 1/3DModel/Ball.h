

#ifndef __BALL_H__
#define __BALL_H__

#include "SimpleModel.h"
#include "../3DeeModel/texture.h"

class BallModel : public SimpleModel
{
public:
	BallModel(){}
	virtual void Render()
	{
		glPushMatrix();
			glutSolidSphere(0.2,16,16);
		glPopMatrix();
	}

	virtual float Get_Bounding_Sphere_radius()const
	{
		return 0.2;
	}

	Texture m_tex;
};


#endif