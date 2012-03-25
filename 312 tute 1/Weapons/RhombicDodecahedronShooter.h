
#ifndef __RHOMBIC_SHOOTER_H__
#define __RHOMBIC_SHOOTER_H__

#include "ProjectileWeapon.h"

class RhombicDodecahedronShooter : public ProjectileWeapon
{
public:
	RhombicDodecahedronShooter();
	void RhombicDodecahedronShooter::Attack(Vec3f pos, Vec3f aim_vec);
};

#endif