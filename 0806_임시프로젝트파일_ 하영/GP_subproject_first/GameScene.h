#pragma once
#include "Scene.h"
#include "MyMap.h"
#include "SearchTree.h"
#include "Command.h"
#include "ViewUnit.h"
#include "UIDeckWnd.h"
#include "UICrown.h"
#include "UIPopup.h"
#include "UIHpbar.h"
#include "UITime.h"
#include "UIElixirbar.h"
#include "UITimeEvent.h"

class GameScene :
	public Scene
{ 
public:
	MyMap* mMap;
	MapEditor* editor;
	SearchTree* mTree;
	Command CommandQueue;
	std::vector<MyUnit*> playUnit;
	BlackBoard* blackBoard;
	bool bRender = false;
	ViewUnit* unitInfo;
	bool m_IsSelectMode;
	bool endflag;						//���� ����
	bool m_bExit;					//���� ����
	Object* tempObj;

	UIDeckWnd* deck;
	UIPopup* m_uiPopup;
	UIHPBar* m_uiHPBar;
	UIElixirBar* m_uiElixBar;
	UITime* m_uiTime;
	UITimeEvent* m_uiTimeEvent;
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
	void CreateMyTower();
	void SendLButtonDown(UINT nFlags, CPoint point);
	void SortInfoByYval();
	GameScene();
	~GameScene();

	friend UITimeEvent;
};



