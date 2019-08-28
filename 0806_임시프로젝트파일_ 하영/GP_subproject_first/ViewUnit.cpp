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
	int width = rc.Width;
	int height = rc.Height;

	Gdiplus::Rect Dst1(MouseMgr::GetInstance().GetMousePos().x - width / 4, MouseMgr::GetInstance().GetMousePos().y - height /4 , width /2, height / 2);
	
	ImageAttributes imageAtt;
	imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);
	MemG->DrawImage(ParentImg, Dst1, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
		&imageAtt);

}

void ViewUnit::CopyObj(MyUnit* dst, int ix, int iy)
{
	ID = dst->ID;
	name = dst->name;
	rc = dst->moveRc[eDirection_Top][0];
	
}