#include "pch.h"

ObjectManager::ObjectManager()
	: curObj(nullptr)
	, curUnit(nullptr)
{
	//test unit knight
	MyUnit* knight = new MyUnit();

	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile("Xml\\knight.xml");

	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");

	for (int i = 0; i < 12; i++)
	{
		knight->moveRc.emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
	}
	for (int i = 12; i < 117; i++)
	{
		Node = Node->NextSiblingElement();
	}
	for (int i = 117; i < 131; i++)
	{
		knight->atkRc.emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
	}

	knight->ID = 0;
	knight->name = "knight";

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