#include "pch.h"
#include "LobbyScene.h"


LobbyScene::LobbyScene()
{
	Init();
}

void LobbyScene::Init()
{
	bgImg = new CImage();
	bgImg->Load(TEXT("loading_tex_.png"));
}

void LobbyScene::Update(float Delta)
{
}

void LobbyScene::Render(Gdiplus::Graphics* MemG /*CDC* pDC*/)
{

	
	Gdiplus::Image* image = new Gdiplus::Image(TEXT("Asset\\loading_tex_.png"));
	
	Rect Dst(0, 0, 800, 700);
	Bitmap bm(800, 700, PixelFormat32bppARGB);
	Graphics test(&bm);


	test.DrawImage(image, Dst, Dst.X, Dst.Y, Dst.Width, Dst.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	MemG->DrawImage(&bm, Dst);

	
}

void LobbyScene::Release()
{
}
