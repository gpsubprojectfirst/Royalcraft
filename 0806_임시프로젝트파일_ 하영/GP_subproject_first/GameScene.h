#pragma once
#include "Scene.h"
#include "myMap.h"
class GameScene :
	public Scene
{
public:
	std::vector<Gdiplus::Image*>	m_vecGame;
	GameScene();
	myMap mMap;

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	void Release();

	void SendLButtonDown(UINT nFlags, CPoint point);
	
};



