#include "pch.h"
#include "UITimeEvent.h"
#include "SoundMgr.h"

UITimeEvent::UITimeEvent()
	:runTime(0)
	,curTime(0)
	,tempFRc(nullptr)
	,result(nullptr)
	,curScene(nullptr)
	, blackWnd(0,0, REAL_WINSIZE_X, REAL_WINSIZE_Y)
	, font(_T("Times New Roman"), MY_FONT_SIZE, FontStyleBold, UnitPixel)
	, sbrush(Gdiplus::Color::White)
	, result()
{

}

void UITimeEvent::Init(GameScene* inScene)
{
	if (inScene == nullptr) return;
	SoundMgr::GetInstance()->SoundPlay(8, 0);
	curScene = inScene;

	startUI.ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\gamestart.png"));
	startUI.rc.X = REAL_WINSIZE_X / 4;
	startUI.rc.Y = REAL_WINSIZE_Y / 4;
	startUI.rc.Width = startUI.ParentImg->GetWidth();
	startUI.rc.Height = startUI.ParentImg->GetHeight();

	/*oostUpUI.ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\gamestart.png"));
	boostUpUI.rc.X = REAL_WINSIZE_X / 4;
	boostUpUI.rc.Y = REAL_WINSIZE_Y / 4;
	boostUpUI.rc.Width = startUI.ParentImg->GetWidth();
	boostUpUI.rc.Height = startUI.ParentImg->GetHeight();*/

	tempFRc = new Gdiplus::RectF(0,0,0,0);
	format.SetAlignment(StringAlignmentCenter);
}
void UITimeEvent::Update(int inTime)
{
	runTime = inTime;
	if (runTime != curTime)
	{
		if (inTime >= 0 && inTime <= 3)
		{
			std::cout << "start" << std::endl;
		}
		if (inTime % ENEMY_CREATE_TERM == 0 && inTime > 0)
		{
			CreateEnemy();
		}
		if (inTime == 90)
		{
			//std::cout << "rutime: 90" << std::endl;
		}
	}
	curTime = inTime;
}
void UITimeEvent::Render(Gdiplus::Graphics* MemG)
{
	if (runTime >= 0 && runTime <= 2)
	{
		tempFRc->X = (float)startUI.rc.X;
		tempFRc->Y= (float)(startUI.rc.Y + 10);
		tempFRc->Width = (float)startUI.rc.Width;
		tempFRc->Height = (float)startUI.rc.Height;

		tempstr = "GAME START";
		wide_string = wstring(tempstr.begin(), tempstr.end());
		result = wide_string.c_str();
		
		MemG->FillRectangle(&BRUSH_BLACK_ALPHA, blackWnd);
		MemG->DrawImage(startUI.ParentImg, startUI.rc);
		MemG->DrawString(result, -1, &font, *tempFRc, &format, &sbrush);
	}
	if (runTime == 90)
	{
		//MemG->DrawImage(startText.ParentImg, Text.rc);
	}
}

void UITimeEvent::CreateEnemy()
{
	if (curScene == nullptr) return;

	int x = rand() % 10 + 5;
	int y = 8;

	EUnit_ID unitID = (EUnit_ID)(rand() % eUnit_Cnt);
	MyUnit* mUnit = new MyUnit((MyUnit*)ObjectManager::GetInstance().GetMyUnit(unitID));

	mUnit->ParentImg = curScene->m_vecImg[EScene_Game][unitID + 1];
	mUnit->curTile.first = x;
	mUnit->curTile.second = y;
	mUnit->posRc = curScene->mMap->Infos[x][y].rc;

	mUnit->curPosX = (float)mUnit->posRc.X + (float)(TILESIZEX / 2);
	mUnit->curPosY = (float)mUnit->posRc.Y + (float)(TILESIZEY / 2);

	mUnit->mMap = curScene->mMap;
	mUnit->teamBlue = false;
	curScene->info.emplace_back(mUnit);
	curScene->playUnit.emplace_back(mUnit);
	curScene->blackBoard->UpdateData(curScene->playUnit);
	mUnit->CreateBT(curScene->blackBoard);
}