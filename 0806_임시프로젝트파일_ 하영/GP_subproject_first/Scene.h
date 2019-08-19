#pragma once

class Object;
class Scene
{

public:
	bool bLoop;
	CString Name;
	std::vector<Object*> info;
	Gdiplus::Image* img;
	Gdiplus::Bitmap* backBuffer;
public:
	virtual void Init() {}
	virtual void Update(float Delta) {}
	virtual void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/) {}
	virtual void Release() {}
	virtual void GetBuffer(Gdiplus::Bitmap* MemG) {}
	virtual void SendLButtonDown(UINT nFlags, CPoint point) {}
};



