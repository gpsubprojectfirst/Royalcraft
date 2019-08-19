#include "pch.h"
#include "ViewUnit.h"

ColorMatrix colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
						   0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
						   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

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
	{
		int width = rc.Width;
		int height = rc.Height;

		Gdiplus::Rect Dst1(curPos.X - width / 4, curPos.Y - height / 4, width / 2, height / 2);
		//Gdiplus::Rect Dst1(posRc.X, posRc.Y, width /2, height / 2);
		ImageAttributes imageAtt;
		imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault,
			ColorAdjustTypeBitmap);
		MemG->DrawImage(ParentImg, Dst1, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
			&imageAtt);
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
	
	curPos.X = ix;
	curPos.Y = iy;
}