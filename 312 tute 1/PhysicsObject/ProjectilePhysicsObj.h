
#ifndef __PROJECTILE_PHYSICSOBJ_H__
#define __PROJECTILE_PHYSICSOBJ_H__

#include "PhysicsObj.h"
#include "../includes.h"

class ProjectilePhysicsObj : public PhysicsObj
{
public:
	ProjectilePhysicsObj(FreeDeeModel* model,
						 std::string volume_type,
						 const Vec3f& target, 
						 const Vec3f& launch_pos, 
						 const double& rot, 
						 const Vec3f& rotvec);
	~ProjectilePhysicsObj();
	virtual void Update();
	virtual void Render();
	void Fire(Vec3f target,Vec3f pos);
private:
	double m_rot_angle;
	Vec3f m_pos;
	Vec3f m_proj_forward;
	Vec3f m_rot_vec;
	Vec3f m_target;
	Vec3f m_launch_pos;
	float m_speed;
	Vec3f grav;
};

#endif