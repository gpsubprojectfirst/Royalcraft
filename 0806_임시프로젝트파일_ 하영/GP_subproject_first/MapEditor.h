#pragma once
#include "Scene.h"
#include "pch.h"


class myMap;

class MapEditor :
	public Scene
{
public:
	myMap* map;
	std::vector<Gdiplus::Image*>	m_vecEditor;
	//map xml
	tinyxml2::XMLElement* element;
	tinyxml2::XMLElement* subelement;


public:
	void Set(CPoint pt);
	void Render(Gdiplus::Graphics* MemG);
	void SaveFile();
	void SetMapData(tinyxml2::XMLElement* node);
	void LoadFile();
	void Update(float Delta);
	void SendLButtonDown(UINT nFlags, CPoint point);

	MapEditor();
	//~MapEditor();
};

