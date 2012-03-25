

#ifndef __PHYSICSOBJ_H__
#define __PHYSICSOBJ_H__

#include "../3DModel/3DModel.h"
#include "../CollisionDetection/BoundingVolume.h"

class PhysicsObj
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
protected:
	FreeDeeModel* m_3d_model;
	BoundingVolume* m_bounding_volume;
};

#endif