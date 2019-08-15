#include "pch.h"
#include "UIDeckWnd.h"

enum ICON
{
	ICON_SLOT,
	ICON_KNIGHT,
	ICON_BARBARIAN,
	ICON_GIANT,
	ICON_END,
};

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
	deckIcon = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\knigth_profile.png"));
	/*for (int i = 0; i < 4; ++i)
	{
		m_tDeckInfo[i].bCanUse = true;
		m_tDeckInfo[i].iCoolTIme = 0;

	}*/

	
	m_dwKey = 0x00000000;
	pSet.x = 0;
	pSet.y = 0;

	m_iSelectedCell = 0;
	m_itempCell = 0;
	m_iIndex = 0;

	for (int i = 0; i < 4; ++i)
	{
		m_bArray[i] = false;
	}

	m_bOpenComplete = false;
}
   
void UIDeckWnd::Update(float Delta)
{
	POINT pt = MouseMgr::GetMousePos();
	m_dwKey = KeyMgr::GetInstance().GetKey();
	if (m_dwKey==  1)
	{
		std::cout << m_dwKey;
	}
	std::cout << pt.x << "," << pt.y << endl;
	
	m_pt.x = LONG(pt.x);
	m_pt.y = LONG(pt.y);

	if ((m_pt.x > 167) && (m_pt.x < 239) && (m_pt.y > 808) && (m_pt.y < 900))
	{
		m_bOnItem = true;
	}
	else
	{
		m_bOnItem = false;
	}

	if (m_bOnItem)
	{
		pSet.x = 8 + (31 * (m_pt.x / 31)) + 72;
		pSet.y = 28 + (31 * (m_pt.y / 31)) - 92;
		SetArray();
	}
	else
	{
		m_bArray[m_iSelectedCell] = false;
		m_iSelectedCell = -1;
	}


	if (m_dwKey & KEY_LBUTTON)
	{
		MouseMgr::GetInstance().GetMouseInfo().ptTemp.x = m_pt.x;
		MouseMgr::GetInstance().GetMouseInfo().ptTemp.y = m_pt.y;
		SelectItem();
	}
}

void UIDeckWnd::Render(Gdiplus::Graphics* MemG)
{
	if (m_bOnItem)
	{
		//167,808 slot1 Knight
		Gdiplus::Pen pen(Color(255, 0, 0), 10.0f);
		MemG->DrawRectangle(&pen, 167, 808, 72, 92);
	}

	//Knight Image
	Gdiplus::Rect rc(167, 808, 72, 92);
	MemG->DrawImage(deckIcon, rc);

	
}


void UIDeckWnd::SetArray()
{
	/*int x, y;

	if (m_itempCell != m_iSelectedCell)
	{
		m_itempCell = m_iSelectedCell;
	}

	m_bArray[m_iSelectedCell] = false;

	x = (pSet.x) / 72;
	y = (pSet.y) / 92;
	m_iSelectedCell = (y - 1) * 4 + x;

	if (m_iSelectedCell > 4)
		m_iSelectedCell = 4;

	if (!m_bArray[m_iSelectedCell])
	{
		m_bArray[m_iSelectedCell] = true;
	}*/
}


void UIDeckWnd::SelectItem()
{
	KeyMgr::GetInstance().SetKey();

	if (!m_bOnItem)
		return;

	MOUSEINFO tempInfo;
	memset(&tempInfo, 0, sizeof(tempInfo));
	if (m_iSelectedCell < 5 && m_bOnItem)
		*m_pIsSelectMode = true;
	m_iSelectedCell = 1;
	switch (m_iSelectedCell)
	{
	case ICON_KNIGHT:

		tempInfo.unitID = UNIT_Knight;
		tempInfo.iSize = 1;
		tempInfo.iElixir = 3;
		break;
	
	default:
		break;
	}

	MouseMgr::GetInstance().SetMouseInfo(tempInfo);
}


void UIDeckWnd::Release()
{
}

