#pragma once
#include "Scene.h"
#include "myMap.h"
#include "SearchTree.h"

class GameScene :
	public Scene
{ 
public:
	std::vector<Gdiplus::Image*>	m_vecGame;
	GameScene();
	myMap* mMap;
	SearchTree mTree;
	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	void Release();
	void SendLButtonDown(UINT nFlags, CPoint point);
	
};



