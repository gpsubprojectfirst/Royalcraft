#pragma once
#include "Object.h"
#include "Deck.h"

#define SLOTCNT 4
class UIDeckWnd :
	public Object
{
private:
	std::map<EDeck_type, Deck*> m_mDeck;
	Deck** viewArray;
	EDeck_type arrayNum[SLOTCNT];
	
	int			m_iSelectedCell;
	DWORD		m_dwKey;

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
	void ChooseDeck();
	void ChangeDeck();
	int CheckDeck(int idx);

public:
	UIDeckWnd(void);
	~UIDeckWnd(void);
};

