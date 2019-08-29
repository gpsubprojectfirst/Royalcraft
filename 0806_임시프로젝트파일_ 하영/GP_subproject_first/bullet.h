#pragma once
#include "myUnit.h"

class Bullet
	: public MyUnit
{
public:
	Bullet();
	Bullet(MyUnit* dst);
	virtual void Init();
	virtual void Update(float Delta) override;
	virtual void Render(Gdiplus::Graphics* NenG) override;
	virtual void Release();
	void SetTarget(float srcx, float srcy,MyUnit* Intarget);
	void CalcVec();
	bool isArrive;
	float xVec;
	float yVec;
};