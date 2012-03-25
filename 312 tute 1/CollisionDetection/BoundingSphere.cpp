
#include "BoundingSphere .h"


BoundingSphere::BoundingSphere(float radius)
{
	m_type			= "sphere";
	m_sphere_radius = radius;
}
std::string BoundingSphere::Get_type()const
{
	return m_type;
}
float BoundingSphere::Get_Bounding_Sphere_radius()const
{
	return m_sphere_radius;
}