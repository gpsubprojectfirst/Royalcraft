#include "pch.h"
#include "LobbyScene.h"

LobbyScene::LobbyScene()
{
	Init();
}

void LobbyScene::Init()
{
	bgImg = new  Gdiplus::Image(TEXT("Asset\\loading_tex_.png"));
}

void LobbyScene::Update(float Delta, int frame)
{

	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		SceneManager::GetInstance().SetState(SCENE_GAME);
		return;
	}

}

void LobbyScene::Render(Gdiplus::Graphics* MemG /*CDC* pDC*/)
{
	if (MemG == nullptr) return;

	//for (auto& it : this->info)
	{

		/*if (it == nullptr) continue;
		if (it->Enable == false) continue;*/


		Rect Dst(0, 0, WINSIZE_X, WINSIZE_Y);
		Bitmap bm(WINSIZE_X, WINSIZE_Y, PixelFormat32bppARGB);
		Graphics test(&bm);


		test.DrawImage(bgImg, Dst, Dst.X, Dst.Y, Dst.Width, Dst.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);

		MemG->DrawImage(&bm, Dst);

		//if (it->Objtype == eObject_Unit)
		//{
		//	myUnit* o = reinterpret_cast<myUnit*>(it);
		//	Gdiplus::Rect Dst(0, 0, 108, 149);
		//	Gdiplus::Bitmap bm(108, 149, PixelFormat32bppARGB);
		//	Gdiplus::Graphics test(&bm);
		//	test.DrawImage(o->ParentImg, Dst, o->rc.X, o->rc.Y, o->rc.Width, o->rc.Height, Gdiplus::Unit::UnitPixel,
		//		nullptr, 0, nullptr);
		//	
		//	// È¸Àü
		//	if (bleft)
		//		bm.RotateFlip(Gdiplus::Rotate270FlipNone);
		//	MemG->DrawImage(&bm, Dst); 
		//}

	}
}

void LobbyScene::Release()
{
}
