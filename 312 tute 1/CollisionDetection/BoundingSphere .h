
#ifndef __BOUNDINGSPHERE_H__
#define __BOUNDINGSPHERE_H__

#include "BoundingVolume.h"

class BoundingSphere : public BoundingVolume
{
public:
	BoundingSphere(float radius);
	virtual std::string Get_type()const;
	virtual float Get_Bounding_Sphere_radius()const;
private:
	float m_sphere_radius;
};

#endif