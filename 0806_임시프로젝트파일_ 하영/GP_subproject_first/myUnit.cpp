#include "pch.h"
#include "MyUnit.h"

MyUnit::MyUnit()
	: Object(EObject::eObject_Unit)
	, AddDelta(0.f)
{
	curTile = std::make_pair(0, 0);
	dstTile = std::make_pair(0, 0);

	move_speed = 1;

	sm.Add(new State_Idle);
	sm.Add(new State_Move);
	sm.Add(new State_Attack);

	//bt추가
}
void MyUnit::Update(float Delta)
{
	AddDelta += Delta;
	if (AddDelta > 0.2f)
	{
		frame++;
		AddDelta = 0;
		if (frame > 10)
			frame = 0;
	}
	//상태 변화, 추후 행동 트리에 추가
	if (curTile != dstTile)
		sm.ChangeState(eState_Move);
	else
		sm.ChangeState(eState_Idle);
	
	if (sm.GetCurState() == eState_Idle)
	{
		rc = moveRc[direction][0];
	}
	else if (sm.GetCurState() == eState_Move)
	{
		rc = moveRc[direction][frame];
		Move(Delta);
	}
	else if (sm.GetCurState() == eState_Attack)
	{
		rc = atkRc[frame];
		Attack(Delta);
	}
}

void MyUnit::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;

	Gdiplus::Rect Dst1(posRc.X, posRc.Y, width, height);
	MemG->DrawImage(ParentImg, Dst1, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
}
void MyUnit::CopyObj(MyUnit* dst, int ix, int iy)
{
 	ID = dst->ID;
	name = dst->name;
	for (int i = 0; i < 5; i++)
	{
		moveRc[i] = dst->moveRc[i];
	}
	atkRc = dst->atkRc;
	Gdiplus::Rect Dst(ix, iy, ix+50, iy+50);
	posRc = Dst;
}

void MyUnit::ParserXML()
{
	if (ID == 0)
	{
		tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
		doc->LoadFile("Xml\\knight.xml");

		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		// 이동
		for (int k = 0; k < 4;k++)
		{
			for (int i = 0; i < 12; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
			for (int i = 0; i < 12; i++)
			{
				Node = Node->NextSiblingElement();
			}
		}
		for (int i = 0; i < 12; i++)
		{
			moveRc[4].emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
			Node = Node->NextSiblingElement();
		}
		// idle
		for (int i = 108; i < 116;i++)
		{
			Node = Node->NextSiblingElement();
		}
		//공격
		for (int i = 116; i < 130; i++)
		{
			atkRc.emplace_back(Node->IntAttribute("x")
				, Node->IntAttribute("y")
				, Node->IntAttribute("w")
				, Node->IntAttribute("h"));
			Node = Node->NextSiblingElement();
		}
	}
	
}
void MyUnit::Set(CPoint pt, MyMap* map,SearchTree* mTree)
{
	/*if (curTile == dstTile)
	{
		dstTile.first = 0; 
		dstTile.second = 0;
	}*/
	for (int i = 0; i < TILECNTX; ++i)
	{
		for (int j = 0; j < TILECNTY; ++j)
		{

			if (map->Infos[i][j].rc.Contains(pt.x,pt.y) && map->Infos[i][j].flags == 0)
			{
				//map->Infos[i][j].flags = 1;
			
				dstTile.first = i;
				dstTile.second = j;

				cout << "dst" << i << ", " << j << endl;
				break;
			}
		}
	}
	while (!moveTilePath.empty())
		moveTilePath.pop();
	mTree->FindPath(curTile, dstTile, &moveTilePath);
}

void MyUnit::Move(float Delta)
{
	if (moveTilePath.empty())
	{
		return;
	}

	AddDelta += Delta;
	
	if (AddDelta > 0.1f)
	{
		AddDelta = 0;
	}

	//moveTilePath큐에 이동경로가 저장되어있음
	if (curTile == moveTilePath.top())
	{
		moveTilePath.pop();
	}
	else
	{
		//시작 좌표의 타일 렉트 가져오기
		Gdiplus::Rect strTile = mMap->Infos[curTile.first][curTile.second].rc;
		
		//다음 목적지 좌표의 타일 렉트 가져오기
		int dstX = moveTilePath.top().first;
		int dstY = moveTilePath.top().second;
		Gdiplus::Rect tempDstTile = mMap->Infos[dstX][dstY].rc;
		
		//거리 계산
		//this->curPos.first += this->move_speed * Delta;
		float distanceX = tempDstTile.X - strTile.X;
		float distanceY = tempDstTile.Y - strTile.Y;

		//방향
		if (distanceX == 0 && distanceY > 0)
		{
			direction = 0;
		}
		if (distanceX > 0 && distanceY > 0)
		{
			direction = 1;
		}
		if (distanceX > 0 && distanceY == 0)
		{
			direction = 2;
		}
		if (distanceX > 0 && distanceY < 0)
		{
			direction = 3;
		}
		if (distanceX == 0 && distanceY < 0)
		{
			direction = 4;
		}
		//posRc = map->Infos[i][j].rc; //현재 위치 이동
		
		posRc.X += (distanceX )  * 0.1;
		posRc.Y += (distanceY ) * 0.1;
		
		/*cout << "dstX: " << dstX << ",	dstY: " << dstY << endl;
		cout << "posRc.X: " << posRc.X << ",	posRc.Y: " << posRc.Y << endl;
*/
		//현재 목적지에 캐릭터가 들어왔는지
		if(abs(posRc.X - tempDstTile.X) < 10 &&
			abs(posRc.Y - tempDstTile.Y) < 10)
		{
			curTile = moveTilePath.top();
			posRc.X = tempDstTile.X;
			posRc.Y = tempDstTile.Y;
		}
	}
}

void MyUnit::Attack(float Delta)
{

}

void MyUnit::ExtraAction(float Delta)
{

}
