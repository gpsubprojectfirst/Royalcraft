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
	Init();

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

	//if (CurScene == nullptr) return;
	//if (MemG == nullptr) return;

	//for (auto& it : CurScene->info)
	//{
	//	

	//	if (it == nullptr) continue;
	//	if (it->Enable == false) continue;
	//	if (it->Objtype == eObject_Unit)
	//	{
	//		myUnit* o = reinterpret_cast<myUnit*>(it);
	//		Gdiplus::Rect Dst(0, 0, 108, 149);
	//		Gdiplus::Bitmap bm(108, 149, PixelFormat32bppARGB);
	//		Gdiplus::Graphics test(&bm);
	//		test.DrawImage(o->ParentImg, Dst, o->rc.X, o->rc.Y, o->rc.Width, o->rc.Height, Gdiplus::Unit::UnitPixel,
	//			nullptr, 0, nullptr);
	//		
	//		// 회전
	//		if (bleft)
	//			bm.RotateFlip(Gdiplus::Rotate270FlipNone);

	//		MemG->DrawImage(&bm, Dst);
	//	}
	//	
	//}
}
void SceneManager::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (CurScene == nullptr) return;

	//CurScene->LeftButtonDown(nFlags, point);
}

void SceneManager::Update(float Delta, int frame)
{
	if (CurScene == nullptr) return;
	CurScene->Update(Delta, frame);
	//for(auto& it : CurScene->info)
	//{
	//	if (it->Objtype == eObject_Unit)
	//	{
	//		myUnit* o = reinterpret_cast<myUnit*>(it);
	//		
	//		//frame에따라 현재 오브젝트의 렉트 변화
	//		o->sm.Update();
	//		if (o->sm.GetCurState() == eState_Idle)
	//		{
	//			o->rc = o->moveRc[0];
	//		}
	//		else if (o->sm.GetCurState() == eState_Move)
	//		{
	//			o->rc = o->moveRc[frame];
	//		}
	//		else if (o->sm.GetCurState() == eState_Attack)
	//		{
	//			o->rc = o->atkRc[frame];
	//		}
	//	}
	//}
}

Scene* SceneManager::GetCurScene()
{
	return CurScene;
}


