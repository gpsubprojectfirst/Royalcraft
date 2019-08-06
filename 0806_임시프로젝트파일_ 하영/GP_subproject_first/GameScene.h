#pragma once
#include "Scene.h"

class GameScene :
	public Scene
{
public:
	CImage* bgImg;
	GameScene();

	void Init();
	void Update(float Delta, int frame);
	void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	void Release();
};



