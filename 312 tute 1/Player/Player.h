

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../includes.h"
#include "../Weapons/WeaponsManager.h"

class Player
{
public:
	Player();
	void Update(Vec3f pos, Vec3f aim_vec);
	void Attack();
	void Pick_up_weapon(Weapon* weapon);
	void Change_weapon(int i);
protected:
	Vec3f m_pos;
	Vec3f m_aim_vec;
	WeaponsManager m_weapons_mgr;
};

#endif