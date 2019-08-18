#include "pch.h"
#include "GameScene.h"
#include "UIDeckWnd.h"
#include "BehaviorTree.h"

GameScene::GameScene()
{
	printf("GameScene init\n");

	mMap = new MyMap();
	mMap->LoadFile();

	mTree = new SearchTree();
	mTree->Set(mMap);

	ObjectManager& om = ObjectManager::GetInstance();
	
	Object::SetMode(&m_IsSelectMode);
	UIDeckWnd* deck = new UIDeckWnd();
	blackBoard = new BlackBoard(this->CommandQueue,this->mTree);
	blackBoard->UpdateData(this->playUnit);
	deck->Init();
	Init();

	MouseMgr::GetInstance().Init();

	//특정 유닛의 에셋 로드, 나중에 오브젝트 클래스 안으로 이동
	//ID: 0,name: knight 
	//knight = new MyUnit();
	//ObjectManager의 유닛데이터 복사
	info.emplace_back(deck);
	
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
	KeyMgr::GetInstance().CheckKey();

	for (auto& it : this->info)
	{
		it->Update(Delta);
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
 	while(!CommandQueue.Empty())
		CommandQueue.Pop(Delta);
}

void GameScene::Render(Gdiplus::Graphics* MemG)
{

	if (m_vecGame.size() <= 0)
		return;

	// 배경
	Gdiplus::Rect Dst1(0,0, m_vecGame[0]->GetWidth(), m_vecGame[0]->GetHeight());
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
}

void GameScene::Release()
{

}

void GameScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	//CreateObj(point);
	for (auto& it : this->info)
	{
		//std::cout <<"x:" <<point.x << "," << point.y << endl;
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		//it->Set(point, mMap, mTree);
		//mTree->Set(mMap);
	//쓰레드 계산 버그
		//it->Set(point,mMap,mTree);
		//mTree->Set(mMap);

	}
}