#include "pch.h"
#include "LogoScene.h"



LogoScene::LogoScene()
{
	Init();
	printf("LogoScene init\n");
}

void LogoScene::Init()
{
	m_vecImg.push_back(new Gdiplus::Image(TEXT("Asset\\supercell_logo.png")));
}

void LogoScene::Update(float Delta, int frame)
{

	if (GetAsyncKeyState(VK_RETURN) & 0x8001)
	{
		SceneManager::GetInstance().LoadScene(CString("LobbyScene"));
		return;
	}
}

void LogoScene::Render(Gdiplus::Graphics* MemG/*CDC* pDC*/)
{

	int width = m_vecImg[0]->GetWidth();
	int height = m_vecImg[0]->GetHeight();
	
	int tempX = 15;
	int tempY = 80;
	//15, 80, 15 + 450, 80 + 337
	//455 ,417
	Gdiplus::Rect Dst1(tempX, tempY, width + tempX, height + tempY);
    Gdiplus::Bitmap bm1(tempX + width ,height + tempY, PixelFormat32bppARGB);
	Graphics test2(&bm1);

	//0,0, 455, 417
	test2.DrawImage(m_vecImg[0], Dst1, 0, 0, width + tempX, height + tempY, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);


	MemG->DrawImage(&bm1, Dst1);
}

void LogoScene::Release()
{
}