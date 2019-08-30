#pragma once
#include "Scene.h"

class LobbyScene :
	public Scene
{
public:
	LobbyScene();
	~LobbyScene();

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void CreateButton();
	void Release();
};


