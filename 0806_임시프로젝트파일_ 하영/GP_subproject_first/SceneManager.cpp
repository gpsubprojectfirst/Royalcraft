#include "pch.h"
#include "SceneManager.h"
#include "SoundMgr.h"

SceneManager::SceneManager()
	: CurScene(nullptr)
{
	//sound load
	SoundMgr::GetInstance()->Init();
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\2min_loop_battle_01_.wav"));   
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\Waltz.wav"));   
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\SeconeRun.wav"));

	ObjectManager& om  = ObjectManager::GetInstance();
	
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
			it->Init();
			CurScene = it;
		//	std::wcout << (const wchar_t*)CurScene->Name <<std::endl;
		}
	}
	//CurScene = nullptr;
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
	KeyMgr::GetInstance().CheckKey();
	CurScene->Update(Delta);
}

Scene* SceneManager::GetCurScene()
{
	return CurScene;
}


