#include "pch.h"

ObjectManager::ObjectManager()
{
	//ÀüÃ¼ À¯´Ö ÆÄ½Ì
	for (int i = 0; i < 12; i++)
	{
		MyUnit* mUnit = new MyUnit();
		mUnit->ID = i;
		mUnit->ParserXML();
		mObj[eObject_Unit].emplace_back(mUnit);
	}
	for (int i = 0; i < 3; i++)
	{
		Build* tower = new Build();
		tower->ID = i;
		tower->ParserXML();
		mObj[eObject_Build].emplace_back(tower);
	}
	
}

Object* ObjectManager::GetObj(int InID)
{
	return mObj[eObject_Cnt - 1].at(InID);
}

Object* ObjectManager::GetMyUnit(int InID)
{
	return mObj[eObject_Unit].at(InID);
}
Object* ObjectManager::GetBuild(int InID)
{
	return mObj[eObject_Build].at(InID);
}