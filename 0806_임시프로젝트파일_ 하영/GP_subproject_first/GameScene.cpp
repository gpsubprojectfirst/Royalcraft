#include "pch.h"
#include "GameScene.h"


GameScene::GameScene()
{
	printf("GameScene init\n");

	mMap = new MyMap();
	mMap->LoadFile();

	mTree = new SearchTree();
	ObjectManager& om = ObjectManager::GetInstance();
	
	Init();

	//특정 유닛의 에셋 로드, 나중에 오브젝트 클래스 안으로 이동
	//ID: 0,name: knight 
	Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\Knight.png"));
	//knight = new MyUnit();
	//ObjectManager의 유닛데이터 복사
	MyUnit* knight = new MyUnit();
	knight->CopyObj(om.GetMyUnit(0));
	knight->ParentImg = load;

	info.emplace_back(knight);
	
}

void GameScene::CreateObj(int ix, int iy)
{
	
	//knight->ID = ObjectManager::GetInstance().GetMyUnit(0)->ID;
	//knight->name = ObjectManager::GetInstance().GetMyUnit(0)->name;
	//knight->moveRc = ObjectManager::GetInstance().GetMyUnit(0)->moveRc;
	//knight->atkRc = ObjectManager::GetInstance().GetMyUnit(0)->atkRc;
	//knight->ParentImg = load;

	//int iSizeX = 50;
	//int iSizeY = 50;

	////Pos  100,100,150,150

	//Gdiplus::Rect Dst(ix, iy, ix+iSizeX, iy + iSizeY);
	//knight->posRc = Dst;
	//knight->mMap = mMap;

}

void GameScene::Init()
{
	m_vecGame.push_back( new Gdiplus::Image(TEXT("Asset\\3.game\\2.map\\level_spell_arena_tex.png")));
}

void GameScene::Update(float Delta)
{
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
}

void GameScene::Release()
{

}

void GameScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	//CreateObj(point.x, point.y);
	for (auto& it : this->info)
	{
		//std::cout << "x: " << point.x << "y: " << point.y << endl;
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		it->Set(point, mMap, mTree);
		mTree->Set(mMap);
		//쓰레드 계산 버그
		//it->Set(point,mMap,mTree);
		//mTree->Set(mMap);

	}
}