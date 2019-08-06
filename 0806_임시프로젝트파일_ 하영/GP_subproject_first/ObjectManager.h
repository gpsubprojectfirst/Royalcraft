#pragma once
#include "SingleTon.h"
#include "state.h"


class ObjectManager 
	: public SingleTon<ObjectManager>
{
public:
	ObjectManager();
	Object* GetObj(int n);
	myUnit* GetMyUnit(int n);
	//static ObjectManager& GetInstance();
	//void Update(float Delta);
private:
	std::vector<Object*> mObj;
	std::vector<myUnit*> UnitObj;
	Object* curObj;
	myUnit* curUnit;
};
