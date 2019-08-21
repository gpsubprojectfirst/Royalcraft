#include"pch.h"
#include "UIHpbar.h"

UIHpbar::UIHpbar()
{
	Init();
}

void UIHpbar::Init()
{
	barRect = new Rect(0,0,0,0);
	this->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\uihp.png"));

	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile("Xml\\uiHp.xml");
	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* Node = Root->FirstChildElement("Data");
	tinyxml2::XMLElement* subNode = Node->FirstChildElement("UV");

	float x = subNode->FloatAttribute("Left") * ParentImg->GetWidth();
	float y = subNode->FloatAttribute("Top") * ParentImg->GetHeight();
	float width = (subNode->FloatAttribute("Right") * ParentImg->GetWidth()) - x;
	float height =(subNode->FloatAttribute("Bottom") * ParentImg->GetHeight()) - y;
	

	baseRect = new Gdiplus::Rect((int)(x + 0.5f), (int)(y + 0.5f), (int)(width + 0.5f), (int)(height + 0.5f));
	
	subNode = subNode->NextSiblingElement();

	x = subNode->FloatAttribute("Left") * ParentImg->GetWidth();
	y = subNode->FloatAttribute("Top") * ParentImg->GetHeight();
	width = (subNode->FloatAttribute("Right") * ParentImg->GetWidth()) - x;
	height =(subNode->FloatAttribute("Bottom") * ParentImg->GetHeight()) - y;

	hpRect = new Gdiplus::Rect((int)(x + 0.5f), (int)(y + 0.5f), (int)(width + 0.5f), (int)(height + 0.5f));

}

void UIHpbar::SetPos(MyUnit* unitptr)
{
	UnitPos.X = unitptr->curPos.X;
	UnitPos.Y = unitptr->curPos.Y;

	barRect->X = UnitPos.X - 60;
	barRect->Y = UnitPos.Y - 60;
	barRect->Width = 100;
	barRect->Height = 20;

}
void UIHpbar::calcRate(int Inhp,int ID,EObject Intype)
{
	if(Intype == eObject_Unit)
		fullHp = ((MyUnit*)ObjectManager::GetInstance().GetMyUnit(ID))->mUnitInfo.hp;
	if(Intype == eObject_Build)
		fullHp = ((Build*)ObjectManager::GetInstance().GetBuild(ID))->mUnitInfo.hp;
	curHp = Inhp;
	rate = ((float)curHp / (float)fullHp);
	/*
	std::cout << "curHp" <<curHp << endl;
	std::cout << "full" << fullHp << endl;
	std::cout << "rate" << rate << endl;*/
}
void UIHpbar::Render(Gdiplus::Graphics* MemG) 
{
	for (auto it : ((GameScene*)SceneManager::GetInstance().GetCurScene())->playUnit)
	{
		if (!it->Isdead)
		{
			SetPos(it);
			calcRate(it->mUnitInfo.hp, it->ID,it->Objtype);
			Gdiplus::Bitmap* tempBitmap = new Bitmap(barRect->Width, barRect->Height);
			Gdiplus::Graphics* tempG = new Gdiplus::Graphics(tempBitmap);
			Gdiplus::Rect* tempRc = new Rect(0, 0, barRect->Width * 0.2, barRect->Height);
			tempG->DrawImage(ParentImg, *tempRc, baseRect->X, baseRect->Y, baseRect->Width, baseRect->Height
				, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
			tempRc = new Rect(barRect->Width * 0.2, 0, barRect->Width * rate, barRect->Height);
			tempG->DrawImage(ParentImg, *tempRc, hpRect->X, hpRect->Y, hpRect->Width, hpRect->Height
				, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

			MemG->DrawImage(tempBitmap, *barRect);
		}
	}
}