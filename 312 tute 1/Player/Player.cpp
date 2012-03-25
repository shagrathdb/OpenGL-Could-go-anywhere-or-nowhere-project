
#include "Player.h"


Player::Player()
{

}

void Player::Update(Vec3f pos, Vec3f aim_vec)
{
	m_pos	  = pos;
	m_aim_vec = aim_vec;
}

void Player::Attack()
{
	m_weapons_mgr.Attack_current_weapon(m_pos, m_aim_vec);
}

void Player::Pick_up_weapon(Weapon* weapon)
{
	m_weapons_mgr.Add_weapon(weapon);
}

void Player::Change_weapon(int i)
{
	m_weapons_mgr.Change_weapon(i);
}