#pragma once
#include "pch.h"
#include "SingleTon.h"
#include <afxwin2.inl>



class MouseMgr : 
	public SingleTon< MouseMgr>
{
private:
	 static MOUSEINFO	m_MouseInfo;

	 Gdiplus::Image* load;
public:
	static inline POINT GetMousePos(void)
	{
		POINT	pt;
		GetCursorPos(&pt);
		::ScreenToClient(AfxGetMainWnd()->GetSafeHwnd(), &pt);
		
		return pt;
	}

	static void SetMouseInfo(MOUSEINFO _mouseInfo) { m_MouseInfo = _mouseInfo; }

	MOUSEINFO& GetMouseInfo() { return m_MouseInfo; }

	void Init();
	void Render(Gdiplus::Graphics* MemG);
	
public:
	MouseMgr();
	~MouseMgr();
};

