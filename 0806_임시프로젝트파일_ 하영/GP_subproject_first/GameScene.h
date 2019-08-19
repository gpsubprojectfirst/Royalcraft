#pragma once
#include "Scene.h"
#include "MyMap.h"
#include "SearchTree.h"
#include "Command.h"
#include "UICrown.h"

class GameScene :
	public Scene
{ 
public:
	std::vector<Gdiplus::Image*>	m_vecGame;

	MyMap* mMap;
	MapEditor* editor;
	SearchTree* mTree;
	Command CommandQueue;
	std::vector<MyUnit*> playUnit;
	BlackBoard* blackBoard;
	bool bRender = false;
	bool m_IsSelectMode;
	bool m_Renderflag;
	bool endflag;

	//끝났을 때 에니메이션을 위한 변수
	UICrown* endUI;
public:

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Release();

	void GetBuffer(Gdiplus::Bitmap* _Buffer);
	void grayscale(int width, int height, Gdiplus::BitmapData& pData);
	void CreateObj(CPoint pt);
	void CreateTower();
	void SendLButtonDown(UINT nFlags, CPoint point);
	
	GameScene();
	~GameScene();
};



