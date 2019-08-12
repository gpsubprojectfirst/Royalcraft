#pragma once

#include "Object.h"
class Object;

class GridInfo
{
public:
	Gdiplus::Rect rc;
	Gdiplus::Image* img;
	int flags;
};

class myMap
{
public:
	int size;
	Gdiplus::Rect rc; // 현재 로드된 Asset에서 불러올 이미지의 rect
	Gdiplus::Rect posRc; //현재 타일의 렉트
	Gdiplus::Image* ParentImg;
	GridInfo Infos[TILECNTX][TILECNTY];

	//map xml
	tinyxml2::XMLElement* element;
	tinyxml2::XMLElement* subelement;
	std::vector<int> m_vecTileInfo;

public:
	myMap();
	void Init();
	void Set(CPoint pt);
	void Render(Gdiplus::Graphics* MemG);
	void SaveFile();
	void LoadFile();
	void SetMapData(tinyxml2::XMLElement* node);
};