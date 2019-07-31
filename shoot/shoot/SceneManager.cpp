#include "pch.h"
#include "SceneManager.h"
#include "MainFrm.h"
void Btn::SendLButtonDown()
{
	switch (ID)
	{
	case 0:
		SceneManager::GetInstance().LoadScene(CString("Scene_Game"));
		break;
	case 1:
		PostQuitMessage(0);
		break;
	}
}

void Player::Update(float Delta)
{
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		rc.MoveToXY(rc.left, rc.top - Delta * Vel);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		rc.MoveToXY(rc.left, rc.top + Delta * Vel);
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		rc.MoveToXY(rc.left - Delta * Vel, rc.top);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		rc.MoveToXY(rc.left + Delta * Vel, rc.top);
	}

	AddDelta += Delta;
	if (AddDelta > Rate)
	{
		AddDelta = 0;
		/*SceneManager::GetInstance().GetCurScene()->info.emplace_back(
			new Bullet(temp.Img, rc.CenterPoint().x - 25, rc.CenterPoint().y - rc.Height() * 0.5f, 300, -500));*/
		SceneManager::GetInstance().GetCurScene()->info.emplace_back(
			new Bullet(temp.Img, rc.CenterPoint().x, rc.CenterPoint().y - rc.Height() * 0.5f, 0, -200));
		/*SceneManager::GetInstance().GetCurScene()->info.emplace_back(
			new Bullet(temp.Img, rc.CenterPoint().x + 25, rc.CenterPoint().y - rc.Height() * 0.5f, -300, -500));*/
	}
}


void Scene::Start()
{
	bLoop = false;

	///////////////
	//info 채우는 부분
	bLoop = true;
}

void Scene::Loop(float Delta)
{
	if (!bLoop) return;
	
}

