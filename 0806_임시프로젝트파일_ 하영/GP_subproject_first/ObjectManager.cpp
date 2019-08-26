#include "pch.h"

ObjectManager::ObjectManager()
{
	//전체 유닛 파싱
	for (int i = 0; i < eUnit_Cnt; i++)
	{
		MyUnit* mUnit = new MyUnit();
		mUnit->ID = i;
		mUnit->ParserXML();
		mObj[eObject_Unit].emplace_back(mUnit);
	}
	for (int i = 0; i < eBuild_Cnt; i++)
	{
		Build* tower = new Build();
		tower->ID = i;
		tower->ParserXML();
		mObj[eObject_Build].emplace_back(tower);
	}
	/* 0- 불, 1- 화살, 2- 대포, 3- 미사일*/
	Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\bullet.png"));
	for (int i = 0; i < eBullet_Cnt; i++)
	{
		Bullet* arrow = new Bullet();
		arrow->ID = i;
		arrow->ParserXML();
		arrow->ParentImg = load;
		mObj[eObject_Bullet].emplace_back(arrow);
	}
	UnitInfoParser();
}

void ObjectManager::UnitInfoParser()
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile("Xml\\unitinfo.xml");
	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* Node = Root->FirstChildElement("unit");
	tinyxml2::XMLElement* unitNode = Node->FirstChildElement("knight");
	
	for (int i = 0; i < eUnit_Cnt; i++)
	{
		tinyxml2::XMLElement* tempNode = unitNode->FirstChildElement("status");
		mObj[eObject_Unit].at(i)->ID = unitNode->IntAttribute("ID");
		MyUnit* tempptr = (MyUnit*)mObj[eObject_Unit].at(i);
		tempptr->mUnitInfo.hp = tempNode->IntAttribute("hp");
		tempptr->mUnitInfo.atk_type = (EAtkType)tempNode->IntAttribute("atk_type");
		tempptr->mUnitInfo.atk_speed = tempNode->FloatAttribute("atk_speed");
		tempptr->mUnitInfo.move_speed = tempNode->FloatAttribute("move_speed");
		tempptr->mUnitInfo.cost = tempNode->IntAttribute("cost");
		tempptr->mUnitInfo.atk_distance = tempNode->FloatAttribute("atk_distance");
		tempptr->mUnitInfo.damage = tempNode->IntAttribute("damage");
		
		unitNode = unitNode->NextSiblingElement();
	}
	Node = Node->NextSiblingElement("tower");
	tinyxml2::XMLElement* buildNode = Node->FirstChildElement("kingtower");

	for (int i = 0; i < eBuild_Cnt; i++)
	{
		tinyxml2::XMLElement* tempNode = buildNode->FirstChildElement("status");
		mObj[eObject_Build].at(i)->ID = buildNode->IntAttribute("ID");
		Build* tempptr = (Build*)mObj[eObject_Build].at(i);
		tempptr->mUnitInfo.hp = tempNode->IntAttribute("hp");
		tempptr->mUnitInfo.atk_type = (EAtkType)tempNode->IntAttribute("atk_type");
		tempptr->mUnitInfo.atk_speed = tempNode->FloatAttribute("atk_speed");
		tempptr->mUnitInfo.move_speed = tempNode->FloatAttribute("move_speed");
		tempptr->mUnitInfo.cost = tempNode->IntAttribute("cost");
		tempptr->mUnitInfo.atk_distance = tempNode->FloatAttribute("atk_distance");
		tempptr->mUnitInfo.damage = tempNode->IntAttribute("damage");

		buildNode = buildNode->NextSiblingElement();
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
Object* ObjectManager::GetBullet(int InID)
{
	return mObj[eObject_Bullet].at(InID);
}