#include "pch.h"
#include "GameScene.h"
#include "UIDeckWnd.h"
#include "BehaviorTree.h"
#include "SoundMgr.h"


GameScene::GameScene()
{
	std::cout << "GameScene()" << endl;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	std::cout << "GameScene Init()" << endl;
	
	m_imgDst = new Gdiplus::Image(TEXT("Asset\\3.game\\2.map\\level_spell_arena_tex.png"));
	m_rcDst = Gdiplus::Rect(0,0, m_imgDst->GetWidth(), m_imgDst->GetHeight());
	m_vecImg[EScene_Game].push_back(m_imgDst);
	
	/*
	ID:
	0- knight, 1- axeman, 2- darknight,3- electric,4- giant,5- archer,
	6- lumberjack, 7- musket,8- varkirey,9- vavarian,10- vendit,11- wizard
`	*/
	SoundMgr::GetInstance()->SoundPlay(0, 1);
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\knight.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\axeman.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\darknight.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\electric.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\giant.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\archer.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\lumberjack.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\musket.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\varkirey.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\vavarian.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\vendit.png")));
	m_vecImg[EScene_Game].push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\wizard.png")));

	endflag = false;
	m_bExit = false;

	mMap = new MyMap();
	mMap->LoadFile();

	mTree = new SearchTree();
	mTree->Set(mMap);


	blackBoard = new BlackBoard(this->CommandQueue, this->mTree);
	blackBoard->UpdateData(this->playUnit);

	ObjectManager& om = ObjectManager::GetInstance();

	UIDeckWnd* deck = new UIDeckWnd();
	info.emplace_back(deck);

	blackBoard = new BlackBoard(this->CommandQueue, this->mTree);
	blackBoard->UpdateData(this->playUnit);

	MouseMgr::GetInstance().Init();

	//임시 위치
	endUI = new UICrown();
	endUI->bluecrown = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\endcrown.png"));
	endUI->redcrown = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\enduired.png"));
	endUI->ParserXML();
	
	m_uiHPBar = new UIHPBar();
	m_uiHPBar->Init();
	m_uiElixBar = new UIElixirBar();
	m_uiElixBar->Init();
	m_uiTime = new UITime();
	m_uiTime->Init();
	m_uiPopup = new UIPopup();
	m_uiPopup->Init();
	//info.push_back(m_uiPopup);

	CreateTower();
	CreateMyTower();
	//playUnit.emplace_back();
	//blackBoard->UpdateData(playUnit);
	//mUnit->CreateBT(blackBoard);

}

void GameScene::CreateViewUnit(CPoint pt, int unitID)
{
	Point mPoint;
	mPoint.X = pt.x;
	mPoint.Y = pt.y;

	for (int i = 0; i < TILECNTX; ++i)
	{
		for (int j = 0; j < TILECNTY; ++j)
		{
			if (mMap->Infos[i][j].rc.Contains(mPoint) && mMap->Infos[i][j].flags == 0)
			{
				ViewUnit* mUnit = new ViewUnit();
				mUnit->CopyObj((MyUnit*)ObjectManager::GetInstance().GetMyUnit(unitID), pt.x, pt.y);
				mUnit->ParentImg = m_vecImg[EScene_Game][unitID + 1]; //image vector index에 들어간 ID값
				//mUnit->posRc = mMap->Infos[i][j].rc;
				unitInfo = mUnit;
				UIDeckWnd::m_IsSelectMode = 2;
			}
		}
	}

}

