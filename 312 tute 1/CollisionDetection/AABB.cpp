
#include "AABB.h"

AABB::AABB(float height, float width, float length)
{
	m_type = "AABB";
}

std::string AABB::Get_type()const
{
	return m_type;
}

float* AABB::Get_vertices(int i)
{
	return m_vertices[i];
}

float AABB::Get_Bounding_Sphere_radius()const
{
	return m_vertices[7].Distance(m_vertices[7],Vec3f(0,0,0));
}