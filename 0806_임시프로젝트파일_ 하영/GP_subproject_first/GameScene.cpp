#include "pch.h"
#include "GameScene.h"


GameScene::GameScene()
{
	printf("GameScene init\n");

	mMap = new MyMap();
	mMap->LoadFile();

	ObjectManager& om = ObjectManager::GetInstance();
	
	Init();

	//mTree = new SearchTree(mMap);
	mTree = new SearchTree();
	//특정 유닛의 에셋 로드, 나중에 오브젝트 클래스 안으로 이동
	//ID: 0,name: knight 
	Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\Knight.png"));

	//ObjectManager의 유닛데이터 복사
	MyUnit* knight = new MyUnit();

	knight->ID = om.GetMyUnit(0)->ID;
	knight->name = om.GetMyUnit(0)->name;
	knight->moveRc = om.GetMyUnit(0)->moveRc;
	knight->atkRc = om.GetMyUnit(0)->atkRc;
	knight->ParentImg = load;
	Gdiplus::Rect Dst(0, 0, 50, 50);
	knight->posRc = Dst;
	knight->mMap = mMap;

	info.emplace_back(knight);

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
	for (auto& it : this->info)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		it->Set(point,mMap,mTree);
		mTree->Set(mMap);
	}
}