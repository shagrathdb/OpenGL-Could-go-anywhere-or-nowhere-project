
#include "WeaponsManager.h"

WeaponsManager::WeaponsManager()
{
}

void WeaponsManager::Add_weapon(Weapon* weapon)
{
	m_weapons.push_back(weapon);
	m_current_weapon = m_weapons.size()-1;
}


void WeaponsManager::Attack_current_weapon(Vec3f pos, Vec3f aim_vec)
{
	m_weapons[m_current_weapon]->Attack(pos,aim_vec);
}

void WeaponsManager::Change_weapon(int i)
{
	m_current_weapon = i;
}