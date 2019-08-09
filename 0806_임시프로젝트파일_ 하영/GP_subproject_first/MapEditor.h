#pragma once
#include "Scene.h"
#include "pch.h"

class MapEditor :
	public Object
{
public:
	std::vector<PTile>			m_vecTile;
	int		size;

public:
	//void InitTile();
	//PTile CreateTile(int ix, int iy);

public:
	//virtual void Initialize(void);
	//virtual void Progress(void);
	//virtual void Render(Gdiplus::Graphics* MemG);
	//virtual void Release(void);


	MapEditor();
	//~MapEditor();
};

