#include "pch.h"

ObjectManager::ObjectManager()
	: curObj(nullptr)
	, curUnit(nullptr)
{
	//test unit knight
	/*CString obj_name;
	obj_name =  "knight";*/
	MyUnit* knight = new MyUnit()
	knight->name = "knight";
	knight->ID = 0;
	//myUnit* knight = reinterpret_cast<myUnit*>(CreateObj(eObject_Unit, obj_name, 0));
	//parserXML(knight);

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

void parserXML(Object* obj)
{
	
}