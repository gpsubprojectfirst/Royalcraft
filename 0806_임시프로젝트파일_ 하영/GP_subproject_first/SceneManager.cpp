#include "pch.h"
#include "SceneManager.h"


SceneManager::SceneManager()
	: CurScene(nullptr)
{
	ObjectManager& om  = ObjectManager::GetInstance();
	//���� ä������
	
	LogoScene* logo = new LogoScene();
	logo->Name = "LogoScene";

	LobbyScene* lobby = new LobbyScene();
	lobby->Name = "LobbyScene";

	MapEditor* editor = new MapEditor();
	editor->Name = "EditorScene";
	
	GameScene* game = new GameScene();
	game->Name = "GameScene";

	mScene.emplace_back(logo);
	mScene.emplace_back(lobby);
	mScene.emplace_back(editor);
	mScene.emplace_back(game);
}

void SceneManager::LoadScene(CString& pName)
{
	for (auto& it : mScene)
	{
		if (!it->Name.CompareNoCase(pName))
		{
			CurScene = it;
			std::wcout << (const wchar_t*)CurScene->Name <<std::endl;
		}
	}
	//CurScene = nullptr;
}

//TODO
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

	case SCENE_EDITOR:
		CurScene = new MapEditor;
		break;

	case SCENE_GAME:
		CurScene = new GameScene;
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

void SceneManager::RenderScene(Gdiplus::Graphics* MemG)
{
	if (CurScene == nullptr) return;
	if (MemG == nullptr) return;


 	CurScene->Render(MemG);

}
void SceneManager::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (CurScene == nullptr) return;

	CurScene->SendLButtonDown(nFlags, point);
}

void SceneManager::Update(float Delta)
{
	if (CurScene == nullptr) return;
	CurScene->Update(Delta);
}

Scene* SceneManager::GetCurScene()
{
	return CurScene;
}


