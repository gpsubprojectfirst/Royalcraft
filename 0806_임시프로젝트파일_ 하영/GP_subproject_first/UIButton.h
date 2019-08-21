#pragma once
#include "Object.h"
class UIButton :
	public Object
{
private:
	Gdiplus::Image*	 m_ImgBefore;
	Gdiplus::Image*	 m_ImgAfter;
	int		 m_iBtnID;
	bool	 m_bColBtn;


public:
	virtual void Init(int btnID);
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);

public:
	UIButton();
	~UIButton();
};

