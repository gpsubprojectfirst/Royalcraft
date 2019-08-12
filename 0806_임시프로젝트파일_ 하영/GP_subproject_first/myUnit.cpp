#include "pch.h"
#include "myUnit.h"

myUnit::myUnit()
	: Object(EObject::eObject_Unit)
	, AddDelta(0.f)
{
	curTile = std::make_pair(0, 0);
	dstTile = std::make_pair(0, 0);

	move_speed = 1;

	sm.Add(new State_Idle);
	sm.Add(new State_Move);
	sm.Add(new State_Attack);
}
void myUnit::Update(float Delta)
{
	AddDelta += Delta;
	if (AddDelta > 0.2f)
	{
		frame++;
		AddDelta = 0;
		if (frame > 10)
			frame = 0;
	}
	//���� ��ȭ, ���� �ൿ Ʈ���� �߰�
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

void myUnit::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;

	Gdiplus::Rect Dst1(posRc.X, posRc.Y, width, height);
	MemG->DrawImage(ParentImg, Dst1, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
}
void myUnit::parserXML()
{
	if (ID == 0)
	{
		tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
		doc->LoadFile("Xml\\knight.xml");

		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		// �̵�
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
		//����
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
void myUnit::Set(CPoint pt, myMap* map,SearchTree* mTree)
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
				map->Infos[i][j].flags = 1;
			
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

void myUnit::Move(float Delta)
{
	if (moveTilePath.empty())
	{
		return;
	}

	float AddDelta = 0;
	AddDelta += Delta;
	
	if (AddDelta > 0.1f)
	{
		AddDelta = 0;
	}

	//moveTilePathť�� �̵���ΰ� ����Ǿ�����
	if (curTile == moveTilePath.top())
	{
		moveTilePath.pop();
	}
	else
	{
		//���� ��ǥ�� Ÿ�� ��Ʈ ��������
		Gdiplus::Rect strTile = mMap->Infos[curTile.first][curTile.second].rc;
		
		//���� ������ ��ǥ�� Ÿ�� ��Ʈ ��������
		int dstX = moveTilePath.top().first;
		int dstY = moveTilePath.top().second;
		Gdiplus::Rect tempDstTile = mMap->Infos[dstX][dstY].rc;
		
		//�Ÿ� ���
		//this->curPos.first += this->move_speed * Delta;
		float distanceX = tempDstTile.X - strTile.X;
		float distanceY = tempDstTile.Y - strTile.Y;

		//����
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
		//posRc = map->Infos[i][j].rc; //���� ��ġ �̵�
		
		posRc.X += (distanceX )  * 0.1;
		posRc.Y += (distanceY ) * 0.1;
		
		cout << "dstX: " << dstX << ",	dstY: " << dstY << endl;
		cout << "posRc.X: " << posRc.X << ",	posRc.Y: " << posRc.Y << endl;

		//���� �������� ĳ���Ͱ� ���Դ���
		if(abs(posRc.X - tempDstTile.X) < 10 &&
			abs(posRc.Y - tempDstTile.Y) < 10)
		{
			curTile = moveTilePath.top();
			posRc.X = tempDstTile.X;
			posRc.Y = tempDstTile.Y;
		}
	}
}

void myUnit::Attack(float Delta)
{

}

void myUnit::ExtraAction(float Delta)
{

}
