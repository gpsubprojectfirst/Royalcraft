#pragma once

class Object;

class Scene
{
	protected:
	std::vector<Object*>						vecInfo[EScene_End];
	std::vector<Gdiplus::Image*>		m_vecImg[EScene_End];
	Gdiplus::Bitmap*							backBuffer;
	Gdiplus::Rect									m_rcDst;
	Gdiplus::Image*							m_imgDst;

public:
	CString Name;

public:
	virtual void Init() {}
	virtual void Update(float Delta) {}
	virtual void Render(Gdiplus::Graphics* MemG) {}
	virtual void Release() {}
	virtual void GetBuffer(Gdiplus::Bitmap* MemG) {}
	virtual void SendLButtonDown(UINT nFlags, CPoint point) {}

	Scene();
	~Scene();

	
};



