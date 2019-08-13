#pragma once
#include "SingleTon.h"
#include "state.h"


class ObjectManager 
	: public SingleTon<ObjectManager>
{
public:
	ObjectManager();
	Object* GetObj(int n);

	MyUnit* GetMyUnit(int n);

	//Object* CreateObj(EObject _obj_type, CString name, int ID);
	//static ObjectManager& GetInstance();
	//void Update(float Delta);
private:
	std::vector<Object*> mObj;
	std::vector<MyUnit*> UnitObj;
};
