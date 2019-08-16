#pragma once
#include "Object.h"

class UIDeckWnd :
	public Object
{
private:
	DECKINFO	m_tDeckInfo[4];
	bool		m_bArray[4];
	POINT		m_pt;
	POINT		pSet;
	int			m_iSelectedCell;
	int			m_itempCell;
	int			m_iIndex;
	bool		m_bOnItem;

	DWORD	m_dwKey;
	bool	m_bOpenComplete;   //  ¿µ¿ª¿¡¼­ ¹þ¾î³´À» ¶§

private:
	void SetArray();
	void SelectItem();
	/*void RenderIcon(Gdiplus::Graphics* MemG);
*/
public:
	Gdiplus::Image* deckIcon;


public:
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Release();

	//void Open();
	//void Close();

public:
	UIDeckWnd(void);
	~UIDeckWnd(void);
};

