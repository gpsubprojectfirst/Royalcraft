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
	CreateDeck(EDeck_type::EDeck_Knight,TEXT("Asset\\3.game\\4.ui\\Deck\\Knight.png"));
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
	
	ChooseDeck();
	m_dwKey = 0x00000000;

	m_iSelectedCell = -1;
}

void UIDeckWnd::ChooseDeck()
{
	//보여질 슬롯 덱 4개 고르기
	viewArray = new Deck*[SLOTCNT];

	srand(static_cast<unsigned int>(time(nullptr)));

	int k = rand() % 12;

	for (int i = 0; i < SLOTCNT; i++)
	{
		arrayNum[i] = (EDeck_type)(k % EDeck_Cnt);
		k++;
	}

	for (int i = 0; i < SLOTCNT; i++)
	{
		viewArray[i] = m_mDeck.at(arrayNum[i]);
		viewArray[i]->typeNum = arrayNum[i];
		viewArray[i]->m_iCost = m_mDeck.at(arrayNum[i])->m_iCost;

		viewArray[i]->m_tInfo.fX = (float)(SLOT_ONE_X + (SLOR_ARRANG_X * (i)));
		viewArray[i]->m_tInfo.fY = (float)(SLOT_ONE_Y);
		viewArray[i]->m_tInfo.fSizeX = (float)(SLOT_SIZE_WIDTH);
		viewArray[i]->m_tInfo.fSizeY = (float)(SLOT_SIZE_HEIGHT);

	}

	/*
	Slot1 (167, 808); // gap : 102
	Slot2 (269, 808);
	Slot3 (371, 808);
	Slot4 (473, 808);
	*/
}

int UIDeckWnd::CheckDeck(int randnum)
{
	if (viewArray == nullptr)
		return -1;
	std::srand(static_cast<unsigned int>(time(nullptr)));

	bool bFlag = true;
	while (bFlag)
	{
		bFlag = false;

		for (int i = 0; i < SLOTCNT; i++)
		{
			if (viewArray[i]->typeNum == randnum)
			{
				bFlag = true;
				int k = rand() % eUnit_Cnt;
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
	if (viewArray == nullptr) return;
	m_IsSelectMode = 4;
	//보여질 슬롯 덱 4개 고르기

	std::srand(static_cast<unsigned int>(time(nullptr)));

	
	int idx = m_iSelectedCell;

	int randnum = rand() % eUnit_Cnt;
	arrayNum[idx] = (EDeck_type)CheckDeck(randnum);
	
	for (int i = 0; i < SLOTCNT; i++)
	{
		if( i  == idx)
		{
			viewArray[idx] = m_mDeck.at(arrayNum[idx]);
			viewArray[idx]->typeNum = arrayNum[idx];
		}
		viewArray[i] = m_mDeck.at(arrayNum[i]);
		viewArray[i]->typeNum = arrayNum[i];

		viewArray[i]->m_tInfo.fX = (float)(SLOT_ONE_X + (SLOR_ARRANG_X * (i)));
		viewArray[i]->m_tInfo.fY = (float)(SLOT_ONE_Y);
		viewArray[i]->m_tInfo.fSizeX = (float)(SLOT_SIZE_WIDTH);
		viewArray[i]->m_tInfo.fSizeY = (float)(SLOT_SIZE_HEIGHT);

	}

	m_IsSelectMode = 0;
}

void UIDeckWnd::Update(float Delta)
{
	POINT pt = MouseMgr::GetMousePos();

	m_dwKey = KeyMgr::GetInstance().GetKey();
	
	for (int i = 0; i < SLOTCNT; ++i)
	{
		if (PtInRect(&viewArray[i]->GetRect(), pt))
		{
			m_iSelectedCell = i;
			UIDeckWnd::m_bOnItem = true;
		}
	}
	
	if (m_dwKey & KEY_LBUTTON)
	{
		SelectItem();
	}

	if (m_IsSelectMode == 3)
	{
		ChangeDeck();
	}

	for (int i = 0; i< SLOTCNT; i++)
	{
		if (viewArray == nullptr) continue;
		viewArray[i]->Update(Delta);
	}

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
	Gdiplus::Rect tempRect[SLOTCNT];
	if (UIDeckWnd::m_bOnItem)
	{
		for (int i = 0; i < SLOTCNT; ++i)
		{
			if (m_iSelectedCell == i)
			{
				tempRect[i].X = viewArray[i]->GetRect().left;
				tempRect[i].Y = viewArray[i]->GetRect().top;
				tempRect[i].Width = (int)viewArray[i]->m_tInfo.fSizeX;
				tempRect[i].Height= (int)viewArray[i]->m_tInfo.fSizeY;
				MemG->DrawRectangle(&pen, tempRect[i]);
			}
		}
	}
	
	for (int i = 0; i< SLOTCNT; i++)
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
	case eDeckSlot_One:
		tempInfo.unitID = viewArray[eDeckSlot_One]->typeNum;
		tempInfo.iElixir = viewArray[eDeckSlot_One]->m_iCost;
		m_IsSelectMode = 1;
		break;
	case eDeckSlot_Two:
		tempInfo.unitID = viewArray[eDeckSlot_Two]->typeNum;
		tempInfo.iElixir = viewArray[eDeckSlot_Two]->m_iCost;
		m_IsSelectMode = 1;
		break;
	case eDeckSlot_Three:
		tempInfo.unitID = viewArray[eDeckSlot_Three]->typeNum;
		tempInfo.iElixir = viewArray[eDeckSlot_Three]->m_iCost;
		m_IsSelectMode = 1;
		break;
	case eDeckSlot_Four:
		tempInfo.unitID = viewArray[eDeckSlot_Four]->typeNum;
		tempInfo.iElixir = viewArray[eDeckSlot_Four]->m_iCost;
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

