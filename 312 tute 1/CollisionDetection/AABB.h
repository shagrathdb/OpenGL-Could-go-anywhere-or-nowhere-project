
#ifndef __AABB_H__
#define __AABB_H__

#include "BoundingVolume.h"

class AABB : public BoundingVolume
{
public:
	AABB(float height, float width, float length);
	virtual std::string Get_type()const;
	float* Get_vertices(int i);
	virtual float Get_Bounding_Sphere_radius()const;
private:
	Vec3f m_vertices[8];
};

#endif