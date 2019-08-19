#include "pch.h"

Build::Build()
{
	Objtype = eObject_Build;
	curTile = std::make_pair(0, 0);
	
	hp = 500;
	move_speed = 0;
	atk_distance = 300;
	damage = 45;
	Isdead = false;

	sm.Add(new State_Idle);
	sm.Add(new State_Attack);
}

void Build::Update(float Delta)
{
	if (!Isdead)
	{
		AddDelta += Delta;
		if (AddDelta > 0.1f)
		{
			frame++;
			AddDelta = 0;

			if (frame > 10)
				frame = 0;
		}
		UnitBt->Tick();
		if (sm.GetCurState() == eState_Idle)
		{
			int frame_ = frame % restRc.size();
			rc = restRc[frame_];
		}
		else if (sm.GetCurState() == eState_Attack)
		{
			int frame_ = frame % atkRc.size();
			rc = atkRc[frame_];
		}
		else if (sm.GetCurState() == eState_Dead)
		{
			//rc = atkRc[0];
		}
	}
}
void Build::Render(Gdiplus::Graphics* MemG)
{
	if (!Isdead)
	{
		int width = rc.Width;
		int height = rc.Height;

		Gdiplus::Rect Dst1(curPos.X - width / 4, curPos.Y - height / 4 , width /2, height/2);
		//Gdiplus::Rect Dst1(posRc.X, posRc.Y, width /2, height / 2);
		MemG->DrawImage(ParentImg, Dst1, rc.X, rc.Y, width,height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}
void Build::ParserXML()
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	if (ID == 0)
	{
		doc->LoadFile("Xml\\kingtower.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");

		for (int i = 0; i < 13; i++)
		{
			restRc.emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
			Node = Node->NextSiblingElement();
		}
		for (int i = 0; i < 15 ; i++)
		{
			atkRc.emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
			Node = Node->NextSiblingElement();
		}
	}
	if (ID == 1 || ID == 2)
	{
		doc->LoadFile("Xml\\subtower.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");

		for (int i = 0; i < 17; i++)
		{
			restRc.emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
			atkRc.emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));

			Node = Node->NextSiblingElement();
		}
	}
}
void Build::CopyObj(MyUnit* dst, int ix, int iy)
{
	
	ID = dst->ID;
	name - dst->name;

	atkRc = dst->atkRc;
	restRc = ((Build*)dst)->restRc;
	curPos.X = ix;
	curPos.Y = iy;
}

void Build::CreateBT(BlackBoard* InBB)
{
	UnitBt = new BehaviorTree(this, InBB);
	UnitBt->InitTower(this, InBB);
}

void Build::Rest(float Delta)
{

}