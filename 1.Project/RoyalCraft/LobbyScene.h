#pragma once
#include "Scene.h"
class LobbyScene :
	public Scene
{
public:
	CImage* bgImg;
	LobbyScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	virtual void Release();
};

