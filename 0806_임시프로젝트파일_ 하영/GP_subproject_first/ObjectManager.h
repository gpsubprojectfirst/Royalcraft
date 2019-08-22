#pragma once
#include "SingleTon.h"
#include "state.h"


class ObjectManager 
	: public SingleTon<ObjectManager>
{
public:
	ObjectManager();

	void UnitInfoParser();
	Object* GetObj(int n);
	Object* GetMyUnit(int n);
	Object* GetBuild(int n);
	Object* GetBullet(int n);
	//Object* CreateObj(EObject _obj_type, CString name, int ID);
	//static ObjectManager& GetInstance();
	//void Update(float Delta);
private:
	std::vector<Object*> mObj[eObject_Cnt];
	//std::vector<MyUnit*> UnitObj;
};
