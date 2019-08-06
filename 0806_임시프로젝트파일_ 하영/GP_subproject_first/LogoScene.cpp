#include "pch.h"
#include "LogoScene.h"



LogoScene::LogoScene()
{
	Init();
}

void LogoScene::Init()
{
	m_vecImg.push_back(new Gdiplus::Image(TEXT("Asset\\supercell_logo.png")));
}

void LogoScene::Update(float Delta, int frame)
{

	if (GetAsyncKeyState(VK_RETURN) & 0x8001)
	{
		SceneManager::GetInstance().SetState(SCENE_LOBBY);
		return;
	}
}

void LogoScene::Render(Gdiplus::Graphics* MemG/*CDC* pDC*/)
{
	
	int width = m_vecImg[0]->GetWidth();
	int height = m_vecImg[0]->GetHeight();
	Gdiplus::Rect Dst1(0, 0, width, height);
		Bitmap bm1(width, height, PixelFormat32bppARGB);
	Graphics test2(&bm1);

	test2.DrawImage(m_vecImg[0], Dst1, Dst1.X + 20, Dst1.Y, width, height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	MemG->DrawImage(&bm1, Dst1);
}

void LogoScene::Release()
{
}