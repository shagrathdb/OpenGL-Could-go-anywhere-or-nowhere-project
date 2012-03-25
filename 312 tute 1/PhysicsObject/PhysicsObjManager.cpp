#include "PhysicsObjManager.h"


PhysicsObjManager* PhysicsObjManager::m_Instance = NULL;


PhysicsObjManager* PhysicsObjManager::Instance()
{
	if(m_Instance==NULL)
	{
		m_Instance = new PhysicsObjManager;
	}
	return m_Instance;
}

PhysicsObjManager::PhysicsObjManager()
{

}

PhysicsObjManager::~PhysicsObjManager()
{
	m_Instance = NULL;

	delete [] m_Instance;
}

void PhysicsObjManager::Update()
{
	for(int i=0;i<m_PhysicsObjs.size();i++)
	{
		m_PhysicsObjs[i]->Update();
	}
}

void PhysicsObjManager::Add_obj(PhysicsObj* obj)
{
	m_PhysicsObjs.push_back(obj);
}

bool PhysicsObjManager::Remove_obj(int i)
{
	return true;

}

void PhysicsObjManager::Render_all()
{
	for(int i=0;i<m_PhysicsObjs.size();i++)
	{
		m_PhysicsObjs[i]->Render();
	}
}