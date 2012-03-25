
#include "BallShooter.h"
#include "../PhysicsObject/PhysicsObjManager.h"
#include "../PhysicsObject/ProjectilePhysicsObj.h"
#include "../3DModel/Ball.h"

BallShooter::BallShooter()
{
	Vec3f temp(0,0,1);
    m_proj_forward = temp;
}

void BallShooter::Attack(Vec3f pos, Vec3f aim_vec)
{
	m_pos = pos;
	m_aim_vec = aim_vec;

	Vec3f heading;

    heading.x = m_aim_vec.x - m_pos.x;
    heading.y = m_aim_vec.y - m_pos.y;
    heading.z = m_aim_vec.z - m_pos.z;

    heading.Normalise();

	m_pos+=heading*1.5;

	static BallModel* ball = new BallModel;

	Vec3f rotate = m_proj_forward.Cross(heading);

        // Calculate the angle between the two std::vectors
        double angle = acos(m_proj_forward.Dot(m_proj_forward,heading));

        // Convert the angle to radians
        angle = angle * (180.0/3.14159265358979);

        // Add the object to the container of all of the world's objects
		PhysicsObjManager::Instance()->Add_obj(new ProjectilePhysicsObj
												   (ball,
												    "sphere",
													heading,
													m_pos,
													angle,rotate));
}