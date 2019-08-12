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
	Gdiplus::Rect rc; // ���� �ε�� Asset���� �ҷ��� �̹����� rect
	Gdiplus::Rect posRc; //���� Ÿ���� ��Ʈ
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