#pragma once
#include "Object.h"
class UIButton :
	public Object
{
private:
	Gdiplus::Image* m_popupWnd;

public:
	virtual void Init(void);
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);

public:
	UIButton();
	~UIButton();
};

