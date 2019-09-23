#pragma once
#include "Scene.h"

class LogoScene :
	public Scene
{
public:
	LogoScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	virtual void Release();
};

