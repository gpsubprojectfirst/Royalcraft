#include "pch.h"
#include "UIPopup.h"

 UIPopup::UIPopup()
	 :m_popupWnd(nullptr)
{
	// Init();
}

 UIPopup::~UIPopup()
{
}

void UIPopup::Init()
{
	m_popupWnd = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\popup.png"));
	Gdiplus::Rect tempRC(0, 0, m_popupWnd->GetWidth(), m_popupWnd->GetHeight());
	this->ParentImg = m_popupWnd;
	this->rc = tempRC;

	CreateButton();

}

 void UIPopup::Update(float Delta)
{
	 for (auto& it : this->m_vecPopup)
	 {
		 if (it == nullptr) continue;
		 if (it->Enable == false) continue;

		 it->Update(Delta);
	 }
}

void UIPopup::Render(Gdiplus::Graphics* MemG)
{
	//popup wnd
	int width = rc.Width;
	int height = rc.Height;

	Gdiplus::Rect Dst1(REAL_WINSIZE_X / 2 - width/2, REAL_WINSIZE_Y / 2 - height/2, width, height);
	MemG->DrawImage(ParentImg, Dst1);

	for (auto& it : this->m_vecPopup)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		it->Render(MemG);
	}
}

void UIPopup::CreateButton()
{
	for (int i = 0; i < 2; ++i)
	{
		UIButton* pBtn = new UIButton();
		pBtn->Init(i);
		float fx = float((this->rc.Width / 4 + 10) + 200 *  ( i ));
		float fy = REAL_WINSIZE_Y / 2 - 30;
		Gdiplus::Rect tempRC(fx, fy, pBtn->ParentImg->GetWidth(), pBtn->ParentImg->GetHeight());
		pBtn->m_tInfo.fX = fx;
		pBtn->m_tInfo.fY = fy;
		pBtn->m_tInfo.fSizeX = (float)pBtn->ParentImg->GetWidth();
		pBtn->m_tInfo.fSizeY = (float)pBtn->ParentImg->GetHeight();
		pBtn->rc = tempRC;

		m_vecPopup.push_back(pBtn);
	}
}