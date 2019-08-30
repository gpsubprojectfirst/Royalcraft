#include "pch.h"
#include "LogoScene.h"
#include "SoundMgr.h"


LogoScene::LogoScene()
{
	std::cout << "LogoScene()" << endl;
}

LogoScene::~LogoScene()
{
}

void LogoScene::Init()
{
	std::cout << "LogoScene Init()" << endl;
	SoundMgr::GetInstance()->SoundPlay(7, 0);
	m_imgDst = new Gdiplus::Image(TEXT("Asset\\1.logo\\supercell_logo.png"));
	int width = m_imgDst->GetWidth();
	int height = m_imgDst->GetHeight();
	m_rcDst = Gdiplus::Rect(REAL_WINSIZE_X / 2 - width/2, REAL_WINSIZE_Y / 2 - height / 2, width, height);
	m_vecImg[EScene_Logo].push_back(m_imgDst);
	
}

void LogoScene::Update(float Delta)
{
	if (KeyMgr::GetInstance().GetKey() & KEY_ENTER)
	{
		SoundMgr::GetInstance()->SoundStop(7);
		SceneManager::GetInstance().LoadScene(CString("LobbyScene"));
		return;
	}
}

void LogoScene::Render(Gdiplus::Graphics* MemG)
{
	for (auto& it : m_vecImg[EScene_Logo])
	{
		MemG->DrawImage(m_imgDst, m_rcDst);
	}
}


void LogoScene::Release()
{

}