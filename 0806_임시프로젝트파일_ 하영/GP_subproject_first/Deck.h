#pragma once
#include "Object.h"
class Deck :
	public Object
{
private:
	Gdiplus::Image* profile;
	
public:
	void CopyObj(int ix, int iy);

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);

	EDeck_type typeNum;
	int				  m_iCost;
public:
	Deck();
	Deck(Gdiplus::Image* img, int cost);
	~Deck();
};

