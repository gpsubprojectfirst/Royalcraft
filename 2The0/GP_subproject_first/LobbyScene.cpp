#include "pch.h"
#include "LobbyScene.h"
#include "SoundMgr.h"
#include "UIButton.h"

LobbyScene::LobbyScene()
{
	std::cout << "LobbyScene()" << std::endl;
	CreateButton();
}

LobbyScene::~LobbyScene()
{

}

void LobbyScene::CreateButton()
{
	for (int i = 0; i < 2; ++i)
	{
		UIButton* pBtn = new UIButton();
		pBtn->Init(i);
		float fx = float((REAL_WINSIZE_X / 4 + 10) + 200 * (i));
		float fy = REAL_WINSIZE_Y / 2 - 30;
		Gdiplus::Rect tempRC((int)fx, (int)fy, (int)pBtn->ParentImg->GetWidth(), (int)pBtn->ParentImg->GetHeight());
		pBtn->m_tInfo.fX = fx;
		pBtn->m_tInfo.fY = fy;
		pBtn->m_tInfo.fSizeX = (float)pBtn->ParentImg->GetWidth();
		pBtn->m_tInfo.fSizeY = (float)pBtn->ParentImg->GetHeight();
		pBtn->rc = tempRC;

		vecInfo[EScene_Lobby].push_back(pBtn);
	}
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
	if (KeyMgr::GetInstance().GetKey() & KEY_F1)
	{
		SceneManager::GetInstance().LoadScene(CString("EditorScene"));
		return;
	}

	for (auto& it : this->vecInfo[EScene_Lobby])
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;
		it->Update(Delta);
	}
}

void LobbyScene::Render(Gdiplus::Graphics* MemG)
{
	if (MemG == nullptr) return;

	for (auto& it : m_vecImg[EScene_Lobby])
	{
		MemG->DrawImage(m_imgDst, m_rcDst);
	}

	for (auto& it : vecInfo[EScene_Lobby])
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;
		it->Render(MemG);
	}
}

void LobbyScene::Release()
{
	for (auto& it : vecInfo[EScene_Lobby])
	{
		//it->Release();
		SAFE_DELETE(it);
	}
	vecInfo[EScene_Lobby].clear();
}
