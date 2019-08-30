#include "pch.h"
#include "Deck.h"

Deck::Deck()
	: costImg(TEXT("Asset\\3.game\\4.ui\\uicost.png"))
	, costRc(0, 0, 0, 0)
	, tempFRc(0,0,0,0)
	, font(_T("Times New Roman"), MY_FONT_SIZE_SMALL, FontStyleBold, UnitPixel)
	, sbrush(Gdiplus::Color::White)
	, typeNum(EDeck_Knight)
	, m_iCost(0)
{
}

Deck::Deck(Gdiplus::Image* img, int cost)
	: costImg(TEXT("Asset\\3.game\\4.ui\\uicost.png"))
	, costRc(0, 0, 0, 0)
	, font(_T("Times New Roman"), MY_FONT_SIZE_SMALL, FontStyleBold, UnitPixel)
	, sbrush(Gdiplus::Color::White)
	, typeNum(EDeck_Knight)
	, m_iCost(0)
{
	ParentImg = img;
	m_iCost = cost;
}

Deck::~Deck()
{
}

void Deck::Init()
{
	
}

void Deck::Update(float Delta)
{
}

void Deck::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect Dst1(int(m_tInfo.fX), int(m_tInfo.fY), int(m_tInfo.fSizeX), int(m_tInfo.fSizeY));

	costRc.X = Dst1.X + SLOT_SIZE_WIDTH - 30;
	costRc.Y = Dst1.Y + SLOT_SIZE_HEIGHT - 30;
	costRc.Width = COST_VIEW_WIDTH;
	costRc.Height = COST_VIEW_HEIGHT;
	
	tempFRc.X =Gdiplus::REAL(Dst1.X + SLOT_SIZE_WIDTH - 13);
	tempFRc.Y = Gdiplus::REAL(Dst1.Y + SLOT_SIZE_HEIGHT - 15);
	tempFRc.Width = Gdiplus::REAL(costRc.Width);
	tempFRc.Height = Gdiplus::REAL(costRc.Height);

	tempstr = std::to_string(m_iCost);
	wide_string = wstring(tempstr.begin(), tempstr.end());
	const WCHAR* result = wide_string.c_str();

	MemG->DrawImage(ParentImg, Dst1);
	MemG->DrawImage(&costImg, costRc);
	MemG->DrawString(result, -1, &font, tempFRc, &format, &sbrush);
}
