#pragma once

#include "Deck.h"



typedef struct tagTile
{
	bool		IsMouseOn;
	int			IsUse;
}TILEINFO, *PTile;

typedef struct tagDeck
{
	bool		bCanUse;
	int			iCoolTIme;
	int			iDeckPosX;
	int			iDeckPosY;
	int			iDeckSizeX;
	int			iDeckSizeY;
	Deck*		pDeck;
}DECKINFO;

typedef struct tagMouse
{
	DWORD	unitID;
	int		iSize;			//�����ϴ� Ÿ�� ����
	POINT	ptTemp;
	int		iElixir;		//�ڿ�
}MOUSEINFO;