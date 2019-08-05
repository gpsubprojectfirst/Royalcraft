#include "pch.h"

ObjectManager::ObjectManager()
	: curObj(nullptr)
	, curUnit(nullptr)
{
	//test unit knight
	myUnit* knight = new myUnit();

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

myUnit* ObjectManager::GetMyUnit(int InID)
{
	return UnitObj.at(InID);
}
Object::Object()
	: Objtype(eObject_None)
	, Enable(true)
	,ID(0)
	,ParentImg(nullptr)
{

};
Object::Object(EObject InType)
	:Objtype(InType)
	, Enable(true)
	, ID(0)
	, ParentImg(nullptr)
{

}
Object::~Object()
{

}

myUnit::myUnit()
	: Object(EObject::eObject_Unit)
{
	sm.Add(new State_Idle);
	sm.Add(new State_Move);
	sm.Add(new State_Attack);
}
void myUnit::Update(float Delta)
{

}

