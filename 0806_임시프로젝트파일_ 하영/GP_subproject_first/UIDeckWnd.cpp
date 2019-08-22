#include "pch.h"
#include "UIDeckWnd.h"


bool UIDeckWnd::m_bOnItem = false;
int UIDeckWnd::m_IsSelectMode = 0;


UIDeckWnd::UIDeckWnd()
{
	Init();
}

UIDeckWnd::~UIDeckWnd()
{
	Release();
}

void UIDeckWnd::Init()
{
	/*
		ID:
		0- knight, 1- axeman, 2- darknight,3- electric,4- giant,5- archer,
		6- lumberjack, 7- musket,8- varkirey,9- vavarian,10- vendit,11- wizard
	*/
	CreateDeck(EDeck_type::EDeck_KNIGHT,TEXT("Asset\\3.game\\4.ui\\Deck\\Knight.png"));
	CreateDeck(EDeck_type::EDeck_Axeman,TEXT("Asset\\3.game\\4.ui\\Deck\\axeman.png"));
	CreateDeck(EDeck_type::EDeck_Darknight,TEXT("Asset\\3.game\\4.ui\\Deck\\darknight.png"));
	CreateDeck(EDeck_type::EDeck_Electric,TEXT("Asset\\3.game\\4.ui\\Deck\\electric.png"));
	CreateDeck(EDeck_type::EDeck_Giant,TEXT("Asset\\3.game\\4.ui\\Deck\\Giant.png"));
	CreateDeck(EDeck_type::EDeck_Archer,TEXT("Asset\\3.game\\4.ui\\Deck\\archer.png"));
	CreateDeck(EDeck_type::EDeck_Lumberjack,TEXT("Asset\\3.game\\4.ui\\Deck\\Lumberjack.png"));
	CreateDeck(EDeck_type::EDeck_Musket,TEXT("Asset\\3.game\\4.ui\\Deck\\musket.png"));
	CreateDeck(EDeck_type::EDeck_Varkirey,TEXT("Asset\\3.game\\4.ui\\Deck\\varkirey.png"));
	CreateDeck(EDeck_type::EDeck_Vavarian,TEXT("Asset\\3.game\\4.ui\\Deck\\vavarian.png"));
	CreateDeck(EDeck_type::EDeck_Vendit,TEXT("Asset\\3.game\\4.ui\\Deck\\vendit.png"));
	CreateDeck(EDeck_type::EDeck_Wizard,TEXT("Asset\\3.game\\4.ui\\Deck\\wizard.png"));
	

	for (int i = 0;i < 12;i++)
	{
		DECKINFO* deckInfo = new DECKINFO();
		deckInfo->pDeck = m_mDeck.at((EDeck_type)i);
		m_liDeckInfo.push_back(deckInfo);
	}
	
	ChooseDeck();
	m_dwKey = 0x00000000;

	m_iSelectedCell = -1;
}
void UIDeckWnd::ChooseDeck()
{
	//º¸¿©Áú ½½·Ô µ¦ 4°³ °í¸£±â
	viewArray = new Deck*[4];
	srand(time(nullptr));
	int k = rand() % 12;

	for (int i = 0; i < 4; i++)
	{
		arrayNum[i] = (EDeck_type)(k % 12);
		k++;
	}

	for (int i = 0; i < 4; i++)
	{
		viewArray[i] = m_mDeck.at(arrayNum[i]);
		viewArray[i]->typeNum = arrayNum[i];
		viewArray[i]->m_iCost = m_mDeck.at(arrayNum[i])->m_iCost;
	}

	viewArray[0]->CopyObj(167, 808);
	viewArray[1]->CopyObj(269, 808);
	viewArray[2]->CopyObj(371, 808);
	viewArray[3]->CopyObj(473, 808);

}

int UIDeckWnd::CheckDeck(int randnum)
{
	srand(time(nullptr));
	bool bFlag = true;
	while (bFlag)
	{
		bFlag = false;

		for (int i = 0; i < 4; i++)
		{
			if (viewArray[i]->typeNum == randnum)
			{
				bFlag = true;
				int k = rand() % 12;
				randnum = k;
			}
			if (bFlag)
				continue;
		}
	}
	return randnum;
}

void UIDeckWnd::ChangeDeck()
{
	m_IsSelectMode = 4;
	//º¸¿©Áú ½½·Ô µ¦ 4°³ °í¸£±â
	srand(time(nullptr));
	
	int idx = m_iSelectedCell;
	
	int randnum = rand() % 12;
	arrayNum[idx] = (EDeck_type)CheckDeck(randnum);
	
	for (int i = 0; i < 4; i++)
	{
		if( i  == idx)
		{
			viewArray[idx] = m_mDeck.at(arrayNum[idx]);
			viewArray[idx]->typeNum = arrayNum[idx];
		}
		viewArray[i] = m_mDeck.at(arrayNum[i]);
		viewArray[i]->typeNum = arrayNum[i];
	}

	viewArray[0]->CopyObj(167, 808);
	viewArray[1]->CopyObj(269, 808);
	viewArray[2]->CopyObj(371, 808);
	viewArray[3]->CopyObj(473, 808);

	m_IsSelectMode = 0;
}

