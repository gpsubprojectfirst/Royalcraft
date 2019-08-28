#include "pch.h"
#include "UITime.h"

UITime::UITime()
	: font(_T("Times New Roman"), MY_FONT_SIZE, FontStyleBold, UnitPixel)
	,sbrush(Gdiplus::Color::Black)
	,pen(Gdiplus::Color::Black)
	,timeMinuite(0)
	,timeSecond(0)
	,runTime(0)
	,AddDelta(0.0)
	,result(nullptr)
	,displayRc(nullptr)
{
	//Init();
}

void UITime::Init()
{
	displayRc = new RectF(TIME_DISPLAY_X,TIME_DISPLAY_Y, TIME_DISPLAY_WIDTH, TIME_DISPLAY_HEIGHT);
	//시간설정
	timeMinuite = TIME_MAX_MINUITE;
	timeSecond = TIME_MAX_SECOND;
	AddDelta = 0;
	runTime = 0;
	format.SetAlignment(StringAlignmentCenter);
}

void UITime::Update(float Delta)
{
	AddDelta += Delta;
	if (AddDelta > 1.0f)
	{
		timeSecond--;
		runTime++;
		AddDelta = 0;
	}
	if (timeSecond < 0)
	{
		timeMinuite--;
		timeSecond += 60; // 1min = 60 sec
	}
}

void UITime::Render(Gdiplus::Graphics* MemG)
{
	
	minStr = std::to_string(timeMinuite);
	secStr = std::to_string(timeSecond);
	timeStr = minStr + " : " + secStr;
	wide_string = wstring(timeStr.begin(), timeStr.end());
	result = wide_string.c_str();

	MemG->DrawRectangle(&pen, *displayRc);
	MemG->DrawString(result,-1,&font,*displayRc,&format,&sbrush);
}

void UITime::Release()
{
	SAFE_DELETE(result);
	SAFE_DELETE(displayRc);
}

bool UITime::IsEndTime()
{
	if (timeMinuite < 0 )
		return true;
	return false;
}