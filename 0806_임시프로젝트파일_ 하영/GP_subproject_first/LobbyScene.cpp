#include "pch.h"
#include "LobbyScene.h"

LobbyScene::LobbyScene()
{
	Init();

	printf("LobbyScene init\n");
}

void LobbyScene::Init()
{
	bgImg = new  Gdiplus::Image(TEXT("Asset\\2.lobby\\loading_tex_.png"));
}

void LobbyScene::Update(float Delta)
{

	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		SceneManager::GetInstance().LoadScene(CString("GameScene"));
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


		Rect Dst(0, 0, REAL_WINSIZE_X, REAL_WINSIZE_Y);
		Bitmap bm(REAL_WINSIZE_X, REAL_WINSIZE_Y, PixelFormat32bppARGB);
		Graphics test(&bm);


		test.DrawImage(bgImg, Dst, Dst.X, Dst.Y, Dst.Width, Dst.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);

		MemG->DrawImage(&bm, Dst);

	}
}

void LobbyScene::Release()
{
}
