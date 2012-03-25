

#ifndef __PHYSOBJ_MANAGER__
#define __PHYSOBJ_MANAGER__

#include "PhysicsObj.h"
#include <vector>

class PhysicsObjManager
{
public:
	static PhysicsObjManager* Instance();

	~PhysicsObjManager();

	void Update();

	void Add_obj(PhysicsObj* obj);

	bool Remove_obj(int i);

	void Render_all();

private:
	PhysicsObjManager();

	static PhysicsObjManager* m_Instance;

	std::vector<PhysicsObj*> m_PhysicsObjs;
};

#endif