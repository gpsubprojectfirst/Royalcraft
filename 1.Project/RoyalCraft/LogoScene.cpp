#include "pch.h"
#include "LogoScene.h"

LogoScene::LogoScene()
{
	Init();
}

void LogoScene::Init()
{
	
	
}

void LogoScene::Update(float Delta)
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		SceneManager::GetInstance().SetState(SCENE_LOBBY);
		return;
	}
}

void LogoScene::Render(Gdiplus::Graphics* MemG/*CDC* pDC*/)
{
	m_vecImg.push_back(new Gdiplus::Image(TEXT("Asset\\supercell_logo.png")));


	Rect Dst1(0, 0, 450, 337);
	Bitmap bm1(450, 347, PixelFormat32bppARGB);
	Graphics test2(&bm1);

	test2.DrawImage(m_vecImg[0], Dst1, Dst1.X, Dst1.Y, Dst1.Width, Dst1.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	MemG->DrawImage(&bm1, Dst1);
}

void LogoScene::Release()
{
} 