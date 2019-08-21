#pragma once
#include "Object.h"

class UIHpbar : public Object
{
public:
	UIHpbar();
	void Init();
	void SetPos(MyUnit* unitptr);
	void calcRate(int Inhp,int ID,EObject Intype);
	virtual void Render(Gdiplus::Graphics* MemG);

	int fullHp;
	int curHp;
	float rate;

	Gdiplus::Rect* barRect;
	Gdiplus::Rect* baseRect;
	Gdiplus::Rect* hpRect;
	COORD UnitPos;
};