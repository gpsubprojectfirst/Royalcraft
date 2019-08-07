#include "pch.h"
#include "LogoScene.h"



LogoScene::LogoScene()
{
	Init();
	printf("LogoScene init\n");
}

void LogoScene::Init()
{
	m_vecImg.push_back(new Gdiplus::Image(TEXT("Asset\\1.logo\\supercell_logo.png")));
}

void LogoScene::Update(float Delta)
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
	
	Gdiplus::Rect Dst1(REAL_WINSIZE_X / 2 - width / 2, REAL_WINSIZE_Y /2  - height / 2, width,height);
	MemG->DrawImage(m_vecImg[0], Dst1);
}

void LogoScene::Release()
{
}