#pragma once
#include "Scene.h"
#include "MyMap.h"
#include "SearchTree.h"
#include "Command.h"
#include "ViewUnit.h"
#include "UICrown.h"
#include "UIPopup.h"
#include "UIHpbar.h"
#include "UITime.h"

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
	bool	m_Renderflag;
	ViewUnit* unitInfo;
	bool m_IsSelectMode;
	bool endflag;						//���� ����
	bool m_bExit;					//���� ����

	
	UIPopup* m_uiPopup;
	UIHpbar* m_uiHpbar;
	UITime* m_uiTime;
	//������ �� ���ϸ��̼��� ���� ����
	UICrown* endUI;
public:

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Release();

	void GetBuffer(Gdiplus::Bitmap* _Buffer);
	void grayscale(int width, int height, Gdiplus::BitmapData& pData);
	void CreateObj(CPoint pt, MOUSEINFO MInfo);
	void CreateViewUnit(CPoint pt, int unitID);
	void CreateTower();
	void SendLButtonDown(UINT nFlags, CPoint point);
	
	GameScene();
	~GameScene();
};