void GameScene::CreateTower()
{
	//tower
	Build* towerKing = new Build();
	towerKing->pivotVal = 286;
	towerKing->CopyObj((Build*)ObjectManager::GetInstance().GetBuild(eBuild_RedKing)
		, mMap->Infos[TOWER_RED_KING_X][TOWER_RED_KING_Y].rc.X + TILESIZEX / 2
		, mMap->Infos[TOWER_RED_KING_X][TOWER_RED_KING_Y].rc.Y + TILESIZEY / 2);
	towerKing->name = "king";
	Build* towerSubA = new Build();
	towerSubA->pivotVal = 198;
	towerSubA->CopyObj((Build*)ObjectManager::GetInstance().GetBuild(eBuild_RedSubL)
		, mMap->Infos[TOWER_RED_SUBL_X][TOWER_RED_SUBL_Y].rc.X + TILESIZEX / 2
		, mMap->Infos[TOWER_RED_SUBL_X][TOWER_RED_SUBL_Y].rc.Y + TILESIZEY / 2);
	Build* towerSubB = new Build();
	towerSubB->pivotVal = 198;
	towerSubB->CopyObj((Build*)ObjectManager::GetInstance().GetBuild(eBuild_RedSubR)
		, mMap->Infos[TOWER_RED_SUBR_X][TOWER_RED_SUBR_Y].rc.X + TILESIZEX / 2
		, mMap->Infos[TOWER_RED_SUBR_X][TOWER_RED_SUBR_Y].rc.Y + TILESIZEY / 2);

	towerKing->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\5.build\\asset\\kingtower.png"));
	towerSubA->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\5.build\\asset\\subtower.png"));
	towerSubB->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\5.build\\asset\\subtower.png"));

	towerKing->curTile.first = TOWER_RED_KING_X;
	towerKing->curTile.second = TOWER_RED_KING_Y;

	towerSubA->curTile.first = TOWER_RED_SUBL_X;
	towerSubA->curTile.second = TOWER_RED_SUBL_Y;

	towerSubB->curTile.first = TOWER_RED_SUBR_X;
	towerSubB->curTile.second = TOWER_RED_SUBR_Y;

	towerKing->posRc = mMap->Infos[TOWER_RED_KING_X][TOWER_RED_KING_Y].rc;
	towerSubA->posRc = mMap->Infos[TOWER_RED_SUBL_X][TOWER_RED_SUBL_Y].rc;
	towerSubB->posRc = mMap->Infos[TOWER_RED_SUBR_X][TOWER_RED_SUBR_Y].rc;

	towerKing->teamBlue = false;
	towerSubA->teamBlue = false;
	towerSubB->teamBlue = false;

	info.emplace_back(towerKing);
	info.emplace_back(towerSubA);
	info.emplace_back(towerSubB);

	playUnit.emplace_back(towerKing);
	playUnit.emplace_back(towerSubA);
	playUnit.emplace_back(towerSubB);

	blackBoard->UpdateData(playUnit);

	towerKing->CreateBT(blackBoard);
	towerSubA->CreateBT(blackBoard);
	towerSubB->CreateBT(blackBoard);
}
void GameScene::CreateMyTower()
{
	//tower
	Build* towerKing = new Build();
	towerKing->pivotVal = 236;
	towerKing->CopyObj((Build*)ObjectManager::GetInstance().GetBuild(eBuild_BlueKing)
		, mMap->Infos[TOWER_BLUE_KING_X][TOWER_BLUE_KING_Y].rc.X + TILESIZEX / 2
		, mMap->Infos[TOWER_BLUE_KING_X][TOWER_BLUE_KING_Y].rc.Y + TILESIZEY / 2);
	towerKing->name = "king";
	Build* towerSubA = new Build();
	towerSubA->pivotVal = 210;
	towerSubA->CopyObj((Build*)ObjectManager::GetInstance().GetBuild(eBuild_BlueSubL)
		, mMap->Infos[TOWER_BLUE_SUBL_X][TOWER_BLUE_SUBL_Y].rc.X + TILESIZEX / 2
		, mMap->Infos[TOWER_BLUE_SUBL_X][TOWER_BLUE_SUBL_Y].rc.Y + TILESIZEY / 2);
	Build* towerSubB = new Build();
	towerSubB->pivotVal = 210;
	towerSubB->CopyObj((Build*)ObjectManager::GetInstance().GetBuild(eBuild_BlueSubR)
		, mMap->Infos[TOWER_BLUE_SUBR_X][TOWER_BLUE_SUBR_Y].rc.X + TILESIZEX / 2
		, mMap->Infos[TOWER_BLUE_SUBR_X][TOWER_BLUE_SUBR_Y].rc.Y + TILESIZEY / 2);

	towerKing->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\5.build\\asset\\kingtowerblue.png"));
	towerSubA->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\5.build\\asset\\subtowerblue.png"));
	towerSubB->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\5.build\\asset\\subtowerblue.png"));

	towerKing->curTile.first = TOWER_BLUE_KING_X;
	towerKing->curTile.second = TOWER_BLUE_KING_Y;

	towerSubA->curTile.first = TOWER_BLUE_SUBL_X;
	towerSubA->curTile.second = TOWER_BLUE_SUBL_Y;

	towerSubB->curTile.first = TOWER_BLUE_SUBR_X;
	towerSubB->curTile.second = TOWER_BLUE_SUBR_Y;

	towerKing->posRc = mMap->Infos[TOWER_BLUE_KING_X][TOWER_BLUE_KING_Y].rc;
	towerSubA->posRc = mMap->Infos[TOWER_BLUE_SUBL_X][TOWER_BLUE_SUBL_Y].rc;
	towerSubB->posRc = mMap->Infos[TOWER_BLUE_SUBR_X][TOWER_BLUE_SUBR_Y].rc;

	towerKing->teamBlue = true;
	towerSubA->teamBlue = true;
	towerSubB->teamBlue = true;

	info.emplace_back(towerKing);
	info.emplace_back(towerSubA);
	info.emplace_back(towerSubB);

	playUnit.emplace_back(towerKing);
	playUnit.emplace_back(towerSubA);
	playUnit.emplace_back(towerSubB);

	blackBoard->UpdateData(playUnit);

	towerKing->CreateBT(blackBoard);
	towerSubA->CreateBT(blackBoard);
	towerSubB->CreateBT(blackBoard);
}

