#include "pch.h"
#include "ViewUnit.h"

ViewUnit::ViewUnit()
	: Object(EObject::eObject_Unit)
{
	
}

ViewUnit::~ViewUnit()
{

}
void ViewUnit::Update(float Delta)
{
	posRc.X = MouseMgr::GetInstance().GetMousePos().x;
	posRc.Y = MouseMgr::GetInstance().GetMousePos().y;
}

void ViewUnit::Render(Gdiplus::Graphics* MemG)
{
	//if (!Isdead)
	{
		int width = rc.Width;
		int height = rc.Height;

		Gdiplus::Rect Dst1(posRc.X, posRc.Y, width, height);
		MemG->DrawImage(ParentImg, Dst1, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}
void ViewUnit::CopyObj(MyUnit* dst, int ix, int iy)
{
	ID = dst->ID;
	name = dst->name;
	for (int i = 0; i < 5; i++)
	{
		moveRc[i] = dst->moveRc[i];
	}
	
	rc = moveRc[4][0];
	
	Gdiplus::Rect Dst(ix, iy, ix + 50, iy + 50);
	posRc = Dst;
}