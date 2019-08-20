#include "pch.h"
#include "UIPopup.h"

 UIPopup::UIPopup()
{
	 Init();
}

 UIPopup::~UIPopup()
{
}

void UIPopup::Init()
{
	m_popupWnd = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\popup.png"));
	Gdiplus::Rect tempRC(0, 0, m_popupWnd->GetWidth(), m_popupWnd->GetHeight());
	this->rc = tempRC;

}

 void UIPopup::Update(float Delta)
{
	
}
void UIPopup::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;

	Gdiplus::Rect Dst1(REAL_WINSIZE_X / 2 - width/2, REAL_WINSIZE_Y / 2 - height/2, width, height);
	MemG->DrawImage(m_popupWnd, Dst1);
}