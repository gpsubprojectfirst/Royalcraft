#include "pch.h"
#include "GameScene.h"



GameScene::GameScene()
{
	ObjectManager& om = ObjectManager::GetInstance();
	printf("GameScene init\n");
	Init();
	mMap = new myMap();
	mMap->Init();

	//특정 유닛의 에셋 로드, 나중에 오브젝트 클래스 안으로 이동
	//ID: 0,name: knight
	Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\Knight.png"));

	//ObjectManager의 유닛데이터 복사
	myUnit* knight = new myUnit();

	knight->ID = om.GetMyUnit(0)->ID;
	knight->name = om.GetMyUnit(0)->name;
	knight->moveRc = om.GetMyUnit(0)->moveRc;
	knight->atkRc = om.GetMyUnit(0)->atkRc;
	knight->ParentImg = load;
	Gdiplus::Rect Dst(0, 0, 108, 149);
	knight->posRc = Dst;
	knight->mMap = mMap;

	info.emplace_back(knight);
}

void GameScene::Init()
{
	m_vecGame.push_back( new Gdiplus::Image(TEXT("Asset\\3.game\\2.map\\level_spell_arena_tex_.png")));
}

void GameScene::Update(float Delta)
{
	for (auto& it : this->info)
	{
		it->Update(Delta);
	}
}

void GameScene::Render(Gdiplus::Graphics* MemG /*CDC* pDC*/)
{
	Gdiplus::Rect Dst1(0,0, REAL_WINSIZE_X, REAL_WINSIZE_Y);
	MemG->DrawImage(m_vecGame[0], Dst1);
	for (auto& it : this->info)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;
		
		it->Render(MemG);
	}

	if (m_vecGame.size() <= 0)
		return;
	int width = m_vecGame[0]->GetWidth();
	int height = m_vecGame[0]->GetHeight();

	
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

		it->Set(point,mMap);

		//나중에 오버라이딩
		if (it->Objtype == eObject_Unit)
		{
			myUnit* mUnit = reinterpret_cast<myUnit*>(it);
			while(!mUnit->moveTilePath.empty())
				mUnit->moveTilePath.pop();
			mTree.FindPath(mUnit->curTile, mUnit->dstTile,mUnit);	
		}
	}
}