

#ifndef __CUBOID_H__
#define __CUBOID_H__

#include "SimpleModel.h"

class Cuboid : public SimpleModel
{
public:
	Cuboid(float height, float width, float length)
	{
		m_vertices[0] = Vec3f(0-width/2,0-height/2,0+length/2);

		m_vertices[1] = Vec3f(0+width/2,0-height/2,0+length/2);

		m_vertices[2] = Vec3f(0+width/2,0+height/2,0+length/2);

		m_vertices[3]= Vec3f(0-width/2,0+height/2,0+length/2);

		m_vertices[4]= Vec3f(0+width/2,0-height/2,0-length/2);

		m_vertices[5]= Vec3f(0-width/2,0-height/2,0-length/2);

		m_vertices[6]= Vec3f(0-width/2,0+height/2,0-length/2);

		m_vertices[7]= Vec3f(0+width/2,0+height/2,0-length/2);
	}

	virtual float Get_Bounding_Sphere_radius()const
	{
		return m_vertices[7].Distance(m_vertices[7],Vec3f(0,0,0));
	}

	virtual void Render()
	{
		glPushMatrix();
		glColor3f(0,1,0);
		glNormal3f(0,0,1);
		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[0]);
			glVertex3fv(m_vertices[1]);
			glVertex3fv(m_vertices[3]);
		glEnd();

		glNormal3f(0,0,1);
		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[1]);
			glVertex3fv(m_vertices[2]);
			glVertex3fv(m_vertices[3]);
		glEnd();

		glNormal3f(0,0,-1);
		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[4]);
			glVertex3fv(m_vertices[5]);
			glVertex3fv(m_vertices[7]);
		glEnd();

		glNormal3f(0,0,-1);
		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[5]);
			glVertex3fv(m_vertices[6]);
			glVertex3fv(m_vertices[7]);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[1]);
			glVertex3fv(m_vertices[4]);
			glVertex3fv(m_vertices[2]);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[4]);
			glVertex3fv(m_vertices[7]);
			glVertex3fv(m_vertices[2]);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[5]);
			glVertex3fv(m_vertices[0]);
			glVertex3fv(m_vertices[6]);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[0]);
			glVertex3fv(m_vertices[3]);
			glVertex3fv(m_vertices[6]);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[3]);
			glVertex3fv(m_vertices[2]);
			glVertex3fv(m_vertices[6]);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[2]);
			glVertex3fv(m_vertices[7]);
			glVertex3fv(m_vertices[6]);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[5]);
			glVertex3fv(m_vertices[4]);
			glVertex3fv(m_vertices[0]);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3fv(m_vertices[4]);
			glVertex3fv(m_vertices[1]);
			glVertex3fv(m_vertices[0]);
		glEnd();

		glPopMatrix();
	}
private:
	Vec3f m_vertices[8];
};

#endif