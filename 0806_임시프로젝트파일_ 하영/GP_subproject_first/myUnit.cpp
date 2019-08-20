#include "pch.h"
#include "MyUnit.h"

MyUnit::MyUnit()
	: Object(EObject::eObject_Unit)
	, AddDelta(0.f)
{
	curTile = std::make_pair(0, 0);
	dstTile = std::make_pair(0, 0);

	mUnitInfo.hp = 100;
	mUnitInfo.move_speed = 1;
	mUnitInfo.atk_distance = 10;
	mUnitInfo.damage = 10;
	
	Isdead = false;

	sm.Add(new State_Idle);
	sm.Add(new State_Move);
	sm.Add(new State_Attack);
	sm.Add(new State_Dead);
}
void MyUnit::Update(float Delta)
{
	if (!Isdead)
	{
		
		AddDelta += Delta;
		
		if (AddDelta > 0.1f)
		{
			frame++;
			AddDelta = 0;

			if (frame > 10)
				frame = 0;
		}
		//상태 변화, 추후 행동 트리에 추가
		UnitBt->Tick();

		if (sm.GetCurState() == eState_Idle)
		{
			rc = moveRc[direction][0];
		}
		else if (sm.GetCurState() == eState_Move)
		{
			int frame_ = frame % moveRc[direction].size();
			rc = moveRc[direction][frame_];
			//Move(Delta);
		}
		else if (sm.GetCurState() == eState_Attack)
		{
			int frame_ = frame % atkRc[direction].size();
			rc = atkRc[direction][frame_];
			//Attack(Delta);
		}
		else if (sm.GetCurState() == eState_Dead)
		{
			rc = moveRc[0][0];
		}
	}
}

void MyUnit::Render(Gdiplus::Graphics* MemG)
{
	if (!Isdead)
	{
		int width = rc.Width;
		int height = rc.Height;
		
		Gdiplus::Rect Dst1(curPos.X - width/4, curPos.Y - height/4, width / 2, height / 2);
		//Gdiplus::Rect Dst1(posRc.X, posRc.Y, width /2, height / 2);
		MemG->DrawImage(ParentImg, Dst1, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}
void MyUnit::CopyObj(MyUnit* dst, int ix, int iy)
{
 	ID = dst->ID;
	name = dst->name;
	mUnitInfo = dst->mUnitInfo;
	for (int i = 0; i < 5; i++)
	{
		moveRc[i] = dst->moveRc[i];
	}
	for (int i = 0; i < 5; i++)
	{
		atkRc[i] = dst->atkRc[i];
	}
	
	curPos.X = ix;
	curPos.Y = iy;
}

void MyUnit::ParserXML()
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	//doc->LoadFile("Xml\\knight.xml");
	/*
	ID:
	0- knight, 1- axeman, 2- darknight,3- electric,4- giant,5- archer,
	6- lumberjack, 7- musket,8- varkirey,9- vavarian,10- vendit,11- wizard
	*/
	if (ID == 0)
	{
		doc->LoadFile("Xml\\knight.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 12; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}

		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 14; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 1)
	{
		doc->LoadFile("Xml\\axeman.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 10; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 2)
	{
		doc->LoadFile("Xml\\darknight.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 10; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 3)
	{
		doc->LoadFile("Xml\\electric.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		
		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 7; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 4)
	{
		doc->LoadFile("Xml\\giant.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 16; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}

		// idle
		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 10; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 5)
	{
		doc->LoadFile("Xml\\archer.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int k = 0; k < 4; k++)
		{
			for (int i = 0; i < 5; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 6)
	{
		doc->LoadFile("Xml\\lumberjack.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 10; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 7)
	{
		doc->LoadFile("Xml\\musket.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{

			for (int i = 0; i < 10; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 10; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 8)
	{
		doc->LoadFile("Xml\\varkirey.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 12; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 9)
	{
		doc->LoadFile("Xml\\vavarian.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 10; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 10)
	{
		doc->LoadFile("Xml\\vendit.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
	if (ID == 11)
	{
		doc->LoadFile("Xml\\wizard.xml");
		tinyxml2::XMLElement* Root = doc->RootElement();
		tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				moveRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
		//공격
		for (int k = 0; k < 5; k++)
		{
			for (int i = 0; i < 7; i++)
			{
				atkRc[k].emplace_back(Node->IntAttribute("x")
					, Node->IntAttribute("y")
					, Node->IntAttribute("w")
					, Node->IntAttribute("h"));
				Node = Node->NextSiblingElement();
			}
		}
	}
}

void MyUnit::Set(SearchTree* mTree)
{
	while (!moveTilePath.empty())
		moveTilePath.pop();
	mTree->FindPath(curTile, dstTile, &moveTilePath);
	mTree->Set(mMap);
	/*else
	{
		if (moveTilePath.empty())
		{
			dstTile.first = 10;
			dstTile.second = 3;

			mTree->FindPath(curTile, dstTile, &moveTilePath);
			mTree->Set(mMap);
		}
	}*/
	
}

void MyUnit::Move(float Delta)
{
	if (moveTilePath.empty())
	{
		return;
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
		int distanceX = tempDstTile.X - strTile.X;
		int distanceY = tempDstTile.Y - strTile.Y;

		//방향
		{
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
		}
		//posRc = map->Infos[i][j].rc; //현재 
		 //위치 이동
		
		curPos.X += (distanceX) / 27 * mUnitInfo.move_speed;
		curPos.Y += (distanceY) / 22 * mUnitInfo.move_speed;

		/*cout << "dstX: " << dstX << ",	dstY: " << dstY << endl;
		cout << "posRc.X: " << posRc.X << ",	posRc.Y: " << posRc.Y << endl;
*/
		//현재 목적지에 캐릭터가 들어왔는지
		if(tempDstTile.Contains(curPos.X,curPos.Y))
		{
			curTile = moveTilePath.top();

			posRc.X = tempDstTile.X;
			posRc.Y = tempDstTile.Y;

			curPos.X = posRc.X + TILESIZEX/2;
			curPos.Y = posRc.Y + TILESIZEY/2;
		}
	}
}

void MyUnit::Attack(float Delta)
{
	if (target == nullptr) std::cout << "targetnull" << std::endl;

	if (target->mUnitInfo.hp > 0)
		target->mUnitInfo.hp -= this->mUnitInfo.damage;
	else
	{
		target->Isdead = true;
		target = nullptr;
	}
}

void MyUnit::ExtraAction(float Delta)
{

}

void MyUnit::CreateBT(BlackBoard* InBB)
{
	UnitBt = new BehaviorTree(this,InBB);
	UnitBt->Init(this, InBB);
}