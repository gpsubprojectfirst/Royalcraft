#include "pch.h"

ObjectManager::ObjectManager()
{
	//test unit knight
	MyUnit* knight = new MyUnit();
	knight->name = "knight";
	knight->ID = 0;
	knight->ParserXML();
	
	mObj.emplace_back(knight);
	UnitObj.emplace_back(knight);
}

Object* ObjectManager::GetObj(int InID)
{
	return mObj.at(InID);
}

MyUnit* ObjectManager::GetMyUnit(int InID)
{
	return UnitObj.at(InID);
}

//Object* CreateObj(EObject _obj_type,CString name,int ID)
//{
//	if (_obj_type == eObject_Unit)
//	{
//		MyUnit* newUnit = new MyUnit();
//		newUnit->name = name;
//		newUnit->ID = ID;
//		newUnit->Objtype = eObject_Unit;
//		return newUnit;
//	}
//	if (_obj_type == eObject_Build)
//	{
//		MyUnit* newUnit = new MyUnit();
//		newUnit->name = name;
//		newUnit->ID = ID;
//		newUnit->Objtype = eObject_Build;
//		return newUnit;
//	}
//	if (_obj_type == eObject_Bullet)
//	{
//		MyUnit* newUnit = new MyUnit();
//		newUnit->name = name;
//		newUnit->ID = ID;
//		newUnit->Objtype = eObject_Bullet;
//		return newUnit;
//	}
//	if (_obj_type == eObject_None)
//	{
//		Object* newObj = new Object();
//		newObj->name = name;
//		newObj->ID = ID;
//		return newObj;
//	}	
//}