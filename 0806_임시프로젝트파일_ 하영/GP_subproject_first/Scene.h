#pragma once

class Object;
class Scene
{

public:
	bool bLoop;
	CString Name;
	std::vector<Object*> info;
	Gdiplus::Image* img;

public:
	virtual void Init() {}
	virtual void Update(float Delta) {}
	virtual void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/) {}
	virtual void Release() {}

	virtual void SendLButtonDown(UINT nFlags, CPoint point) {}
};



