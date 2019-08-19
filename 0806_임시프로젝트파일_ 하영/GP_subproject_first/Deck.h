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
public:
	Deck();
	Deck(Gdiplus::Image* img);
	~Deck();
};

