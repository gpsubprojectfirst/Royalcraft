#include"pch.h"
#include "UIHPBar.h"

UIHPBar::UIHPBar()
{
	Init();
}

void UIHPBar::Init()
{
	barRect = new Rect(0,0,0,0);
	this->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\uihp.png"));
	XmlManager::GetInstance().UIHPBarParser(this);
}

void UIHPBar::SetPos(MyUnit* unitptr)
{
	UnitPos.X = unitptr->curPosX;
	UnitPos.Y = unitptr->curPosY;

	barRect->X = UnitPos.X - 60;
	barRect->Y = UnitPos.Y - 60;
	barRect->Width = 100;
	barRect->Height = 20;

}
void UIHPBar::calcRate(int Inhp,int ID,EObject Intype)
{
	if(Intype == eObject_Unit)
		fullHp = ((MyUnit*)ObjectManager::GetInstance().GetMyUnit(ID))->mUnitInfo.hp;
	if(Intype == eObject_Build)
		fullHp = ((Build*)ObjectManager::GetInstance().GetBuild(ID))->mUnitInfo.hp;
	curHp = Inhp;
	rate = (curHp / fullHp);
	/*
	std::cout << "curHp" <<curHp << endl;
	std::cout << "full" << fullHp << endl;
	std::cout << "rate" << rate << endl;*/
}
void UIHPBar::Render(Gdiplus::Graphics* MemG) 
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
			tempRc = new Rect(barRect->Width * 0.2, 0, barRect->Width * rate * 0.8, barRect->Height);
			tempG->DrawImage(ParentImg, *tempRc, hpRect->X, hpRect->Y, hpRect->Width, hpRect->Height
				, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

			MemG->DrawImage(tempBitmap, *barRect);
		}
	}
}