void GameScene::CreateObj(CPoint pt, MOUSEINFO MInfo)
{
	if (MInfo.iElixir <= m_uiElixBar->mycost)
	{
		Point mPoint;
		mPoint.X = pt.x;
		mPoint.Y = pt.y;

		for (int i = 0; i < TILECNTX; ++i)
		{
			for (int j = 0; j < TILECNTY; ++j)
			{
				if (mMap->Infos[i][j].rc.Contains(mPoint) && mMap->Infos[i][j].flags == 0)
				{
					MyUnit* mUnit = new MyUnit();
					EUnit_ID unitID = (EUnit_ID)MInfo.unitID;
					int cost = MInfo.iElixir;
					mUnit->CopyObj((MyUnit*)ObjectManager::GetInstance().GetMyUnit(unitID), pt.x, pt.y);
					mUnit->ParentImg = m_vecImg[EScene_Game][unitID + 1];
					mUnit->curTile.first = i;
					mUnit->curTile.second = j;
					mUnit->posRc = mMap->Infos[i][j].rc;
					mUnit->curPosX = mUnit->posRc.X + (TILESIZEX / 2);
					mUnit->curPosY = mUnit->posRc.Y + (TILESIZEY / 2);
					mUnit->mMap = mMap;
					mUnit->teamBlue = true;
					info.emplace_back(mUnit);
					playUnit.emplace_back(mUnit);
					blackBoard->UpdateData(playUnit);
					mUnit->CreateBT(blackBoard);
					m_uiElixBar->spendCost(cost);
					UIDeckWnd::m_IsSelectMode = 3;
				}
			}
		}
	}
}
void GameScene::CreateEnemy()
{
	srand(time(nullptr));
	
	int x = rand()% 10 + 5;
	int y = 8;

	MyUnit* mUnit = new MyUnit();
	EUnit_ID unitID = (EUnit_ID)(rand() % eUnit_Cnt);
	mUnit->CopyObj((MyUnit*)ObjectManager::GetInstance().GetMyUnit(unitID),0,0);
	mUnit->ParentImg = m_vecImg[EScene_Game][unitID + 1];
	mUnit->curTile.first = x;
	mUnit->curTile.second = y;
	mUnit->posRc = mMap->Infos[x][y].rc;
	mUnit->curPosX = mUnit->posRc.X + (TILESIZEX / 2);
	mUnit->curPosY = mUnit->posRc.Y + (TILESIZEY / 2);
	mUnit->mMap = mMap;
	mUnit->teamBlue = false;
	info.emplace_back(mUnit);
	playUnit.emplace_back(mUnit);
	blackBoard->UpdateData(playUnit);
	mUnit->CreateBT(blackBoard);
}
void GameScene::Update(float Delta)
{
	
	if (KeyMgr::GetInstance().GetKey() & KEY_ESC)
	{
		m_bExit = !m_bExit;
	}
	
	if (!endflag && !m_bExit && !m_uiTime->IsEndTime())
	{
		POINT pt = MouseMgr::GetInstance().GetMousePos();
		if (m_uiTime->runTime == ENEMY_CREATE_TERM && m_uiTime->runTime > 0)
		{
			CreateEnemy();
			m_uiTime->runTime = 0;
		}
		for (auto& it : this->info)
		{
			it->Update(Delta);
			//str비교연산 추후 수정 필요
			if (((Build*)it)->Isdead && it->name.Compare(KING) == 0)
				endflag = true;
		}
		//UI update
		m_uiTime->Update(Delta);
		m_uiElixBar->Update(Delta);
		

		if (UIDeckWnd::m_IsSelectMode == 1)
		{
			CPoint _cPt(pt.x, pt.y);
			CreateViewUnit(_cPt, MouseMgr::GetInstance().GetUnitID());
			
		}

		if (KeyMgr::GetInstance().GetKey() & KEY_F1)
		{
			bRender = !bRender;
		}
		while (!CommandQueue.Empty())
			CommandQueue.Pop(Delta);
	}
	else
	{
		if (endflag || m_uiTime->IsEndTime())
		{
			//게임이 끝났으면 업데이트 멈춤
			SoundMgr::GetInstance()->SoundStop(0);
			endUI->SetTeam(endflag);
			endUI->Update(Delta);
		}
		if (m_bExit)
		{
			m_uiPopup->Update(Delta);
		}
		
	}
}

