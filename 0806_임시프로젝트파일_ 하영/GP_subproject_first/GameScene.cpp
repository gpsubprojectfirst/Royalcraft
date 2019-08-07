#include "pch.h"
#include "GameScene.h"



GameScene::GameScene()
{
	printf("GameScene init\n");
}

void GameScene::Init()
{
	//SceneManager::GetInstance().LoadScene(CString("GameScene"));

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
}

void GameScene::Release()
{

}

