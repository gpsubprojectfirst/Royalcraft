#pragma once
#include "Scene.h"

class LobbyScene :
	public Scene
{
public:
	CImage* bgImg;
	LobbyScene();

	void Init();
	void Update(float Delta, int frame);
	void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	void Release();
};


