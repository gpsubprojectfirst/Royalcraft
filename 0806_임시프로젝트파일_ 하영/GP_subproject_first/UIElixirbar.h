#pragma once
#include "Object.h"

class UIElixirbar : public Object
{
public:
	UIElixirbar();
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	void spendCost(int n);
	float full;
	float curGage;
	float rate;
	float AddDelta;

	int mycost;

	Gdiplus::Rect* barRect;
	Gdiplus::Rect* baseRect;
	Gdiplus::Rect* elixirRect;
	Gdiplus::Rect* barImgRect;
};