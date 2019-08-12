#include "pch.h"

ObjectManager::ObjectManager()
	: curObj(nullptr)
	, curUnit(nullptr)
{
	//test unit knight
	myUnit* knight = new myUnit();
	knight->name = "knight";
	knight->ID = 0;
	knight->parserXML();
	
	mObj.emplace_back(knight);
	UnitObj.emplace_back(knight);
}

Object* ObjectManager::GetObj(int InID)
{
	return mObj.at(InID);
}

myUnit* ObjectManager::GetMyUnit(int InID)
{
	return UnitObj.at(InID);
}

Object* CreateObj(EObject _obj_type,CString name,int ID)
{
	if (_obj_type == eObject_Unit)
	{
		myUnit* newUnit = new myUnit();
		newUnit->name = name;
		newUnit->ID = ID;
		newUnit->Objtype = eObject_Unit;
		return newUnit;
	}
	if (_obj_type == eObject_Build)
	{
		myUnit* newUnit = new myUnit();
		newUnit->name = name;
		newUnit->ID = ID;
		newUnit->Objtype = eObject_Build;
		return newUnit;
	}
	if (_obj_type == eObject_Bullet)
	{
		myUnit* newUnit = new myUnit();
		newUnit->name = name;
		newUnit->ID = ID;
		newUnit->Objtype = eObject_Bullet;
		return newUnit;
	}
	if (_obj_type == eObject_None)
	{
		Object* newObj = new Object();
		newObj->name = name;
		newObj->ID = ID;
		return newObj;
	}	
}