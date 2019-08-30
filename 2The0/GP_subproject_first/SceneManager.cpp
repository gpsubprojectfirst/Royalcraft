#include "pch.h"
#include "SceneManager.h"
#include "SoundMgr.h"

SceneManager::SceneManager()
	: CurScene(nullptr)
{
	
	//sound load
	SoundMgr::GetInstance()->Init();
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\1st_crown_01.wav"));					//0
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\2min_loop_battle_01.wav"));		//1. mainBG
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\archer_attack_07.wav"));				//2. archer attack
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\button_click_02.wav"));				//3. popup click
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\card_fly_in_06.wav"));					//4. click
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\menu_03.wav"));							//5. Lobby
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\scroll_win_02.wav"));					//6. battle win
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\supercell_jingle.wav"));				//7. Logo 
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\tut_jing_01.wav"));						//8. Lobby->main entrance effect bg
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\dark_prince_atk_hit_01.wav"));	//9. hit effect					
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\cannon_fire_03.wav"));				//10.canno effect		
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\musket_fire_02.wav"));				//11.musket_fire effect		
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\electro_wiz_atk_02.wav"));			//12.electric_fire effect		
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\magic_archer_fire_01.wav"));		//13.wizard_fire effect		
	SoundMgr::GetInstance()->LoadWave(TEXT("Asset\\4.sound\\npc_die_02.wav"));						//14.die effect		
	
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

void SceneManager::Release()
{
	for (auto& it : mScene)
	{
		//SAFE_DELETE(it);
		it->Release();
	}
	mScene.clear();
}