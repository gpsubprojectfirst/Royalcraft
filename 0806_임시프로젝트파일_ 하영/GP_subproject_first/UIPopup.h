#pragma once
#include "Object.h"
class UIPopup :
	public Object
{
private:
	Gdiplus::Image*		m_popupWnd;

public:
	virtual void Init(void);
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);

public:
	UIPopup();
	~UIPopup();
};

