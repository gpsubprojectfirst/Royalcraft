#include "pch.h"
#include "GameScene.h"



GameScene::GameScene()
{

}

void GameScene::Init()
{
	SceneManager::GetInstance().LoadScene(CString("GameScene"));

}

void GameScene::Update(float Delta, int frame)
{
	for (auto& it : this->info)
	{
		if (it->Objtype == eObject_Unit)
		{
			myUnit* o = reinterpret_cast<myUnit*>(it);

			//frame에따라 현재 오브젝트의 렉트 변화
			o->sm.Update();
			if (o->sm.GetCurState() == eState_Idle)
			{
				o->rc = o->moveRc[0];
			}
			else if (o->sm.GetCurState() == eState_Move)
			{
				o->rc = o->moveRc[frame];
			}
			else if (o->sm.GetCurState() == eState_Attack)
			{
				o->rc = o->atkRc[frame];
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
			myUnit* o = reinterpret_cast<myUnit*>(it);
			Gdiplus::Rect Dst(0, 0, 108, 149);
			Gdiplus::Bitmap bm(108, 149, PixelFormat32bppARGB);
			Gdiplus::Graphics test(&bm);
			test.DrawImage(o->ParentImg, Dst, o->rc.X, o->rc.Y, o->rc.Width, o->rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);

			// 회전
			if (bleft)
				bm.RotateFlip(Gdiplus::Rotate270FlipNone);

			MemG->DrawImage(&bm, Dst);
		}

	}
}

void GameScene::Release()
{

}

