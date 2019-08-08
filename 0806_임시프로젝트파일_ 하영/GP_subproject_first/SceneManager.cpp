#include "pch.h"
#include "SceneManager.h"


SceneManager::SceneManager()
	: CurScene(nullptr)
{
	ObjectManager& om  = ObjectManager::GetInstance();
	//씬을 채워야함

	LogoScene* logo = new LogoScene();
	logo->Name = "LogoScene";

	LobbyScene* lobby = new LobbyScene();
	lobby->Name = "LobbyScene";

	GameScene* game = new GameScene();
	game->Name = "GameScene";


	//특정 유닛의 에셋 로드
	//ID: 0,name: knight
	Gdiplus::Image* load = new Gdiplus::Image(TEXT("Asset\\3.game\\1.unit\\Knight.png"));
	
	//ObjectManager의 유닛데이터 복사
	myUnit* knight = new myUnit();
	
	knight->ID = om.GetMyUnit(0)->ID;
	knight->name = om.GetMyUnit(0)->name;
	knight->moveRc = om.GetMyUnit(0)->moveRc;
	knight->atkRc = om.GetMyUnit(0)->atkRc;
	knight->ParentImg = load;
	Gdiplus::Rect Dst(0, 0, 108, 149);
	knight->posRc = Dst;

	game->info.emplace_back(knight);


	mScene.emplace_back(logo);
	mScene.emplace_back(lobby);
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


