#include "pch.h"
#include "myUnit.h"

myUnit::myUnit()
	: Object(EObject::eObject_Unit)
	, AddDelta(0.f)
{
	curTile = std::make_pair(0, 0);
	dstTile = std::make_pair(0, 0);

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
	sm.Update();
	if (sm.GetCurState() == eState_Idle)
	{
		rc = moveRc[0];
	}
	else if (sm.GetCurState() == eState_Move)
	{
		rc = moveRc[frame];
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

void myUnit::Set(CPoint pt, myMap* map)
{
	for (int i = 0; i < 101; ++i)
	{
		for (int j = 0; j < 163; ++j)
		{

			if (map->Infos[i][j].rc.Contains(pt.x,pt.y) && map->Infos[i][j].flags == 0)
			{
				map->Infos[i][j].flags = 1;
				posRc = map->Infos[i][j].rc; //현재 위치 이동
			
				dstTile.first = i;
				dstTile.second = j;

				cout << "dst" << i << ", " << j << endl;
				break;
			}
		}
	}
	
}
void myUnit::SchPath(myMap* map)
{

}
void myUnit::Move(float Delta)
{
	//길찾기 알고리즘, delta
	//현위치 기준으로 갈수있는 타일 검색
	//거리 계산
	//this->curPos.first += this->move_speed * Delta;

}

void myUnit::Attack(float Delta)
{

}

void myUnit::ExtraAction(float Delta)
{

}
