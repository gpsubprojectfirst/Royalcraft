#pragma once
class Scene
{

public:
	bool bLoop;
	CString Name;
	std::vector<Object*> info;
	Gdiplus::Image* img;

public:
	std::vector<Gdiplus::Image*>	m_vecImg;

	virtual void Init() {}
	virtual void Update(float Delta) {}
	virtual void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/) {}
	virtual void Release() {}

	virtual void SendLButtonDown(UINT nFlags, CPoint point) {}
};



