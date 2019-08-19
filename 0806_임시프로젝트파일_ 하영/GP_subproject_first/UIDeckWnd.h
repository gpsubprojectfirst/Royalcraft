#pragma once
#include "Object.h"
#include "Deck.h"

class UIDeckWnd :
	public Object
{
private:
	std::map<EDeck_type, Deck*> m_mDeck;
	std::list<DECKINFO*>	m_liDeckInfo;		//slot
	POINT		m_pt;
	//POINT		pSet;
	int			m_iSelectedCell;
	DWORD	m_dwKey;

private:
	void SelectItem();

public:
    static bool		m_bOnItem;
	static int		m_IsSelectMode;

public:
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Release();
	void CreateDeck(EDeck_type _eType, const WCHAR* str);


public:
	UIDeckWnd(void);
	~UIDeckWnd(void);
};

