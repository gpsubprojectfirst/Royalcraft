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
	//상태 변화, 추후 행동 트리에 추가
	if (curTile != dstTile)
		sm.ChangeState(eState_Move);
	else
		sm.ChangeState(eState_Idle);
	
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
	/*if (curTile == dstTile)
	{
		dstTile.first = 0; 
		dstTile.second = 0;
	}*/
	for (int i = 0; i < 65; ++i)
	{
		for (int j = 0; j < 97; ++j)
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
		//posRc = map->Infos[i][j].rc; //현재 위치 이동
		posRc.X += (distanceX )  * 0.1 ;
		posRc.Y += (distanceY ) * 0.1 ;
		//cout << "posRc.X: " << posRc.X << ",	posRc.Y: " << posRc.Y << endl;

		if (mMap->Infos[dstX][dstY].rc.Contains( posRc.X,posRc.Y))
			curTile = moveTilePath.top();
	}
}

void myUnit::Attack(float Delta)
{

}

void myUnit::ExtraAction(float Delta)
{

}
