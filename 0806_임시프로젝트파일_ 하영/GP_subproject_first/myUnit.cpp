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
		//posRc = map->Infos[i][j].rc; //���� ��ġ �̵�
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