void UIDeckWnd::Update(float Delta)
{
	POINT pt = MouseMgr::GetMousePos();

	m_dwKey = KeyMgr::GetInstance().GetKey();
	
	m_pt.x = LONG(pt.x);
	m_pt.y = LONG(pt.y);

	//167,808 slot1
	//slot 2 269,808
	//slot 371,808
	//slot 473,808
	if ((m_pt.x > 167) && (m_pt.x < 239) && (m_pt.y > 808) && (m_pt.y < 900))
	{
		m_iSelectedCell = 0;
		UIDeckWnd::m_bOnItem = true;
	}
	if ((m_pt.x > 269) && (m_pt.x < 341) && (m_pt.y > 808) && (m_pt.y < 900))
	{
		m_iSelectedCell = 1;
		UIDeckWnd::m_bOnItem = true;
	}
	if ((m_pt.x > 371) && (m_pt.x < 443) && (m_pt.y > 808) && (m_pt.y < 900))
	{
		m_iSelectedCell = 2;
		UIDeckWnd::m_bOnItem = true;
	}
	if ((m_pt.x > 473) && (m_pt.x < 545) && (m_pt.y > 808) && (m_pt.y < 900))
	{
		m_iSelectedCell = 3;
		UIDeckWnd::m_bOnItem = true;
	}

	if (m_dwKey & KEY_LBUTTON)
	{
		SelectItem();
	}

	if (m_IsSelectMode == 3)
	{
		ChangeDeck();
	}

	for (int i = 0; i<4; i++)
	{
		if (viewArray == nullptr) continue;
		viewArray[i]->Update(Delta);
	}

	viewArray[0]->CopyObj(167, 808);
	viewArray[1]->CopyObj(269, 808);
	viewArray[2]->CopyObj(371, 808);
	viewArray[3]->CopyObj(473, 808);
}

void UIDeckWnd::CreateDeck(EDeck_type _eType, const WCHAR* str)
{
	Gdiplus::Image* deckIcon = new Gdiplus::Image(str);
	int cost = ((MyUnit*)ObjectManager::GetInstance().GetMyUnit(_eType))->mUnitInfo.cost;
	Deck* m_deck = new Deck(deckIcon, cost);
	m_mDeck.insert(make_pair(_eType, m_deck));
}

void UIDeckWnd::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Pen pen(Color(255, 255, 255), 5.0f);

	if (UIDeckWnd::m_bOnItem)
	{
		//167,808 slot1
		if (m_iSelectedCell == 0)
		{
			MemG->DrawRectangle(&pen, 167, 808, 72, 92);
		}
		if (m_iSelectedCell == 1)
		{
			//slot 2 269,808
			MemG->DrawRectangle(&pen, 269, 808, 72, 92);
		}
		if (m_iSelectedCell == 2)
		{
			//slot 371,808
			MemG->DrawRectangle(&pen, 371, 808, 72, 92);
		}
		if (m_iSelectedCell == 3)
		{
			//slot 473,808
			MemG->DrawRectangle(&pen, 473, 808, 72, 92);
		}
	}
	
	for (int i = 0; i<4 ; i++)
	{
		viewArray[i]->Render(MemG);
	}
}

void UIDeckWnd::SelectItem()
{
	KeyMgr::GetInstance().SetKey();

	/*if (!UIDeckWnd::m_bOnItem)
		return;*/

	MOUSEINFO tempInfo;
	memset(&tempInfo, 0, sizeof(tempInfo));
	
	
	switch (m_iSelectedCell)
	{
	case 0:
		tempInfo.unitID = viewArray[0]->typeNum;
		tempInfo.iElixir = viewArray[0]->m_iCost;
		m_IsSelectMode = 1;
		break;
	case 1:
		tempInfo.unitID = viewArray[1]->typeNum;
		tempInfo.iElixir = viewArray[1]->m_iCost;
		m_IsSelectMode = 1;
		break;
	case 2:
		tempInfo.unitID = viewArray[2]->typeNum;
		tempInfo.iElixir = viewArray[2]->m_iCost;
		m_IsSelectMode = 1;
		break;
	case 3:
		tempInfo.unitID = viewArray[3]->typeNum;
		tempInfo.iElixir = viewArray[3]->m_iCost;
		m_IsSelectMode = 1;
		break;

	default:
		break;
	}
	
	MouseMgr::GetInstance().SetMouseInfo(tempInfo);
	}


void UIDeckWnd::Release()
{
}

