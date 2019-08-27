#include"pch.h"
#include "UIHPBar.h"

UIHPBar::UIHPBar()
{
	//Init();
}

void UIHPBar::Init()
{
	barRect = new Rect(0,0, HP_BAR_WIDTH, HP_BAR_HEIGHT);
	this->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\uihp.png"));
	tempBitmap = new Bitmap(HP_BAR_WIDTH, HP_BAR_HEIGHT);
	tempG = new Gdiplus::Graphics(tempBitmap);
	tempRc = new Rect(0, 0, HP_BAR_WIDTH * BASE_RECT_RATE, HP_BAR_HEIGHT);
	XmlManager::GetInstance().UIHPBarParser(this);
}

void UIHPBar::SetPos(MyUnit* unitptr)
{
	UnitPos.X = unitptr->curPosX;
	UnitPos.Y = unitptr->curPosY;

	barRect->X = UnitPos.X - 60;
	barRect->Y = UnitPos.Y - 60;
	barRect->Width = HP_BAR_WIDTH;
	barRect->Height = HP_BAR_HEIGHT;

}
void UIHPBar::calcRate(int Inhp,int ID,EObject Intype)
{
	if(Intype == eObject_Unit)
		fullHp = ((MyUnit*)ObjectManager::GetInstance().GetMyUnit(ID))->mUnitInfo.hp;
	if(Intype == eObject_Build)
		fullHp = ((Build*)ObjectManager::GetInstance().GetBuild(ID))->mUnitInfo.hp;
	curHp = Inhp;
	rate = (curHp / fullHp);
}
void UIHPBar::Render(Gdiplus::Graphics* MemG) 
{
	for (auto it : ((GameScene*)SceneManager::GetInstance().GetCurScene())->playUnit)
	{
		if (it == nullptr) continue;
		if (!it->Isdead)
		{
			SetPos(it);
			calcRate(it->mUnitInfo.hp, it->ID,it->Objtype);

			tempRc->X = barRect->Width * BASE_RECT_RATE;
			tempRc->Y = 0;
			tempRc->Width = barRect->Width * rate * GAGE_RECT_RATE;
			tempRc->Height = barRect->Height;

			tempG->DrawImage(ParentImg, *tempRc, hpRect->X, hpRect->Y, hpRect->Width, hpRect->Height
				, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

			tempRc->X = 0;
			tempRc->Y = 0;
			tempRc->Width = barRect->Width * BASE_RECT_RATE;
			tempRc->Height = barRect->Height;

			tempG->DrawImage(ParentImg, *tempRc, baseRect->X, baseRect->Y, baseRect->Width, baseRect->Height
				, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

			MemG->DrawImage(tempBitmap, *barRect);
			
			EraseBmp();
		}
	}
}
void UIHPBar::EraseBmp()
{
	tempRc->X = 0;
	tempRc->Y = 0;
	tempRc->Width = HP_BAR_WIDTH;
	tempRc->Height = HP_BAR_HEIGHT;
	tempG->SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceCopy);
	tempG->FillRectangle(&BRUSH_ERASE, *tempRc);
	tempG->SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceOver);
}

void UIHPBar::Release()
{

}