#pragma once
#include "Object.h"
#include "Deck.h"

class UIDeckWnd :
	public Object
{
private:
	std::map<EDeck_type, Deck*> m_mDeck;
	std::list<DECKINFO*>	m_liDeckInfo;		//slot
	bool		m_bArray[4];
	POINT		m_pt;
	POINT		pSet;
	int			m_iSelectedCell;
	int			m_itempCell;
	int			m_iIndex;

	DWORD	m_dwKey;
	bool	m_bOpenComplete;   //  ¿µ¿ª¿¡¼­ ¹þ¾î³´À» ¶§

private:
	void SetArray();
	void SelectItem();
	/*void RenderIcon(Gdiplus::Graphics* MemG);*/

public:
	
    static bool		m_bOnItem;
	static int		m_IsSelectMode;


public:
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Release();
	void CreateDeck(EDeck_type _eType, const WCHAR* str);
	//void Open();
	//void Close();

public:
	UIDeckWnd(void);
	~UIDeckWnd(void);
};

