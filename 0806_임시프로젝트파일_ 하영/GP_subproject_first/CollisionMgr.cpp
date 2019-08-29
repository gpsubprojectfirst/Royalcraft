#include "pch.h"
#include "CollisionMgr.h"


CollisionMgr::CollisionMgr()
	:direction(eColDirection_Bottom)
{

}

CollisionMgr::~CollisionMgr()
{

}

Gdiplus::Rect temprc;

static BOOL Intersect(OUT Gdiplus::Rect& c,
	IN const Gdiplus::Rect& a,
	IN const Gdiplus::Rect& b)
{

	INT right = min(a.GetRight(), b.GetRight());
	INT bottom = min(a.GetBottom(), b.GetBottom());
	INT left = max(a.GetLeft(), b.GetLeft());
	INT top = max(a.GetTop(), b.GetTop());

	c.X = left;
	c.Y = top;
	c.Width = right - left;
	c.Height = bottom - top;
	return !c.IsEmptyArea();
}
bool CollisionMgr::IsCollision(MyUnit* src, vector<MyUnit*>* _vecUnit)
{
	CalcColBox(_vecUnit);
	src->colRc = Gdiplus::Rect(int(src->curPosX - (src->rc.Width / 8))
		, int(src->curPosY - (src->rc.Height / 8))
		, (int)(src->rc.Width * 0.25), (int)(src->rc.Height * 0.25));

	if (src == nullptr) return false;
	
	for (unsigned int i = 0; i < _vecUnit->size(); ++i)
	{
		if (_vecUnit->at(i) == nullptr) continue;
		if (src == _vecUnit->at(i)) continue;
		
		if (Intersect(temprc, src->colRc,_vecUnit->at(i)->colRc)
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
void CollisionMgr::CalcColBox(vector<MyUnit*>* _vecUnit)
{
	for (auto& it : *_vecUnit)
	{
		// HACK
		it->colRc = Gdiplus::Rect(int(it->curPosX - (it->rc.Width / 8))
			, int(it->curPosY - (it->rc.Height / 8))
			, (int) (it->rc.Width * 0.25), (int)(it->rc.Height * 0.25));

		//
	}
}
void CollisionMgr::Render(vector<MyUnit*> _vecUnit, Gdiplus::Graphics* MemG)
{
	Pen pen(Color(255, 255, 255), 3);

	for (unsigned int i = 0; i < _vecUnit.size(); ++i)
	{
		 _vecUnit[i]->colRc = Gdiplus::Rect(int(_vecUnit[i]->curPosX - _vecUnit[i]->rc.Width / 8)
			 , int(_vecUnit[i]->curPosY - _vecUnit[i]->rc.Height / 8)
			 , int(_vecUnit[i]->rc.Width / 4), int(_vecUnit[i]->rc.Height / 4));
		 if (!_vecUnit[i]->Isdead)
			MemG->DrawRectangle(&pen, _vecUnit[i]->colRc);
	}
}

void CollisionMgr::CalcDirection(float xvec, float yvec)
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