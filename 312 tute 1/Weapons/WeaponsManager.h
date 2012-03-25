

#ifndef __WPNS_MGR_H__
#define __WPNS_MGR_H__

#include "Weapon.h"
#include <vector>

class WeaponsManager
{
public:
	WeaponsManager();
	void Update();
	void Add_weapon(Weapon* weapon);
	void Attack_current_weapon(Vec3f pos, Vec3f aim_vec);
	void Change_weapon(int i);
private:
	std::vector<Weapon*> m_weapons;
	int m_current_weapon;
};

#endif