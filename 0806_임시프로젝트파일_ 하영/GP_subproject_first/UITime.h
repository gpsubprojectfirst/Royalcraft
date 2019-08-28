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
	Gdiplus::Font font; 
	Gdiplus::SolidBrush sbrush;
	Gdiplus::Pen pen;
	Gdiplus::StringFormat format;
	std::string minStr;
	std::string secStr;
	std::string timeStr;
	std::wstring wide_string;
	const WCHAR* result;
	Gdiplus::RectF* displayRc;
};