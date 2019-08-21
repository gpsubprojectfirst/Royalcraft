#include "pch.h"
#include "UIButton.h"

UIButton::UIButton()
{
}

UIButton::~UIButton()
{

}
void UIButton::Init()
{
	//클릭전 
	btnImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\gameend.png"));
	Gdiplus::Rect tempRC(0, 0, btnImg->GetWidth(), btnImg->GetHeight());
	this->ParentImg = btnImg;
	this->rc = tempRC;
	
	//클릭후
	btnImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\gameend2.png"));
	Gdiplus::Rect tempRC(0, 0, btnImg->GetWidth(), btnImg->GetHeight());
	
}

void UIButton::Update(float Delta)
{
	
}

void UIButton::Render(Gdiplus::Graphics* MemG)
{
	
	int width = rc.Width;
	int height = rc.Height;

	Gdiplus::Rect Dst1(REAL_WINSIZE_X / 2 - width / 2, REAL_WINSIZE_Y / 2 - height / 2, width, height);
	MemG->DrawImage(ParentImg, Dst1);

}