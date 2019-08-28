#include "pch.h"
#include "CollisionMgr.h"


CollisionMgr::CollisionMgr()
{

}

CollisionMgr::~CollisionMgr()
{

}

bool CollisionMgr::IsCollision(MyUnit* src, vector<MyUnit*>* _vecUnit)
{
	if (src == nullptr) return false;
	for (int i = 0; i < _vecUnit->size(); ++i)
	{
		if (_vecUnit->at(i) == nullptr) continue;
		// HACK
		_vecUnit->at(i)->colRc = Gdiplus::Rect(_vecUnit->at(i)->curPosX - _vecUnit->at(i)->rc.Width / 4
			, _vecUnit->at(i)->curPosY - _vecUnit->at(i)->rc.Height / 4
			, _vecUnit->at(i)->rc.Width / 2, _vecUnit->at(i)->rc.Height / 2);
		if (src == _vecUnit->at(i))
		{
			src->colRc = _vecUnit->at(i)->colRc;
			continue;
		}
		//
		if (_vecUnit->at(i)->colRc.Intersect(src->colRc)
			&& !_vecUnit->at(i)->Isdead)
		{
			float distanceX = _vecUnit->at(i)->curPosX - src->curPosX;
			float distanceY = _vecUnit->at(i)->curPosY - src->curPosY;

			float xvec = distanceX == 0 ? 0 : distanceX / abs(distanceX);
			float yvec = distanceY == 0 ? 0 : distanceY / abs(distanceY);

			CalcDirection(xvec,yvec);
			
			return true;
		}
	}
	return false;
}

void CollisionMgr::Render(vector<MyUnit*> _vecUnit, Gdiplus::Graphics* MemG)
{
	//충돌박스 그리기
	Pen pen(Color(255, 255, 255), 3);

	for (int i = 0; i < _vecUnit.size(); ++i)
	{
		 _vecUnit[i]->colRc = Gdiplus::Rect(_vecUnit[i]->curPosX - _vecUnit[i]->rc.Width / 4, _vecUnit[i]->curPosY - _vecUnit[i]->rc.Height / 4, _vecUnit[i]->rc.Width / 2, _vecUnit[i]->rc.Height / 2);
		MemG->DrawRectangle(&pen, _vecUnit[i]->colRc);
	}
}

void CollisionMgr::CalcDirection(int xvec, int yvec)
{
	if (xvec == 0 && yvec > 0)
	{
		direction = eColDirection_Bottom;
	}
	if (xvec == 0 && yvec < 0)
	{
		direction = eColDirection_Top;
	}
	if (xvec > 0 && yvec > 0)
	{
		direction = eColDirection_RightBottom;
	}
	if (xvec > 0 && yvec == 0)
	{
		direction = eColDirection_Right;
	}
	if (xvec > 0 && yvec < 0)
	{
		direction = eColDirection_RightTop;
	}
	if (xvec < 0 && yvec > 0)
	{
		direction = eColDirection_LeftBottom;
	}
	if (xvec < 0 && yvec == 0)
	{
		direction = eColDirection_Left;
	}
	if (xvec < 0 && yvec < 0)
	{
		direction = eColDirection_LeftTop;
	}
}