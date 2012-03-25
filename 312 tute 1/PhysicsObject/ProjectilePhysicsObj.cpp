
#include "ProjectilePhysicsObj.h"


ProjectilePhysicsObj::
ProjectilePhysicsObj(FreeDeeModel* model,
					 std::string volume_type,
					 const Vec3f& target, 
					 const Vec3f& launch_pos, 
					 const double& rot, 
					 const Vec3f& rotvec)
{
	m_3d_model   = model;
    m_target     = target;
	m_launch_pos = launch_pos;
    m_pos        = launch_pos;
	m_rot_angle  = rot;
    m_rot_vec    = rotvec;
	m_speed		 = 0.45;
	Vec3f temp(0,0,1);
    m_proj_forward = temp;
	grav = Vec3f(0,-0.1,0);
    m_target.Normalise();
}

ProjectilePhysicsObj::~ProjectilePhysicsObj()
{
	m_3d_model = NULL;
	delete [] m_3d_model;
}



void ProjectilePhysicsObj::Update()
{
	
	m_pos += m_target * m_speed;
	m_pos += grav;
	
	grav*=1.008;
}

float rot = 0.5;
void ProjectilePhysicsObj::Render()
{
	glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
		glRotatef(m_rot_angle, m_rot_vec.x, m_rot_vec.y, m_rot_vec.z);
		glRotatef(rot++,1,0,0);
		m_3d_model->Render();
	glPopMatrix();
}
