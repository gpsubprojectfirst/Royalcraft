#include "pch.h"
#include "LobbyScene.h"

LobbyScene::LobbyScene()
{
	std::cout << "LobbyScene()" << std::endl;
}

void LobbyScene::Init()
{
	std::cout << "LobbyScene Init()" << std::endl;
	bgImg = new  Gdiplus::Image(TEXT("Asset\\2.lobby\\loading_tex.png"));

}

void LobbyScene::Update(float Delta)
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		SceneManager::GetInstance().LoadScene(CString("GameScene"));
		return;
	}

	if (GetAsyncKeyState(VK_F1) & 0x8001)
	{
		SceneManager::GetInstance().LoadScene(CString("EditorScene"));
		return;
	}
}

void LobbyScene::Render(Gdiplus::Graphics* MemG)
{
	if (MemG == nullptr) return;

	{
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
