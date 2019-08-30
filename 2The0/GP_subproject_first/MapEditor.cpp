#include "pch.h"
#include "MapEditor.h"



MapEditor::MapEditor()
	:map(nullptr)
	, subelement(nullptr)
	, element(nullptr)
{
}

void MapEditor::Init()
{
	map = new MyMap();
	m_vecEditor.push_back(new Gdiplus::Image(TEXT("Asset\\3.game\\2.map\\level_spell_arena_tex.png")));
	LoadFile();
}

void MapEditor::Set(CPoint pt)
{
	Point mPoint;
	mPoint.X = pt.x;
	mPoint.Y = pt.y;

	for (int i = 0; i < TILECNTX; ++i)
	{
		for (int j = 0; j < TILECNTY; ++j)
		{
			if (map->Infos[i][j].rc.Contains(mPoint) && map->Infos[i][j].flags == 0)
			{
				map->Infos[i][j].flags = 1;
				map->Infos[i][j].img = new Gdiplus::Image(TEXT("Asset\\3.game\\3.tile\\Tile.png"));
				break;
			}
		}
	}
}

void MapEditor::Render(Gdiplus::Graphics* MemG)
{
	// 배경
	Gdiplus::Rect Dst1(0, 0, m_vecEditor[0]->GetWidth(), m_vecEditor[0]->GetHeight());
	MemG->DrawImage(m_vecEditor[0], Dst1);

	for each (GridInfo info in map->Infos)
	{
		MemG->DrawImage(info.img, info.rc);
	}
}

void MapEditor::SaveFile()
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


	int k = 0, l = 0;
	for (int i = 0; i <= REAL_WINSIZE_X; i += TILESIZEX)
	{
		for (int j = 0; j <= REAL_WINSIZE_Y; j += TILESIZEY)
		{
			subelement = doc->NewElement("info");
			element->LinkEndChild(subelement);
			subelement->SetAttribute("flag", map->Infos[k][l].flags);
			subelement->SetAttribute("rcY", map->Infos[k][l].rc.Y);
			subelement->SetAttribute("rcX", map->Infos[k][l].rc.X);
			subelement->SetAttribute("Yidx", l);
			subelement->SetAttribute("Xidx", k);
			++l;
		}
		++k;
		l = 0;
	}

	doc->SaveFile("Xml\\mapData\\mapInfo.xml");

}

void MapEditor::SetMapData(tinyxml2::XMLElement* node)
{
	int flag = atoi(node->ToElement()->Attribute("flag"));
	int rcY = atoi(node->ToElement()->Attribute("rcY"));
	int rcX = atoi(node->ToElement()->Attribute("rcX"));
	int Yidx = atoi(node->ToElement()->Attribute("Yidx"));
	int Xidx = atoi(node->ToElement()->Attribute("Xidx"));


 	map->Infos[Xidx][Yidx].rc = Rect(rcX, rcY, TILESIZEX, TILESIZEY);
	map->Infos[Xidx][Yidx].flags = flag;
	

	//오브젝트가 갈 수 없는 타일
	if (flag == 1)
	{
		map->Infos[Xidx][Yidx].img = new Gdiplus::Image(TEXT("Asset\\3.game\\3.tile\\Tile.png"));
	}

	//오브젝트 생성 타일
	if (flag == 2)
	{
		map->Infos[Xidx][Yidx].img = new Gdiplus::Image(TEXT("Asset\\3.game\\3.tile\\Tile1.png"));
	}
}

void MapEditor::LoadFile()
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

	doc->Clear();

	
}

void MapEditor::Update(float Delta)
{
	if (GetAsyncKeyState(VK_F1) & 0x8001)
	{
		SaveFile();
	}
}

void MapEditor::SendLButtonDown(UINT nFlags, CPoint point)
{
	Set(point);
}

