#pragma once
#include "Object.h"
class UITime :
	public Object
{
public:
	UITime();
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Release();
	bool IsEndTime();
	int timeMinuite;
	int timeSecond;
	int runTime;
	float AddDelta;
	Gdiplus::RectF* displayRc;
};