void GameScene::Render(Gdiplus::Graphics* MemG)
{
	if (this == nullptr)
		return;

	//// 배경
	Gdiplus::Rect Dst1(0, 0, m_vecImg[EScene_Game][0]->GetWidth(), m_vecImg[EScene_Game][0]->GetHeight());
	MemG->DrawImage(m_vecImg[EScene_Game][0], Dst1);

	// 타일
	if (bRender)
	{
		mMap->Render(MemG);
	}

	// 게임 오브젝트
	for (auto& it : this->info)
	{
		if (it == nullptr) return;
		if (it->Enable == false) return;
		it->Render(MemG);
	}

	if (unitInfo != nullptr)
	{
		unitInfo->Render(MemG);
	}

	if(m_uiHPBar!=nullptr)
	m_uiHPBar->Render(MemG);
	m_uiTime->Render(MemG);
	m_uiElixBar->Render(MemG);


	if (endflag || m_bExit || m_uiTime->IsEndTime())
	{
		BitmapData pt;
		Gdiplus::Rect rc(0, 0, m_rcDst.Width, m_rcDst.Height);
		backBuffer->LockBits(&rc, ImageLockModeWrite, PixelFormat32bppARGB, &pt);
		grayscale(rc.Width, rc.Height, pt);
		backBuffer->UnlockBits(&pt);

		if (endUI == nullptr)
			return;

		if (m_uiPopup == nullptr)
			return;

		if (endflag || m_uiTime->IsEndTime())
		{
			endUI->Render(MemG);
		}

		if (m_bExit)
		{
			m_uiPopup->Render(MemG);
		}
	}

}

void GameScene::Release()
{
	info.clear();
	playUnit.clear();
	m_vecImg[EScene_Game].clear();
	SAFE_DELETE(mMap);
	SAFE_DELETE(mTree);
	SAFE_DELETE(blackBoard);
	SAFE_DELETE(endUI);
	SAFE_DELETE(m_uiHPBar);
}

void GameScene::GetBuffer(Gdiplus::Bitmap* _Buffer)
{
	this->backBuffer = _Buffer;
}

void GameScene::grayscale(int width, int height, Gdiplus::BitmapData& pData)
{
	BYTE* pt = static_cast<BYTE*>(pData.Scan0);
	BYTE* pt2 = pt;
	for (int i = 0; i < height; ++i)
	{
		pt = pt2 + i * pData.Width * 4;
		for (int j = 0; j < width; ++j)
		{
			BYTE calc = *(pt) * 0.299 + *(pt + 1) * 0.587 + *(pt + 2) * 0.114;
			*(pt) = calc;
			*(pt + 1) = calc;
			*(pt + 2) = calc;
			pt += 4;
		}
	}
}

void GameScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (UIDeckWnd::m_IsSelectMode == 2)
	{
		if (unitInfo != nullptr)
		{
			delete(unitInfo);
			unitInfo = nullptr;
		}

		
		CreateObj(point, MouseMgr::GetInstance().GetMouseInfo());
	}
}