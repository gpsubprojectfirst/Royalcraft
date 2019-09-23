#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	: CurScene(nullptr)
{
	LogoScene* logo = new LogoScene();
	logo->Name = "LogoScene";
	mScene.emplace_back(logo);

	LobbyScene* lobby = new LobbyScene();
	lobby->Name = "LobbyScene";
	mScene.emplace_back(lobby);

	Init();
	
}

void SceneManager::LoadScene(CString& pName)
{
	for (auto& it : mScene)
	{
		if (!it->Name.CompareNoCase(pName))
		{
			CurScene = it;
		}
	}

	//CurScene = nullptr;
}

void SceneManager::SetState(SCENE _SceneState)
{
		switch (_SceneState)
		{
		case SCENE_LOGO:
			CurScene = new LogoScene;
			break;

		case SCENE_LOBBY:
			CurScene = new LobbyScene;
			break;

		case SCENE_GAME:
			break;

		case SCENE_END:
			break;
		}

		CurScene->Init();
}

void SceneManager::Init()
{
	if (CurScene == nullptr) return;

}

void SceneManager::RenderScene(Gdiplus::Graphics* MemG/*CDC* pDC*/)
{
	if (CurScene == nullptr) return;
	if (MemG == nullptr) return;

	CurScene->Render(MemG);
}

Scene* SceneManager::GetCurScene()
{
	return CurScene;

}

void SceneManager::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (CurScene == nullptr) return;

	//CurScene->LeftButtonDown(nFlags, point);
}

void SceneManager::Update(float Delta)
{
	if (CurScene == nullptr) return;
	CurScene->Update(Delta);
}

