#include "pch.h"
#include "MouseMgr.h"

MOUSEINFO	MouseMgr::m_MouseInfo = { 0, };

MouseMgr::MouseMgr(void)
{

 	Init();
}

MouseMgr::~MouseMgr(void)
{
	
}

void MouseMgr::Init()
{
	
}

void MouseMgr::Render(Gdiplus::Graphics* MemG)
{

}

int MouseMgr::GetUnitID()
{
	return m_MouseInfo.unitID;
}