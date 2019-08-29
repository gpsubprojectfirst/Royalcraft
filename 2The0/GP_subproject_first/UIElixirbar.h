#pragma once
#include "pch.h"
#include "Object.h"

class UIElixirBar : public Object
{
public:
	UIElixirBar();
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Release();
	void spendCost(int n);
	void EraseBmp();
	float full;
	float curGage;
	float rate;
	float AddDelta;

	int mycost;

	Gdiplus::Rect* barRect;
	Gdiplus::Rect* baseRect;
	Gdiplus::Rect* elixirRect;
	Gdiplus::Rect* barImgRect;
	Gdiplus::Bitmap* tempBitmap;
	Gdiplus::Graphics* tempG;
	Gdiplus::Rect* tempRc;
	Gdiplus::RectF* tempFRc;
	//
	Gdiplus::Font font;
	Gdiplus::SolidBrush sbrush;
	Gdiplus::StringFormat format;
	std::string tempstr;
	std::wstring wide_string;
	const WCHAR* result;

};