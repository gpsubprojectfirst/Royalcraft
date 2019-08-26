#pragma once
#include "Scene.h"
class LogoScene :
	public Scene
{

public:
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Release();

	LogoScene();
	~LogoScene();
};

