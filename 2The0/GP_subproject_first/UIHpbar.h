#pragma once
#include "Object.h"

class UIHPBar : public Object
{
public:
	UIHPBar();
	void Init();
	void SetPos(MyUnit* unitptr);
	void calcRate(float Inhp,int ID,EObject Intype);
	void EraseBmp();
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Release();
	float fullHp;
	float curHp;
	float rate;

	Gdiplus::Rect* barRect;
	Gdiplus::Rect* baseRect;
	Gdiplus::Rect* hpRect;

	Gdiplus::Bitmap* tempBitmap;
	Gdiplus::Graphics* tempG;
	Gdiplus::Rect* tempRc;
	COORD UnitPos;
};