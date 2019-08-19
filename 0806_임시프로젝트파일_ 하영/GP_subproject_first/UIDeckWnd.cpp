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
	

	DECKINFO* deckInfo = new DECKINFO();
	Deck* tempDeck = new Deck();
	deckInfo->pDeck = m_mDeck.at(EDeck_KNIGHT);
	deckInfo->pDeck->CopyObj(167, 808);
	m_liDeckInfo.push_back(deckInfo);
	

	m_dwKey = 0x00000000;

}

void UIDeckWnd::Update(float Delta)
{
	POINT pt = MouseMgr::GetMousePos();

	m_dwKey = KeyMgr::GetInstance().GetKey();
	
	m_pt.x = LONG(pt.x);
	m_pt.y = LONG(pt.y);

	if ((m_pt.x > 167) && (m_pt.x < 239) && (m_pt.y > 808) && (m_pt.y < 900))
	{
		m_iSelectedCell = 1;
		UIDeckWnd::m_bOnItem = true;
	}
	else
	{
		UIDeckWnd::m_bOnItem = false;
	}

	if (m_dwKey & KEY_LBUTTON)
	{
		SelectItem();
	}

	
	for (auto& it : this->m_liDeckInfo)
	{
		if (it == nullptr) continue;
		it->pDeck->Update(Delta);
	}
}

void UIDeckWnd::CreateDeck(EDeck_type _eType, const WCHAR* str)
{
	Gdiplus::Image* deckIcon = new Gdiplus::Image(str);
	Deck* m_deck = new Deck(deckIcon);
	m_mDeck.insert(make_pair(_eType, m_deck));
}

void UIDeckWnd::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Pen pen(Color(255, 255, 255), 5.0f);

	if (UIDeckWnd::m_bOnItem)
	{
		//167,808 slot1 Knight
		MemG->DrawRectangle(&pen, 167, 808, 72, 92);

	}

	//slot 2 269,808
	Gdiplus::Pen pen1(Color(255, 255, 255), 5.0f);
	MemG->DrawRectangle(&pen, 269, 808, 72, 92);


	//slot 371,808
	Gdiplus::Pen pen2(Color(255, 255, 255), 5.0f);
	MemG->DrawRectangle(&pen, 371, 808, 72, 92);


	//slot 473,808
	Gdiplus::Pen pen3(Color(255, 255, 255), 5.0f);
	MemG->DrawRectangle(&pen, 473, 808, 72, 92);

	for (auto& it : this->m_liDeckInfo)
	{
		if (it == nullptr) continue;
		it->pDeck->Render(MemG);
	}
}

void UIDeckWnd::SelectItem()
{
	KeyMgr::GetInstance().SetKey();

	/*if (!UIDeckWnd::m_bOnItem)
		return;*/

	MOUSEINFO tempInfo;
	memset(&tempInfo, 0, sizeof(tempInfo));
	m_IsSelectMode = 1;
	m_iSelectedCell = 0;
	switch (m_iSelectedCell)
	{
	/*case ICON_KNIGHT:

		tempInfo.unitID = UNIT_Knight;
		tempInfo.iSize = 1;
		tempInfo.iElixir = 3;
		break;*/
	
	default:
		break;
	}
	//MouseMgr::GetInstance().SetMouseInfo(tempInfo);
}


void UIDeckWnd::Release()
{
}

