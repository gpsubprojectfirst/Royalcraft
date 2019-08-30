#include "pch.h"
#include "UIElixirBar.h"

UIElixirBar::UIElixirBar()
	:font(_T("Times New Roman"), MY_FONT_SIZE, FontStyleBold, UnitPixel)
	,sbrush(Gdiplus::Color::White)
	,barRect(nullptr)
	,barImgRect(nullptr)
	,baseRect(nullptr)
	,elixirRect(nullptr)
	,tempRc(nullptr)
	,tempG(nullptr)
	,tempFRc(nullptr)
	,tempBitmap(nullptr)
	,result(nullptr)
	,full(100.0)
	,rate(0.0)
	,curGage(0.0)
	,AddDelta(0.0)
	,mycost(0)
{
	//Init();
}

void UIElixirBar::Init()
{
	full = GAGE_FULL;
	curGage = GAGE_EMPTY;
	mycost = 0;
	AddDelta = 0.0;

	barRect = new Gdiplus::Rect(ELIXIR_DISPLAY_X, ELIXIR_DISPLAY_Y, ELIXIR_DISPLAY_WIDTH, ELIXIR_DISPLAY_HEIGHT);
	this->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\Elixir.png"));

	tempBitmap = new Bitmap(barRect->Width, barRect->Height);
	tempG = new Gdiplus::Graphics(tempBitmap);
	tempRc = new Gdiplus::Rect(0, 0, barRect->Width, barRect->Height);
	tempFRc = new Gdiplus::RectF(ELIXIR_DISPLAY_X, ELIXIR_DISPLAY_Y + 5, ELIXIR_COUNT_WIDTH, ELIXIR_DISPLAY_HEIGHT);
	
	format.SetAlignment(StringAlignmentCenter);
	XmlManager::GetInstance().UIElixirBarParser(this);
}

void UIElixirBar::Update(float Delta)
{
	AddDelta += Delta;
	if (AddDelta > INCREASE_TIME_TERM)
	{
		if(curGage < full)
			curGage += INCREASE_GAGE_TERM;
		else if (curGage >= full)
			curGage = full;
		AddDelta = 0;
	}
	
	rate = curGage / full;

	mycost = (int)curGage / MAX_COST;
	if (curGage / GAGE_FULL >= 1)
		mycost = MAX_COST;
}
void UIElixirBar::Render(Gdiplus::Graphics* MemG)
{
	tempG->DrawImage(ParentImg, *tempRc, barImgRect->X, barImgRect->Y, barImgRect->Width, barImgRect->Height
		, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	tempRc->X = 0;
	tempRc->Y = 0;
	tempRc->Width = (int)(ELIXIR_DISPLAY_WIDTH * BASE_RECT_RATE);
	tempRc->Height = (int)(ELIXIR_DISPLAY_HEIGHT);
	tempG->DrawImage(ParentImg, *tempRc, baseRect->X, baseRect->Y, baseRect->Width, baseRect->Height
		, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	tempRc->X = (int)(barRect->Width * BASE_RECT_RATE);
	tempRc->Y = 1;
	tempRc->Width = (int)(ELIXIR_DISPLAY_WIDTH * rate * GAGE_RECT_RATE);
	tempRc->Height = (int)(ELIXIR_DISPLAY_HEIGHT);
	tempG->DrawImage(ParentImg, *tempRc, elixirRect->X, elixirRect->Y, elixirRect->Width, elixirRect->Height
		, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	
	tempstr = std::to_string(mycost);
	wide_string = wstring(tempstr.begin(), tempstr.end());
	result = wide_string.c_str();
	
	MemG->DrawImage(tempBitmap, *barRect);
	MemG->DrawString(result, -1, &font, *tempFRc, &format, &sbrush);

	EraseBmp();
}

void UIElixirBar::Release()
{
	delete barRect;
	delete baseRect;
	delete elixirRect;
	delete barImgRect;
	delete tempBitmap;
	delete tempG;
	delete tempRc;
	delete tempFRc;
}
void UIElixirBar::EraseBmp()
{
	tempRc->X = 0;
	tempRc->Y = 0;
	tempRc->Width = ELIXIR_DISPLAY_WIDTH;
	tempRc->Height = ELIXIR_DISPLAY_HEIGHT;

	tempG->SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceCopy);
	tempG->FillRectangle(&BRUSH_ERASE, *tempRc);
	tempG->SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceOver);
}
void UIElixirBar::spendCost(int n)
{
	mycost -= n;
	curGage -= n * MAX_COST;
}
 
