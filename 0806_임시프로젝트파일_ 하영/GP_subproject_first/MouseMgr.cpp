#include "pch.h"
#include "MouseMgr.h"

MOUSEINFO	MouseMgr::m_MouseInfo = { 0, };

ColorMatrix colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
						   0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
						   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };


MyUnit* knight;
MouseMgr::MouseMgr(void)
{

 	Init();
}

MouseMgr::~MouseMgr(void)
{
	
}

void MouseMgr::Init()
{
	load = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\knigth_profile.png"));
	knight = new MyUnit();
	knight->CopyObj((MyUnit*)ObjectManager::GetInstance().GetMyUnit(0), m_MouseInfo.ptTemp.x, m_MouseInfo.ptTemp.y);
	knight->ParentImg = load;

}

void MouseMgr::Render(Gdiplus::Graphics* MemG)
{

	//TODO
	string strName;
	switch (m_MouseInfo.unitID)
	{
	case UNIT_Knight:
		strName = "Knight";

		Gdiplus::Rect Dst1(m_MouseInfo.ptTemp.x, m_MouseInfo.ptTemp.y, 50, 50);
		ImageAttributes imageAtt;
		imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault,
			ColorAdjustTypeBitmap);
		MemG->DrawImage(knight->ParentImg, Dst1, 0, 0, knight->ParentImg->GetWidth(), knight->ParentImg->GetHeight(), UnitPixel, &imageAtt);
		//knight->Render(MemG);
		break;
	
	}
	
	

}