void Scene::End()
{
	bLoop = false;
	for (auto& it : info)
	{
		delete it;
		it = nullptr;
	}

	info.empty();
}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager cm;
	return cm;
}
struct mRect
{
	float left;
	float right;
	float bottom;
	float top;
};
SceneManager::SceneManager()
	: CurScene(nullptr)
{
	
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile("Asset.xml");

	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* Node = Root->FirstChildElement("Data");
	tinyxml2::XMLElement* subNode = Node->FirstChildElement("UV");

	int dataCnt;
	std::vector<mRect>* ImgRect;
	ImgRect = new std::vector<mRect>();

	dataCnt = Node->IntAttribute("Count");

	
	for (int i = 0; i < dataCnt; i++)
	{
		mRect frc;
		frc.left = subNode->FloatAttribute("Left");
		frc.right = subNode->FloatAttribute("Right");
		frc.bottom = subNode->FloatAttribute("Bottom");
		frc.top = subNode->FloatAttribute("Top");

		ImgRect->emplace_back(frc);
		subNode = subNode->NextSiblingElement();
	}
	
	
	Scene* LoginScene = new Scene();
	Scene* GameScene = new Scene();
	
	Btn* n1 = new Btn();
	Btn* n2 = new Btn();

	CImage* cm = new CImage();
	cm->Load(TEXT("Asset\\Asset.png"));

	n1->ParentImg = cm;
	n2->ParentImg = cm;

	n1->ID = 0;
	n2->ID = 1;

	//xml float uv을 int rect로
	std::vector<CRect>* rcVec = new std::vector<CRect>();

	for (auto& it : ImgRect[0])
	{
		CRect rc;
		rc.left = it.left * cm->GetWidth() + 0.5f;
		rc.right = it.right * cm->GetWidth() + 0.5f;
		rc.bottom = it.bottom * cm->GetHeight() + 0.5f;
		rc.top = it.top * cm->GetHeight() + 0.5f;

		rcVec->emplace_back(rc);
	}

	n1->Img.Create(200, 200, cm->GetBPP());
	n2->Img.Create(200,200, cm->GetBPP());
	
	::StretchBlt(n1->Img.GetDC(), 0, 0, 200, 200, cm->GetDC(), 
		rcVec->at(0).left, rcVec->at(0).top, rcVec->at(0).Width(), rcVec->at(0).Height(), SRCCOPY);
	::StretchBlt(n2->Img.GetDC(), 0, 0, 200, 200, cm->GetDC(), 
		rcVec->at(1).left, rcVec->at(1).top, rcVec->at(1).Width(), rcVec->at(1).Height(), SRCCOPY);

	n1->rc = CRect(220, 100, 420, 200);
	n2->rc = CRect(220, 400, 420, 500);

	
	StaticObject* bg = new StaticObject();
	Player* player = new Player();
	Enemy* enemy1 = new Enemy();
	Enemy* enemy2 = new Enemy();
	Enemy* enemy3 = new Enemy();

	CImage* bgImg = new CImage();
	bgImg->Load(TEXT("Asset\\bg.jpg"));

	bg->ParentImg = bgImg;
	player->ParentImg = cm;
	player->temp.ParentImg = cm;

	bg->Img.Create(580, 900, cm->GetBPP());
	player->Img.Create(100, 100, cm->GetBPP());
	enemy1->Img.Create(100, 100, cm->GetBPP());
	enemy2->Img.Create(100, 100, cm->GetBPP());
	enemy3->Img.Create(100, 100, cm->GetBPP());
	player->temp.Img.Create(100, 100, cm->GetBPP());

	::StretchBlt(bg->Img.GetDC(), 0, 0, 580,900, bgImg->GetDC(), 0, 0, bgImg->GetWidth(), bgImg->GetHeight(), SRCCOPY);
	::StretchBlt(player->Img.GetDC(), 0, 0, 100, 100, cm->GetDC(),
		rcVec->at(5).left, rcVec->at(5).top, rcVec->at(5).Width(), rcVec->at(5).Height(), SRCCOPY);
	::StretchBlt(player->temp.Img.GetDC(), 0, 0, 100, 100, cm->GetDC(),
		rcVec->at(5).left, rcVec->at(5).top, rcVec->at(5).Width(), rcVec->at(5).Height(), SRCCOPY);

	::StretchBlt(enemy1->Img.GetDC(), 0, 0, 100, 100, cm->GetDC(),
		rcVec->at(2).left, rcVec->at(2).top, rcVec->at(2).Width(), rcVec->at(2).Height(), SRCCOPY);
	::StretchBlt(enemy2->Img.GetDC(), 0, 0, 100, 100, cm->GetDC(),
		rcVec->at(3).left, rcVec->at(3).top, rcVec->at(3).Width(), rcVec->at(3).Height(), SRCCOPY);
	::StretchBlt(enemy3->Img.GetDC(), 0, 0, 100, 100, cm->GetDC(),
		rcVec->at(4).left, rcVec->at(4).top, rcVec->at(4).Width(), rcVec->at(4).Height(), SRCCOPY);

	bg->rc = CRect(0, 0, 580, 900);
	player->rc = CRect(220, 800, 320, 900);

	enemy1->rc = CRect(0, -1200, 100, -1100);
	enemy2->rc = CRect(200, -1200, 300, -1100);
	enemy3->rc = CRect(400, -1200, 500, -1100);
	
	player->temp.rc = CRect(0, 0, 25, 25);

	GameScene->info.emplace_back(bg);
	GameScene->info.emplace_back(player);
	GameScene->info.emplace_back(enemy1);
	GameScene->info.emplace_back(enemy2);
	GameScene->info.emplace_back(enemy3);

	LoginScene->info.emplace_back(n1);
	LoginScene->info.emplace_back(n2);

	LoginScene->Name = "Scene_Start";
	GameScene->Name = "Scene_Game";
	
	mScene.emplace_back(LoginScene);
	mScene.emplace_back(GameScene);
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

void SceneManager::RenderScene(CDC* pDC)
{
	if (CurScene == nullptr) return;
	if (pDC == nullptr) return;
	
	for (auto& it : CurScene->info)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		it->Img.Draw(pDC->GetSafeHdc(), it->rc);
	}
}

Scene* SceneManager::GetCurScene()
{
	return CurScene;
}

void SceneManager::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (CurScene == nullptr) return;

	for (auto& it : CurScene->info)
	{
		if (it->Objtype== eObjectType_Btn && it->rc.PtInRect(point))
		{
			Btn* o = reinterpret_cast<Btn*>(it);
			o->SendLButtonDown();
		}
	}
}

void SceneManager::Update(float Delta)
{
	if (CurScene == nullptr) return;

	std::vector<Enemy*> enemyVec;
	int nSize = CurScene->info.size();
	for (int i = 0; i < nSize; ++i)
	{
		if (CurScene->info[i]->Enable == false) continue;

		if (CurScene->info[i]->Objtype == eObjectType_Enemy)
		{
			enemyVec.emplace_back(static_cast<Enemy*>(CurScene->info[i]));
		}
	}

	int nCnt = CurScene->info.size();
	for (auto it = 0; it < nCnt; ++it)
	{
		if (CurScene->info[it] == nullptr) continue;
		if (CurScene->info[it]->Enable == false) continue;

		CurScene->info[it]->Update(Delta);

		if (CurScene->info[it]->Objtype == eObjectType_Bullet)
		{
			Bullet* c = static_cast<Bullet*>((CurScene->info[it]));
			if (c->IsCullBull(enemyVec))
			{
				CurScene->info[it]->Enable = false;
			}
		}
	}
}
