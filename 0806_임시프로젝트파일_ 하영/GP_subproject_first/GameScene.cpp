#include "pch.h"
#include "GameScene.h"
#include "UIDeckWnd.h"


GameScene::GameScene()
{
	printf("GameScene init\n");

	mMap = new MyMap();
	mMap->LoadFile();

	mTree = new SearchTree();
	ObjectManager& om = ObjectManager::GetInstance();
	

	Object::SetMode(&m_IsSelectMode);
	UIDeckWnd* deck = new UIDeckWnd();
	deck->Init();
	Init();

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

	int xIdx;
	int yIdx;

	for (int i = 0; i < TILECNTX; ++i)
	{
		for (int j = 0; j < TILECNTY; ++j)
		{
			if (mMap->Infos[i][j].rc.Contains(mPoint) && mMap->Infos[i][j].flags == 0)
			{
				Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\Knight.png"));

				MyUnit* knight = new MyUnit();
				knight->CopyObj((MyUnit*)ObjectManager::GetInstance().GetMyUnit(0), pt.x, pt.y);
				knight->ParentImg = load;
				info.emplace_back(knight);
			}
		
		}
	}
	
}


void GameScene::Init()
{
	m_vecGame.push_back( new Gdiplus::Image(TEXT("Asset\\3.game\\2.map\\level_spell_arena_tex.png")));
}

void GameScene::Update(float Delta)
{
	KeyMgr::GetInstance().CheckKey();
	for (auto& it : this->info)
	{
		it->Update(Delta);
	}

	if (GetAsyncKeyState(VK_F1) & 0x8001)
	{
		bRender = !bRender;
	}
	
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

	if (m_IsSelectMode)
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

		//쓰레드 계산 버그
		//it->Set(point,mMap,mTree);
		//mTree->Set(mMap);

	}
}