#pragma once
#include "Scene.h"
#include "MyMap.h"
#include "SearchTree.h"

class GameScene :
	public Scene
{ 
public:
	std::vector<Gdiplus::Image*>	m_vecGame;
	MyMap* mMap;
	MapEditor* editor;
	SearchTree* mTree;
	MyUnit* knight;
	bool bRender = false;


public:
	GameScene();
	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Release();

	void CreateObj(int ix, int iy);
	void SendLButtonDown(UINT nFlags, CPoint point);
};



