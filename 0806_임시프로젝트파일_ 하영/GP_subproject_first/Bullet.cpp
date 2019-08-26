#include "pch.h"
#include "bullet.h"

Bullet::Bullet()
{
	Init();
}

void Bullet::Init()
{
	Objtype = eObject_Bullet;
	curTile = std::make_pair(0, 0);
	dstTile = std::make_pair(0, 0);
	Isarrive = false;
}
void Bullet::Update(float Delta)
{
	if (target == nullptr)
	{
		Isarrive = true;
		return;
	}
	AddDelta += Delta;
	if (AddDelta > 0.01f)
	{
		frame++;
		AddDelta = 0;

		if (frame > 10)
			frame = 0;
	}
	float distanceX = target->curPosX - curPosX;
	float distanceY = target->curPosY - curPosY;

	int xvec = distanceX == 0 ? 0 : distanceX / abs(distanceX);
	int yvec = distanceY == 0 ? 0 : distanceY / abs(distanceY);

	
	curPosX += 5 * xvec;
	curPosY += 5 * yvec;

	int frame_ = frame % moveRc->size();
	rc = moveRc[0][frame_];
	if(target->posRc.Contains(curPosX,curPosY) || target->Isdead)
	{
		Isarrive = true;
	}
}
void Bullet::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;
	Gdiplus::Rect Dst1(curPosX - width / 2, curPosY - height / 2, width, height);
	Gdiplus::Bitmap* tempBmp = new Bitmap(width, height);
	Gdiplus::Graphics* tempG = new Gdiplus::Graphics(tempBmp);
	Gdiplus::Rect tempRc(0, 0, width, height);
	tempG->DrawImage(ParentImg, tempRc, rc.X, rc.Y, width, height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	if (ID == 1)
		tempBmp->RotateFlip(Rotate270FlipNone);

	//Gdiplus::Rect Dst1(posRc.X, posRc.Y, width /2, height / 2);
	MemG->DrawImage(tempBmp, Dst1, 0, 0, width, height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
	
	delete tempBmp;
	delete tempG;
}
void Bullet::Release()
{
	delete this;
}
void Bullet::ParserXML()
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	
	if (ID == 0)
	{
		doc->LoadFile("Xml\\bullet.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");

		//for (int i = 0; i < 13; i++)
		{
			moveRc[0].emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
		}
	}
	if (ID == 1)
	{
		doc->LoadFile("Xml\\bullet.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");

		for (int i = 0; i < 12; i++)
		{
			Node = Node->NextSiblingElement();
		}
		//for (int i = 12; i < 27; i++)
		{
			moveRc[0].emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
		}
	}
	if (ID == 2)
	{
		doc->LoadFile("Xml\\bullet.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		
		for (int i = 0; i < 26; i++)
		{
			Node = Node->NextSiblingElement();
		}
		moveRc[0].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
	}
	if (ID == 3)
	{
		doc->LoadFile("Xml\\bullet.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");

		for (int i = 0; i < 28; i++)
		{
			Node = Node->NextSiblingElement();
		}
		for (int i = 28; i < 86; i++)
		{
			moveRc[0].emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
			Node = Node->NextSiblingElement();
		}
	}

}
void Bullet::CopyObj(MyUnit* dst, int ix, int iy)
{
	ID = dst->ID;
	name = dst->name;
	mUnitInfo.move_speed = dst->mUnitInfo.move_speed;
	moveRc[0] = dst->moveRc[0];
	ParentImg = dst->ParentImg;
	curPosX = ix;
	curPosY = iy;
}
void Bullet::SetTarget(float srcx, float srcy, MyUnit* Intarget)
{
	curPosX = srcx;
	curPosY = srcy;

	target = Intarget;
}