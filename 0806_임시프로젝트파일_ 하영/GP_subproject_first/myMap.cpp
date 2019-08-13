#include "pch.h"
#include "MyMap.h"


MyMap::MyMap()
{
	Init();
}
void MyMap::Init()
{
	int k = 0, l = 0;
	for (int i = 0; i <= REAL_WINSIZE_X; i += TILESIZEX)
	{
		for (int j = 0; j <= REAL_WINSIZE_Y; j += TILESIZEY)
		{

			Infos[k][l].rc = Rect(i, j, TILESIZEX, TILESIZEY);
			Infos[k][l].flags = 0;
			
			++l;

		}
		++k;
		l = 0;
	}

}

void MyMap::Render(Gdiplus::Graphics* MemG)
{
	for each (GridInfo info in Infos)
	{
		MemG->DrawImage(info.img, info.rc);
	}
}

void MyMap::SetMapData(tinyxml2::XMLElement* node)
{
	int flag = atoi(node->ToElement()->Attribute("flag"));
	int rcY = atoi(node->ToElement()->Attribute("rcY"));
	int rcX = atoi(node->ToElement()->Attribute("rcX"));
	int Yidx = atoi(node->ToElement()->Attribute("Yidx"));
	int Xidx = atoi(node->ToElement()->Attribute("Xidx"));


	Infos[Xidx][Yidx].rc = Rect(rcX, rcY, TILESIZEX, TILESIZEY);
	Infos[Xidx][Yidx].flags = flag;


	//오브젝트가 갈 수 없는 타일
	if (flag == 1)
	{
		Infos[Xidx][Yidx].img = new Gdiplus::Image(TEXT("Asset\\3.game\\3.tile\\Tile.png"));
	}

	//오브젝트 생성 타일
	if (flag == 2)
	{
		Infos[Xidx][Yidx].img = new Gdiplus::Image(TEXT("Asset\\3.game\\3.tile\\Tile1.png"));
	}
}

void MyMap::LoadFile()
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile("Xml\\mapData\\mapInfo.xml");

	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* Node = Root->FirstChildElement("map")->FirstChildElement("info");
	tinyxml2::XMLElement* lastNode = Root->FirstChildElement("map")->LastChildElement("info");
	SetMapData(Node);

	do {
		Node = Node->NextSiblingElement();
		SetMapData(Node);
	} while (Node != lastNode);

	tinyxml2::XMLDocument Clear();
}