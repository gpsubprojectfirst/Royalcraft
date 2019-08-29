#include "pch.h"
#include "LobbyScene.h"
#include "SoundMgr.h"

LobbyScene::LobbyScene()
{
	std::cout << "LobbyScene()" << std::endl;
}

void LobbyScene::Init()
{
	std::cout << "LobbyScene Init()" << std::endl;
	SoundMgr::GetInstance()->SoundPlay(5, 0);
	m_imgDst = new  Gdiplus::Image(TEXT("Asset\\2.lobby\\loading_tex.png"));
	m_rcDst = Gdiplus::Rect(0, 0, REAL_WINSIZE_X, REAL_WINSIZE_Y);
	m_vecImg[EScene_Lobby].push_back(m_imgDst);
}

void LobbyScene::Update(float Delta)
{
	if (KeyMgr::GetInstance().GetKey() & KEY_SPACE)
	{
		SoundMgr::GetInstance()->SoundStop(5);
		SceneManager::GetInstance().LoadScene(CString("GameScene"));
		return;
	}

	if (KeyMgr::GetInstance().GetKey() & KEY_F1)
	{
		SceneManager::GetInstance().LoadScene(CString("EditorScene"));
		return;
	}
}

void LobbyScene::Render(Gdiplus::Graphics* MemG)
{
	if (MemG == nullptr) return;

	for (auto& it : m_vecImg[EScene_Lobby])
	{
		MemG->DrawImage(m_imgDst, m_rcDst);
	}
}

void LobbyScene::Release()
{
}
