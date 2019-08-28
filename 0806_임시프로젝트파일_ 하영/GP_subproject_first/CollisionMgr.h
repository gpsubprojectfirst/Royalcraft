#pragma once
#include "SingleTon.h"
class CollisionMgr :
	public SingleTon<CollisionMgr>
{
public:
	void Collision(vector<MyUnit*> _pTemp);
	void Render(vector<MyUnit*> _vecUnit, Gdiplus::Graphics* MemG);

public:
	CollisionMgr();
	~CollisionMgr();
};

