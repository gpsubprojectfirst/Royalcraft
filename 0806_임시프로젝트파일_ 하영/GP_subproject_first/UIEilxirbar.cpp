#include "pch.h"
#include "UIElixirBar.h"

UIElixirBar::UIElixirBar()
{
	Init();
}

void UIElixirBar::Init()
{
	full = 100.0;
	curGage = 0.0;
	mycost = 0;
	AddDelta = 0.0;
	barRect = new Gdiplus::Rect(160, 900, 385, 60);
	this->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\Elixir.png"));

	XmlManager::GetInstance().UIElixirBarParser(this);
}

void UIElixirBar::Update(float Delta)
{
	AddDelta += Delta;
	if (AddDelta > 0.01f)
	{
		if(curGage < full)
			curGage += 0.1f;
		else if (curGage >= full)
			curGage = full;
		AddDelta = 0;
	}
	
	rate = curGage / full;

	mycost = (int)curGage / 10;
	if (curGage / 100.0 >= 1)
		mycost = 10;
}
void UIElixirBar::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Bitmap* tempBitmap = new Bitmap(barRect->Width, barRect->Height);
	Gdiplus::Graphics* tempG = new Gdiplus::Graphics(tempBitmap);
	Gdiplus::Rect* tempRc = new Gdiplus::Rect(0, 0, barRect->Width, barRect->Height);
	
	tempG->DrawImage(ParentImg, *tempRc, barImgRect->X, barImgRect->Y, barImgRect->Width, barImgRect->Height
		, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	tempRc->X = 0;
	tempRc->Y = 0;
	tempRc->Width = barRect->Width * 0.2;
	tempRc->Height = barRect->Height;
	tempG->DrawImage(ParentImg, *tempRc, baseRect->X, baseRect->Y, baseRect->Width, baseRect->Height
		, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	tempRc->X = barRect->Width * 0.2;
	tempRc->Y = 1;
	tempRc->Width = barRect->Width * rate * 0.8;
	tempRc->Height = barRect->Height;
	tempG->DrawImage(ParentImg, *tempRc, elixirRect->X, elixirRect->Y, elixirRect->Width, elixirRect->Height
		, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	
	Gdiplus::Font font(_T("Times New Roman"), 30, FontStyleBold, UnitPixel);
	SolidBrush sbrush(Gdiplus::Color::Black);
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	string tempstr = std::to_string(mycost);
	wstring wide_string = wstring(tempstr.begin(), tempstr.end());
	const WCHAR* result = wide_string.c_str();
	Gdiplus::RectF* tempFRc = new Gdiplus::RectF(150, 920, 80, 30);
	MemG->DrawImage(tempBitmap, *barRect);
	MemG->DrawString(result, -1, &font, *tempFRc, &format, &sbrush);


}

void UIElixirBar::spendCost(int n)
{
	mycost -= n;
	curGage -= n * 10;
}
 