#pragma once
#include "Scene.h"
#include "myMap.h"
class GameScene :
	public Scene
{
public:
	Gdiplus::Image* bgImg;
	GameScene();
	myMap* mMap;

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	void Release();

	void SendLButtonDown(UINT nFlags, CPoint point);
	
};



