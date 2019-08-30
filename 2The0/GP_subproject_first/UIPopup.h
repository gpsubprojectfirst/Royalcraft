#pragma once
#include "Object.h"
#include "UIButton.h"
class UIPopup :
	public Object
{
private:
	Gdiplus::Image*			m_popupWnd;
	std::vector<UIButton*>		m_vecPopup;

public:
	virtual void Init(void);
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	void CreateButton(void);

public:
	UIPopup();
	~UIPopup();
};

