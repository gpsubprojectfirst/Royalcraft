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
	UnitInfoParser();
}

void ObjectManager::UnitInfoParser()
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile("Xml\\unitinfo.xml");
	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* Node = Root->FirstChildElement("unit");
	tinyxml2::XMLElement* unitNode = Node->FirstChildElement("knight");
	
	for (int i = 0; i < 12; i++)
	{
		tinyxml2::XMLElement* tempNode = unitNode->FirstChildElement("status");
		mObj[eObject_Unit].at(i)->ID = unitNode->IntAttribute("ID");
		((MyUnit*)mObj[eObject_Unit].at(i))->mUnitInfo.hp = tempNode->IntAttribute("hp");
		((MyUnit*)mObj[eObject_Unit].at(i))->mUnitInfo.atk_type = (EAtkType)tempNode->IntAttribute("atk_type");
		((MyUnit*)mObj[eObject_Unit].at(i))->mUnitInfo.atk_speed = tempNode->FloatAttribute("atk_speed");
		((MyUnit*)mObj[eObject_Unit].at(i))->mUnitInfo.move_speed = tempNode->FloatAttribute("move_speed");
		((MyUnit*)mObj[eObject_Unit].at(i))->mUnitInfo.cost = tempNode->IntAttribute("cost");
		((MyUnit*)mObj[eObject_Unit].at(i))->mUnitInfo.atk_distance = tempNode->FloatAttribute("atk_distance");
		((MyUnit*)mObj[eObject_Unit].at(i))->mUnitInfo.damage = tempNode->IntAttribute("damage");
		
		unitNode = unitNode->NextSiblingElement();
	}
	Node = Node->NextSiblingElement("tower");
	tinyxml2::XMLElement* buildNode = Node->FirstChildElement("kingtower");

	for (int i = 0; i < 3; i++)
	{
		tinyxml2::XMLElement* tempNode = buildNode->FirstChildElement("status");
		mObj[eObject_Build].at(i)->ID = buildNode->IntAttribute("ID");
		((Build*)mObj[eObject_Build].at(i))->mUnitInfo.hp = tempNode->IntAttribute("hp");
		((Build*)mObj[eObject_Build].at(i))->mUnitInfo.atk_type = (EAtkType)tempNode->IntAttribute("atk_type");
		((Build*)mObj[eObject_Build].at(i))->mUnitInfo.atk_speed = tempNode->FloatAttribute("atk_speed");
		((Build*)mObj[eObject_Build].at(i))->mUnitInfo.move_speed = tempNode->FloatAttribute("move_speed");
		((Build*)mObj[eObject_Build].at(i))->mUnitInfo.cost = tempNode->IntAttribute("cost");
		((Build*)mObj[eObject_Build].at(i))->mUnitInfo.atk_distance = tempNode->FloatAttribute("atk_distance");
		((Build*)mObj[eObject_Build].at(i))->mUnitInfo.damage = tempNode->IntAttribute("damage");

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