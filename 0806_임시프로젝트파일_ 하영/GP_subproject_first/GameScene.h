#pragma once
#include "Scene.h"
#include "MyMap.h"
#include "SearchTree.h"
#include "Command.h"


class GameScene :
	public Scene
{ 
public:
	std::vector<Gdiplus::Image*>	m_vecGame;
	MyMap* mMap;
	MapEditor* editor;
	SearchTree* mTree;
	Command CommandQueue;
	MyUnit* knight;
	std::vector<MyUnit> playUnit;
	BlackBoard* blackBoard;
	bool bRender = false;

public:
	GameScene();
	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Release();

	void CreateObj(CPoint pt);
	void SendLButtonDown(UINT nFlags, CPoint point);

};



