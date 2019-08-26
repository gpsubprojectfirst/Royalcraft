#pragma once
#include "Object.h"
class Deck :
	public Object
{
public:
	EDeck_type		  typeNum;
	int				  m_iCost;

public:
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);

public:
	Deck();
	Deck(Gdiplus::Image* img, int cost);
	~Deck();
};

