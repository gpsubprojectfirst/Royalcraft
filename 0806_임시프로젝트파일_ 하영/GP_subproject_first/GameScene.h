#pragma once
#include "Scene.h"
#include "MyMap.h"
#include "SearchTree.h"

class GameScene :
	public Scene
{ 
public:
	std::vector<Gdiplus::Image*>	m_vecGame;
	GameScene();
	MyMap* mMap;
	MapEditor* editor;
	SearchTree* mTree;
	bool bRender = false;
	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Release();
	void SendLButtonDown(UINT nFlags, CPoint point);
	
};



