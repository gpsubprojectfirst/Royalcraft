#pragma once

#include "Object.h"
#include "MapEditor.h"
class Object;

class GridInfo
{
public:
	Gdiplus::Rect rc;
	Gdiplus::Image* img;
	int flags;
};

class MyMap
{
public:
	GridInfo Infos[TILECNTX][TILECNTY];
	MapEditor* editor;

public:
	void Render(Gdiplus::Graphics* MemG);
	void LoadFile();
	void SetMapData(tinyxml2::XMLElement* node);
	MyMap();
	void Init();
};