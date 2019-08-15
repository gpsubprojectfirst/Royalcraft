#pragma once

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fSizeX;
	float	fSizeY;

	tagInfo(void) {}

	tagInfo(float _fx, float _fy)
		: fX(_fx), fY(_fy) {}
}INFO;


typedef struct tagTile
{
	bool		IsMouseOn;
	int			IsUse;
}TILEINFO, *PTile;

typedef struct tagDeck
{
	bool		bCanUse;
	int			iCoolTIme;
}DECKINFO;


typedef struct tagMouse
{
	DWORD	unitID;
	int		iSize;			//�����ϴ� Ÿ�� ����
	POINT	ptTemp;
	int		iElixir;		//�ڿ�
}MOUSEINFO;