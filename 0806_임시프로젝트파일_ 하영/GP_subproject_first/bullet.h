#pragma once
#include "myUnit.h"

class Bullet
	: public MyUnit
{
public:
	Bullet();
	Bullet(MyUnit* dst, float fx, float fy);
	virtual void Init();
	virtual void Update(float Delta) override;
	virtual void Render(Gdiplus::Graphics* NenG) override;
	virtual void Release();
	//virtual void CopyObj(MyUnit* dst, float fx, float fy) override;
	void SetTarget(float srcx, float srcy,MyUnit* Intarget);

	bool Isarrive;
};