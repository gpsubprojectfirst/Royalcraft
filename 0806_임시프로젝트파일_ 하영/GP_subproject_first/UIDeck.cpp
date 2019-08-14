#include "pch.h"
#include "UIDeck.h"


UIDeck::UIDeck()
{
	Init();
}

UIDeck::~UIDeck()
{
	Release();
}

void UIDeck::Init()
{
	img = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\knigth_profile.png"));
	for (int i = 0; i < 4; ++i)
	{
		m_tDeckInfo[i].bCanUse = true;
		m_tDeckInfo[i].iCoolTIme = 0;

	}
}

void UIDeck::Update(float Delta)
{
	
}

void UIDeck::Render(Gdiplus::Graphics* MemG)
{
	//167,808 slot1 Knight
	Gdiplus::Pen pen(Color(255,0,0),10.0f);
	MemG->DrawRectangle(&pen, 167, 808, 72, 92);


	//Knight Image
	Gdiplus::Rect rc(167, 808, 72, 92);
	MemG->DrawImage(img, rc);

	
}

void UIDeck::Release()
{
}

