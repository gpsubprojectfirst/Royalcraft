#pragma once
#include "Scene.h"
class LogoScene :
	public Scene
{
public:
	LogoScene();

	void Init();
	void Update(float Delta, int frame);
	void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	void Release();
};

