
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "../includes.h"

class Weapon
{
public:
	virtual void Attack(Vec3f pos, Vec3f aim_vec) = 0;
protected:
    Vec3f m_proj_forward;
	Vec3f m_pos;
	Vec3f m_aim_vec;
};

#endif