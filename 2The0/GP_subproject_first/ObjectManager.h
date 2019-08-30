#pragma once
#include "SingleTon.h"
#include "state.h"


class ObjectManager 
	: public SingleTon<ObjectManager>
{
public:
	ObjectManager();

	Object* GetObj(int n);
	Object* GetMyUnit(int n);
	Object* GetBuild(int n);
	Object* GetBullet(int n);
private:
	std::vector<Object*> mObj[eObject_Cnt];
};