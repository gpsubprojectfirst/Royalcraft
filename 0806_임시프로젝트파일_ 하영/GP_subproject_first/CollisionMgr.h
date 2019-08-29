#pragma once
#include "SingleTon.h"
class CollisionMgr :
	public SingleTon<CollisionMgr>
{
public:
	EColDirectionType direction;
	bool IsCollision(MyUnit* src,vector<MyUnit*>* _pTemp);
	void Render(vector<MyUnit*> _vecUnit, Gdiplus::Graphics* MemG);
	void CalcDirection(float xvec,float yvec);
	void CalcColBox(vector<MyUnit*>* _vecUnit);
public:
	CollisionMgr();
	~CollisionMgr();
};

