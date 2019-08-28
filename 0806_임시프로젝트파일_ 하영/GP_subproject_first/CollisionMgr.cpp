#include "pch.h"
#include "CollisionMgr.h"


CollisionMgr::CollisionMgr()
{

}

CollisionMgr::~CollisionMgr()
{

}

void CollisionMgr::Collision(vector<MyUnit*> _vecUnit)
{
	for (unsigned int i = 0; i < _vecUnit.size(); ++i)
	{
		for (unsigned int j = i; j < _vecUnit.size(); ++j)
		{
			if (i == j)
				continue;

			if (_vecUnit[i]->Objtype == eObject_Unit && _vecUnit[i]->teamBlue == true)
			{
				_vecUnit[i]->tempRc = Gdiplus::Rect(_vecUnit[i]->curPosX - _vecUnit[i]->rc.Width / 4, _vecUnit[i]->curPosY - _vecUnit[i]->rc.Height / 4, _vecUnit[i]->rc.Width / 2, _vecUnit[i]->rc.Height / 2);
				_vecUnit[j]->tempRc = Gdiplus::Rect(_vecUnit[j]->curPosX - _vecUnit[j]->rc.Width / 4, _vecUnit[j]->curPosY - _vecUnit[j]->rc.Height / 4, _vecUnit[j]->rc.Width / 2, _vecUnit[j]->rc.Height / 2);

				if (_vecUnit[i]->tempRc.Intersect(_vecUnit[j]->tempRc))
				{
					std::cout << "col" << std::endl;

				}
			}


		}
	}
}

void CollisionMgr::Render(vector<MyUnit*> _vecUnit, Gdiplus::Graphics* MemG)
{
	//충돌박스 그리기
	Pen pen(Color(255, 255, 255), 3);

	for (unsigned int i = 0; i < _vecUnit.size(); ++i)
	{
		for (unsigned int j = i; j < _vecUnit.size(); ++j)
		{
			if (i == j)
				continue;

			if (_vecUnit[i]->Objtype == eObject_Unit && _vecUnit[i]->teamBlue == true)
			{
				 _vecUnit[i]->tempRc = Gdiplus::Rect(_vecUnit[i]->curPosX - _vecUnit[i]->rc.Width / 4, _vecUnit[i]->curPosY - _vecUnit[i]->rc.Height / 4, _vecUnit[i]->rc.Width / 2, _vecUnit[i]->rc.Height / 2);
				_vecUnit[j]->tempRc = Gdiplus::Rect(_vecUnit[j]->curPosX - _vecUnit[j]->rc.Width / 4, _vecUnit[j]->curPosY - _vecUnit[j]->rc.Height / 4, _vecUnit[j]->rc.Width / 2, _vecUnit[j]->rc.Height / 2);

				MemG->DrawRectangle(&pen, _vecUnit[i]->tempRc);
				MemG->DrawRectangle(&pen, _vecUnit[j]->tempRc);


			}

		}
	}
}