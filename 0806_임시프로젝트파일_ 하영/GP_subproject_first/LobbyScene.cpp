#include "pch.h"
#include "LobbyScene.h"

LobbyScene::LobbyScene()
{
	Init();
}

void LobbyScene::Init()
{
	bgImg = new CImage();
	bgImg->Load(TEXT("Asset\\loading_tex_.png"));
}

void LobbyScene::Update(float Delta, int frame)
{

}

void LobbyScene::Render(Gdiplus::Graphics* MemG /*CDC* pDC*/)
{
	if (MemG == nullptr) return;

	for (auto& it : this->info)
	{


		if (it == nullptr) continue;
		if (it->Enable == false) continue;


		Gdiplus::Image* image = new Gdiplus::Image(TEXT("Asset\\loading_tex_.png"));

		Rect Dst(0, 0, 800, 700);
		Bitmap bm(800, 700, PixelFormat32bppARGB);
		Graphics test(&bm);


		test.DrawImage(image, Dst, Dst.X, Dst.Y, Dst.Width, Dst.Height, Gdiplus::Unit::UnitPixel,
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
