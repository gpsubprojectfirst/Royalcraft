#include "pch.h"
#include "Deck.h"

Deck::Deck()
{
}

Deck::Deck(Gdiplus::Image* img)
{
	ParentImg = img;
}

Deck::~Deck()
{
}

void Deck::Init()
{
	
}

void Deck::CopyObj(int ix, int iy)
{

 	Gdiplus::Rect Dst(ix, iy, 72, 92);
	rc = Dst;
}

void Deck::Update(float Delta)
{
}

void Deck::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect Dst1(rc.X, rc.Y, rc.Width, rc.Height);
	MemG->DrawImage(ParentImg, Dst1);
}
