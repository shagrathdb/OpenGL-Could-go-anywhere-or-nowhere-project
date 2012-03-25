
#ifndef __BALLSHOOTER_H__
#define __BALLSHOOTER_H__

#include "ProjectileWeapon.h"

class BallShooter : public ProjectileWeapon
{
public:
	BallShooter();
	virtual void Attack(Vec3f pos, Vec3f aim_vec);
};

#endif