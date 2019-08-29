#pragma once
#include "pch.h"
#include "Object.h"
class Deck :
	public Object
{
public:
	EDeck_type		  typeNum;
	int						  m_iCost;
	Gdiplus::Image	  costImg;
	Gdiplus::Rect	  costRc;
	Gdiplus::RectF tempFRc;
	Gdiplus::Font font;
	Gdiplus::SolidBrush sbrush;
	Gdiplus::StringFormat format;
	std::string tempstr;
	std::wstring wide_string;


public:
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);

public:
	Deck();
	Deck(Gdiplus::Image* img, int cost);
	~Deck();
};

