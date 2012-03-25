
#ifndef __PROJECTILE_WEP_H__
#define __PROJECTILE_WEP_H__

#include "Weapon.h"

class ProjectileWeapon : public Weapon
{
public:
	virtual void Attack(Vec3f pos, Vec3f aim_vec) = 0;
};

#endif