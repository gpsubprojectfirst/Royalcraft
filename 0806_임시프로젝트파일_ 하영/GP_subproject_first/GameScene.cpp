#include "pch.h"
#include "GameScene.h"



GameScene::GameScene()
{
	printf("GameScene init\n");
	Init();

}

void GameScene::Init()
{
	//���map
	m_vecGame.push_back( new Gdiplus::Image(TEXT("Asset\\3.game\\2.map\\level_spell_arena_tex_.png")));
	//myMap();
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

	Gdiplus::Rect Dst1(0,0, REAL_WINSIZE_X, REAL_WINSIZE_Y);
	MemG->DrawImage(m_vecGame[0], Dst1);
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

		mMap.set(point, it);
	}
}