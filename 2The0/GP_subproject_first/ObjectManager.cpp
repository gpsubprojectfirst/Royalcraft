#include "pch.h"

ObjectManager::ObjectManager()
{
	for (int i = 0; i < eUnit_Cnt; i++)
	{
		MyUnit* mUnit = new  MyUnit();
		mUnit->ID = i;
		XmlManager::GetInstance().UnitParser(mUnit);
		//mUnit->ParserXML();
		mObj[eObject_Unit].emplace_back(mUnit);
	}
	for (int i = 0; i < eBuild_Cnt; i++)
	{
		Build* tower = new Build();
		tower->ID = i;
		XmlManager::GetInstance().BuildParser(tower);
		//tower->ParserXML();
		mObj[eObject_Build].emplace_back(tower);
	}
	Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\bullet.png"));
	for (int i = 0; i < eBullet_Cnt; i++)
	{
		Bullet* arrow = new Bullet();
		arrow->ID = i;
		XmlManager::GetInstance().BulletParser(arrow);
		//arrow->ParserXML();
		arrow->ParentImg = load;
		mObj[eObject_Bullet].emplace_back(arrow);
	}

	XmlManager::GetInstance().UnitInfoParser(mObj);
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
Object* ObjectManager::GetBullet(int InID)
{
	return mObj[eObject_Bullet].at(InID);
}