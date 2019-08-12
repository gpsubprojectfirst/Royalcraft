#include "pch.h"
#include "myMap.h"


myMap::myMap()
{
	Init();
}
void myMap::Init()
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

	LoadFile();
}


void myMap::Set(CPoint pt)
{

	Point mPoint;
	mPoint.X = pt.x;
	mPoint.Y = pt.y;

	for (int i = 0; i < TILECNTX; ++i)
	{
		for (int j = 0; j < TILECNTY; ++j)
		{
			if (Infos[i][j].rc.Contains(mPoint) && Infos[i][j].flags == 0)
			{
				Infos[i][j].flags = 1;
				//cout << "move" << i << ", " << j << endl;
			
				
				Infos[i][j].img = new Gdiplus::Image(TEXT("Asset\\3.game\\3.tile\\tile.png"));
				break;
			}
		}
	}

}

void myMap::Render(Gdiplus::Graphics* MemG)
{
	for each (GridInfo info in Infos)
	{
		MemG->DrawImage(info.img, info.rc);
	}
}

void myMap::SaveFile()
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	if (!doc)
		return;

	tinyxml2::XMLDeclaration* decl = doc->NewDeclaration();
	doc->InsertFirstChild(decl);

	tinyxml2::XMLElement* Root = doc->NewElement("Root");
	doc->LinkEndChild(Root);

	element = doc->NewElement("map");
	Root->LinkEndChild(element);

	//////////


	int k = 0, l = 0;
	for (int i = 0; i <= REAL_WINSIZE_X; i += TILESIZEX)
	{
		for (int j = 0; j <= REAL_WINSIZE_Y; j += TILESIZEY)
		{
			subelement = doc->NewElement("info");
			element->LinkEndChild(subelement);
			subelement->SetAttribute("flag", Infos[k][l].flags);
			subelement->SetAttribute("rcY", Infos[k][l].rc.Y);
			subelement->SetAttribute("rcX", Infos[k][l].rc.X);
			subelement->SetAttribute("Yidx", l);
			subelement->SetAttribute("Xidx", k);
			++l;
		}
		++k;
		l = 0;
	}

	doc->SaveFile("Xml\\mapData\\mapInfo.xml");

}

void myMap::SetMapData(tinyxml2::XMLElement* node)
{
	int flag = atoi(node->ToElement()->Attribute("flag"));
	int rcY = atoi(node->ToElement()->Attribute("rcY"));
	int rcX = atoi(node->ToElement()->Attribute("rcX"));
	int Yidx = atoi(node->ToElement()->Attribute("Yidx"));
	int Xidx = atoi(node->ToElement()->Attribute("Xidx"));

	
	Infos[Xidx][Yidx].rc = Rect(rcX, rcY, TILESIZEX, TILESIZEY);
	Infos[Xidx][Yidx].flags = flag;

	if (flag == 1)
	{
		Infos[Xidx][Yidx].img = new Gdiplus::Image(TEXT("Asset\\3.game\\3.tile\\tile.png"));
	}
}

void myMap::LoadFile()
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