#include "pch.h"
#include "MouseMgr.h"

MOUSEINFO	MouseMgr::m_MouseInfo = { 0, };

MouseMgr::MouseMgr(void)
{

}

MouseMgr::~MouseMgr(void)
{
	
}

void MouseMgr::Init()
{
}

void MouseMgr::Render(Gdiplus::Graphics* MemG)
{

	//TODO
	string strName;
	switch (m_MouseInfo.unitID)
	{
	case UNIT_Knight:
		strName = "Knight";
		std::cout << "Knight±×¸®ÀÚ" << endl;
		load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\Knight.png"));
		MyUnit* knight = new MyUnit();
		knight->CopyObj((MyUnit*)ObjectManager::GetInstance().GetMyUnit(0),m_MouseInfo.ptTemp.x, m_MouseInfo.ptTemp.y);
		knight->ParentImg = load;
		Gdiplus::Rect Dst1(m_MouseInfo.ptTemp.x, m_MouseInfo.ptTemp.y, 50, 50);
		MemG->DrawImage(knight->ParentImg, Dst1);
		break;
	
	}
	
	

}
