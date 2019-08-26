#include "pch.h"
#include "Deck.h"

Deck::Deck()
{
}

Deck::Deck(Gdiplus::Image* img, int cost)
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
	Gdiplus::Rect Dst1(m_tInfo.fX, m_tInfo.fY, m_tInfo.fSizeX, m_tInfo.fSizeY);
	MemG->DrawImage(ParentImg, Dst1);
}
