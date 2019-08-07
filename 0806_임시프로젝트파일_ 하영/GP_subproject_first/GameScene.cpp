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
		if (it->Objtype == eObject_Unit)
		{
			myUnit* unit = reinterpret_cast<myUnit*>(it);
			
			//state에따라 현재 오브젝트의 렉트 변화
			unit->Update(Delta);
			//unit->sm.Update();
			if (unit->sm.GetCurState() == eState_Idle)
			{
				unit->rc = unit->moveRc[unit->frame];
			}
			else if (unit->sm.GetCurState() == eState_Move)
			{
				unit->rc = unit->moveRc[unit->frame];
			}
			else if (unit->sm.GetCurState() == eState_Attack)
			{
				unit->rc = unit->atkRc[unit->frame];
			}
		}
	}
}

void GameScene::Render(Gdiplus::Graphics* MemG /*CDC* pDC*/)
{

	for (auto& it : this->info)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;
		if (it->Objtype == eObject_Unit)
		{
			myUnit* unit = reinterpret_cast<myUnit*>(it);
			
			int width = unit->rc.Width;
			int height = unit->rc.Height;

			Gdiplus::Rect Dst1(0, 0, width, height);
			MemG->DrawImage(unit->ParentImg, Dst1 , unit->rc.X,unit->rc.Y,unit->rc.Width,unit->rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
	}
}

void GameScene::Release()
{

}

