#include "pch.h"
#include "XmlManager.h"

XmlManager::XmlManager()
	: doc(nullptr)
	,Root(nullptr)
	,Node(nullptr)
{
	
}
void XmlManager::Init()
{
	doc = new tinyxml2::XMLDocument();
}
void XmlManager::Release()
{
	delete doc;
}
void XmlManager::UnitParser(MyUnit* InUnit)
{
	EUnit_ID ID = (EUnit_ID)InUnit->ID;
	Init();
	if (ID == eUnit_Knight)
	{
		doc->LoadFile("Xml\\knight.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 12; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}

		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 14; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Axeman)
	{
		doc->LoadFile("Xml\\axeman.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 8; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 10; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Darknight)
	{
		doc->LoadFile("Xml\\darknight.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 10; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 8; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Electric)
	{
		doc->LoadFile("Xml\\electric.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 8; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}

		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 7; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Giant)
	{
		doc->LoadFile("Xml\\giant.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 16; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}

		// idle
		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 10; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Archer)
	{
		doc->LoadFile("Xml\\archer.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 8; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 5; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Lumberjack)
	{
		doc->LoadFile("Xml\\lumberjack.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 8; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 10; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Musket)
	{
		doc->LoadFile("Xml\\musket.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{

			for (int i = 0; i < 10; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 10; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Varkirey)
	{
		doc->LoadFile("Xml\\varkirey.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 8; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 12; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Vavarian)
	{
		doc->LoadFile("Xml\\vavarian.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 8; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 10; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Vendit)
	{
		doc->LoadFile("Xml\\vendit.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 8; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 8; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eUnit_Wizard)
	{
		doc->LoadFile("Xml\\wizard.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 8; i++)
			{
				InUnit->moveRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 7; i++)
			{
				InUnit->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	Release();
}
void XmlManager::BuildParser(Build* InBuild)
{
	EBuild_ID ID = (EBuild_ID)InBuild->ID;
	Init();
	if (ID == eBuild_RedKing)
	{
		doc->LoadFile("Xml\\kingtower.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");

		for (int i = 0; i < 13; i++)
		{
			InBuild->restRc.emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
			Node = Node->NextSiblingElement();
		}
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 3; i++)
			{
				InBuild->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eBuild_RedSubL || ID == eBuild_RedSubR)
	{
		doc->LoadFile("Xml\\subtower.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");

		//0
		InBuild->atkRc[0].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		//3
		InBuild->atkRc[1].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		//8
		InBuild->restRc.emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));

		//9
		InBuild->atkRc[2].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		//13
		InBuild->atkRc[3].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		//19
		InBuild->atkRc[4].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
	}
	if (ID == eBuild_BlueKing)
	{
		doc->LoadFile("Xml\\kingtowerblue.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		
		InBuild->restRc.emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		for (int direction = 0; direction < eDirection_Cnt; direction++)
		{
			for (int i = 0; i < 3; i++)
			{
				InBuild->atkRc[direction].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				

				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == eBuild_BlueSubL || ID == eBuild_BlueSubR)
	{
		doc->LoadFile("Xml\\subtowerblue.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");
		
		//0
		InBuild->atkRc[0].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		//3
		InBuild->atkRc[1].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		//9
		InBuild->atkRc[2].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		//13
		InBuild->atkRc[3].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		InBuild->restRc.emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		Node = Node->NextSiblingElement();
		//19
		InBuild->atkRc[4].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
	}
	Release();
}
void XmlManager::BulletParser(Bullet* InBullet)
{
	EBullet_ID ID = (EBullet_ID)InBullet->ID;
	Init();
	if (ID == eBullet_Fire)
	{
		doc->LoadFile("Xml\\bullet.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");

		//for (int i = 0; i < 13; i++)
		{
			InBullet->moveRc[0].emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
		}
	}
	if (ID == eBullet_Arrow)
	{
		doc->LoadFile("Xml\\bullet.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");

		for (int i = 0; i < 12; i++)
		{
			Node = Node->NextSiblingElement();
		}
		//for (int i = 12; i < 27; i++)
		{
			InBullet->moveRc[0].emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
		}
	}
	if (ID == eBullet_Bullet)
	{
		doc->LoadFile("Xml\\bullet.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");

		for (int i = 0; i < 26; i++)
		{
			Node = Node->NextSiblingElement();
		}
		InBullet->moveRc[0].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
	}
	if (ID == eBullet_Misile)
	{
		doc->LoadFile("Xml\\bullet.xml");
		this->Root = doc->RootElement();
		this->Node = Root->FirstChildElement("sprite");

		for (int i = 0; i < 28; i++)
		{
			Node = Node->NextSiblingElement();
		}
		for (int i = 28; i < 86; i++)
		{
			InBullet->moveRc[0].emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
			Node = Node->NextSiblingElement();
		}
	}

	Release();
}
void XmlManager::UnitInfoParser(std::vector<Object*>** objVector)
{
	Init();
	doc->LoadFile("Xml\\unitinfo.xml");
	this->Root = doc->RootElement();
	this->Node = Root->FirstChildElement("unit");
	tinyxml2::XMLElement* unitNode = Node->FirstChildElement("knight");
	for (int i = 0; i < eUnit_Cnt; i++)
	{//TODO
		tinyxml2::XMLElement* tempNode = unitNode->FirstChildElement("status");
		objVector[eObject_Unit]->at(i)->ID = unitNode->IntAttribute("ID");
		MyUnit* tempptr = (MyUnit*)objVector[eObject_Unit]->at(i);
		tempptr->mUnitInfo.hp = tempNode->IntAttribute("hp");
		tempptr->mUnitInfo.atk_type = (EAtkType)tempNode->IntAttribute("atk_type");
		tempptr->mUnitInfo.atk_speed = (int)tempNode->FloatAttribute("atk_speed");
		tempptr->mUnitInfo.move_speed = tempNode->FloatAttribute("move_speed");
		tempptr->mUnitInfo.cost = tempNode->IntAttribute("cost");
		tempptr->mUnitInfo.atk_distance = tempNode->IntAttribute("atk_distance");
		tempptr->mUnitInfo.damage = tempNode->IntAttribute("damage");

		unitNode = unitNode->NextSiblingElement();
	}
	Node = Node->NextSiblingElement("tower");
	tinyxml2::XMLElement* buildNode = Node->FirstChildElement("kingtower");

	for (int i = 0; i < eBuild_Cnt; i++)
	{
		tinyxml2::XMLElement* tempNode = buildNode->FirstChildElement("status");
		objVector[eObject_Build]->at(i)->ID = buildNode->IntAttribute("ID");
		Build* tempptr = (Build*)objVector[eObject_Build]->at(i);
		tempptr->mUnitInfo.hp = tempNode->IntAttribute("hp");
		tempptr->mUnitInfo.atk_type = (EAtkType)tempNode->IntAttribute("atk_type");
		tempptr->mUnitInfo.atk_speed = (int)tempNode->IntAttribute("atk_speed");
		tempptr->mUnitInfo.move_speed = tempNode->FloatAttribute("move_speed");
		tempptr->mUnitInfo.cost = tempNode->IntAttribute("cost");
		tempptr->mUnitInfo.atk_distance =tempNode->IntAttribute("atk_distance");
		tempptr->mUnitInfo.damage = tempNode->IntAttribute("damage");

		buildNode = buildNode->NextSiblingElement();
	}
	Release();
}
void XmlManager::UIHPBarParser(UIHPBar* InUI)
{
	Init();
	doc->LoadFile("Xml\\uiHp.xml");
	this->Root = doc->RootElement();
	this->Node = Root->FirstChildElement("Data");
	tinyxml2::XMLElement* subNode = Node->FirstChildElement("UV");

	float x = subNode->FloatAttribute("Left") * InUI->ParentImg->GetWidth();
	float y = subNode->FloatAttribute("Top") * InUI->ParentImg->GetHeight();
	float width = (subNode->FloatAttribute("Right") * InUI->ParentImg->GetWidth()) - x;
	float height = (subNode->FloatAttribute("Bottom") * InUI->ParentImg->GetHeight()) - y;

	InUI->baseRect = new Gdiplus::Rect((int)(x + 0.5f), (int)(y + 0.5f), (int)(width + 0.5f), (int)(height + 0.5f));

	subNode = subNode->NextSiblingElement();

	x = subNode->FloatAttribute("Left") * InUI->ParentImg->GetWidth();
	y = subNode->FloatAttribute("Top") * InUI->ParentImg->GetHeight();
	width = (subNode->FloatAttribute("Right") * InUI->ParentImg->GetWidth()) - x;
	height = (subNode->FloatAttribute("Bottom") * InUI->ParentImg->GetHeight()) - y;

	InUI->hpRect = new Gdiplus::Rect((int)(x + 0.5f), (int)(y + 0.5f), (int)(width + 0.5f), (int)(height + 0.5f));

	Release();
}
void XmlManager::UIElixirBarParser(UIElixirBar* InUI)
{
	Init();
	doc->LoadFile("Xml\\Elixir.xml");
	this->Root = doc->RootElement();
	this->Node = Root->FirstChildElement("Data");
	tinyxml2::XMLElement* subNode = Node->FirstChildElement("UV");

	float x = subNode->FloatAttribute("Left") * InUI->ParentImg->GetWidth();
	float y = subNode->FloatAttribute("Top") * InUI->ParentImg->GetHeight();
	float width = (subNode->FloatAttribute("Right") * InUI->ParentImg->GetWidth()) - x;
	float height = (subNode->FloatAttribute("Bottom") * InUI->ParentImg->GetHeight()) - y;

	InUI->baseRect = new Gdiplus::Rect((int)(x + 0.5f), (int)(y + 0.5f), (int)(width + 0.5f), (int)(height + 0.5f));

	subNode = subNode->NextSiblingElement();

	x = subNode->FloatAttribute("Left") * InUI->ParentImg->GetWidth();
	y = subNode->FloatAttribute("Top") * InUI->ParentImg->GetHeight();
	width = (subNode->FloatAttribute("Right") * InUI->ParentImg->GetWidth()) - x;
	height = (subNode->FloatAttribute("Bottom") * InUI->ParentImg->GetHeight()) - y;

	InUI->elixirRect = new Gdiplus::Rect((int)(x + 0.5f), (int)(y + 0.5f), (int)(width + 0.5f), (int)(height + 0.5f));

	subNode = subNode->NextSiblingElement();

	x = subNode->FloatAttribute("Left") * InUI->ParentImg->GetWidth();
	y = subNode->FloatAttribute("Top") * InUI->ParentImg->GetHeight();
	width = (subNode->FloatAttribute("Right") * InUI->ParentImg->GetWidth()) - x;
	height = (subNode->FloatAttribute("Bottom") * InUI->ParentImg->GetHeight()) - y;

	InUI->barImgRect = new Gdiplus::Rect((int)(x + 0.5f), (int)(y + 0.5f), (int)(width + 0.5f), (int)(height + 0.5f));

	Release();
}
