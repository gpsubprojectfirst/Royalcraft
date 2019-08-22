#include "pch.h"
#include "UITime.h"

UITime::UITime() 
{
	Init();
}

void UITime::Init()
{
	displayRc = new RectF(REAL_WINSIZE_X - 100, 0, 100, 30);
	//시간설정
	timeMinuite = 2;
	timeSecond = 30;
	AddDelta = 0;
	runTime = 0;
}

void UITime::Update(float Delta)
{
	AddDelta += Delta;
	if (AddDelta > 1.0f)
	{
		timeSecond--;
		AddDelta = 0;
	}
	if (timeSecond < 0)
	{
		timeMinuite--;
		timeSecond += 60;
	}
}

void UITime::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Font font(_T("Times New Roman"), 30, FontStyleBold, UnitPixel);
	SolidBrush sbrush(Gdiplus::Color::Black);
	Pen pen(Gdiplus::Color::Black);
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	string minstr = std::to_string(timeMinuite);
	string secstr = std::to_string(timeSecond);
	string s = minstr +" : "+ secstr;
	wstring wide_string = wstring(s.begin(), s.end());
	const WCHAR* result = wide_string.c_str();
	MemG->DrawRectangle(&pen, *displayRc);
	MemG->DrawString(result,-1,&font,*displayRc,&format,&sbrush);
}

void UITime::Release()
{

}

bool UITime::IsEndTime()
{
	if (timeMinuite < 0 )
		return true;
	return false;
}