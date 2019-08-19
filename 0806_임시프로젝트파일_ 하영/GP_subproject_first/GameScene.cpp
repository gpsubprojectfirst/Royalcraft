#include "pch.h"
#include "GameScene.h"
#include "UIDeckWnd.h"
#include "BehaviorTree.h"

GameScene::GameScene()
{
	endflag = false;
	printf("GameScene init\n");

	mMap = new MyMap();
	mMap->LoadFile();

	mTree = new SearchTree();
	mTree->Set(mMap);


	blackBoard = new BlackBoard(this->CommandQueue, this->mTree);
	blackBoard->UpdateData(this->playUnit);

	ObjectManager& om = ObjectManager::GetInstance();
	
	Object::SetMode(&m_IsSelectMode);
	UIDeckWnd* deck = new UIDeckWnd();
	deck->Init();
	Init();

	MouseMgr::GetInstance().Init();

	info.emplace_back(deck);
	
	//임시 위치
	endUI = new UICrown();
	endUI->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\endcrown.png"));
	endUI->ParserXML();

	CreateTower();
	//playUnit.emplace_back();
	//blackBoard->UpdateData(playUnit);
	//mUnit->CreateBT(blackBoard);
}

void GameScene::CreateTower()
{
	//tower
	Build* towerKing = new Build();
	towerKing->CopyObj((Build*)ObjectManager::GetInstance().GetBuild(0)
		, mMap->Infos[11][3].rc.X + TILESIZEX /2
		, mMap->Infos[11][3].rc.Y + TILESIZEY /2);
	towerKing->name = "king";
	Build* towerSubA = new Build();
	towerSubA->CopyObj((Build*)ObjectManager::GetInstance().GetBuild(1)
		, mMap->Infos[5][7].rc.X + TILESIZEX / 2
		, mMap->Infos[5][7].rc.Y + TILESIZEY / 2);
	Build* towerSubB = new Build();
	towerSubB->CopyObj((Build*)ObjectManager::GetInstance().GetBuild(2)
		, mMap->Infos[16][7].rc.X + TILESIZEX / 2
		, mMap->Infos[16][7].rc.Y + TILESIZEY / 2);

	towerKing->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\5.build\\asset\\kingtower.png"));
	towerSubA->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\5.build\\asset\\subtower.png"));
	towerSubB->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\5.build\\asset\\subtower.png"));

	towerKing->curTile.first = 11;
	towerKing->curTile.second = 3;

	towerSubA->curTile.first = 5;
	towerSubA->curTile.second = 7;

	towerSubB->curTile.first = 16;
	towerSubB->curTile.second = 7;

	towerKing->posRc = mMap->Infos[11][3].rc;
	towerSubA->posRc = mMap->Infos[5][7].rc;
	towerSubB->posRc = mMap->Infos[16][7].rc;

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
void GameScene::CreateObj(CPoint pt)
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
				/*
				ID:
				0- knight, 1- axeman, 2- darknight,3- electric,4- giant,5- archer,
				6- lumberjack, 7- musket,8- varkirey,9- vavarian,10- vendit,11- wizard
				*/
				Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\knight.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\axeman.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\archer.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\darknight.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\electric.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\giant.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\lumberjack.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\musket.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\varkirey.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\vavarian.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\vendit.png"));
				//Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\wizard.png"));

				MyUnit* mUnit = new MyUnit();
				mUnit->CopyObj((MyUnit*)ObjectManager::GetInstance().GetMyUnit(0), pt.x, pt.y);
				mUnit->ParentImg = load;
				mUnit->curTile.first = i;
				mUnit->curTile.second = j;
				mUnit->posRc = mMap->Infos[i][j].rc;
				mUnit->curPos.X = mUnit->posRc.X + (TILESIZEX / 2);
				mUnit->curPos.Y = mUnit->posRc.Y + (TILESIZEY / 2);
				mUnit->mMap = mMap;
				mUnit->teamBlue = true;
				info.emplace_back(mUnit);
				playUnit.emplace_back(mUnit);
				blackBoard->UpdateData(playUnit);
				mUnit->CreateBT(blackBoard);
			}
		}
	}
	
}

void GameScene::Init()
{
	Object::SetMode(&m_IsSelectMode);
	m_vecGame.push_back( new Gdiplus::Image(TEXT("Asset\\3.game\\2.map\\level_spell_arena_tex.png")));
}

void GameScene::Update(float Delta)
{
	if (!endflag)
	{

		KeyMgr::GetInstance().CheckKey();

		for (auto& it : this->info)
		{
			it->Update(Delta);

			//str비교연산 추후 수정 필요
			if (((Build*)it)->Isdead && it->name.Compare(KING) == 0)
				endflag = true;
		}

		if (m_IsSelectMode)
		{
			POINT pt = MouseMgr::GetInstance().GetMousePos();

			MOUSEINFO _mouseInfo = MouseMgr::GetInstance().GetMouseInfo();

			//TODO : KEY_LBUTTON
			if (KeyMgr::GetInstance().GetKey() & KEY_RBUTTON)
			{
				m_IsSelectMode = false;
				CPoint _cPt(pt.x, pt.y);
				//캐릭터 생성
				CreateObj(_cPt);
			}
		}

		if (KeyMgr::GetInstance().GetKey() & VK_F1)
		{
			bRender = !bRender;
		}
		while (!CommandQueue.Empty())
			CommandQueue.Pop(Delta);
	}
	else
	{
		//게임이 끝났으면 업데이트 멈춤
		endUI->Update(Delta);
	}
}

void GameScene::Render(Gdiplus::Graphics* MemG)
{
	if (m_vecGame.size() <= 0)
		return;

	// 배경
	Gdiplus::Rect Dst1(0, 0, m_vecGame[0]->GetWidth(), m_vecGame[0]->GetHeight());
	MemG->DrawImage(m_vecGame[0], Dst1);

	// 타일
	if (bRender)
	{
		mMap->Render(MemG);
	}

	// 게임 오브젝트
	for (auto& it : this->info)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		it->Render(MemG);
	}

	if (m_IsSelectMode && UIDeckWnd::m_bOnItem == FALSE)
	{
		MouseMgr::GetInstance().Render(MemG);
	}

	if (endflag)
	{
		BitmapData pt;
		Gdiplus::Rect rc(0, 0, Dst1.Width, Dst1.Height);
		backBuffer->LockBits(&rc, ImageLockModeWrite, PixelFormat32bppARGB, &pt);
		grayscale(rc.Width , rc.Height, pt);
		backBuffer->UnlockBits(&pt);

		endUI->Render(MemG);
	}
}

void GameScene::Release()
{

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
	CreateObj(point);
	
}