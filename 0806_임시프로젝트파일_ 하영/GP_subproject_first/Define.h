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
	float	iX;
	float	iY;
	float	iSizeX;
	float	iSizeY;

	bool bEnable;

}TILEINFO, *PTile;

typedef struct tagDeck
{
	bool		bCanUse;
	int			iCoolTIme;
}DECKINFO;