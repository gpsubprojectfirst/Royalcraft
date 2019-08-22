#pragma once
#include "myUnit.h"

class Bullet
	: public MyUnit
{
public:
	Bullet();
	virtual void Init();
	virtual void Update(float Delta) override;
	virtual void Render(Gdiplus::Graphics* NenG) override;
	virtual void Release();
	virtual void ParserXML() override;
	virtual void CopyObj(MyUnit* dst, int ix, int iy) override;
	void SetTarget(float srcx, float srcy,MyUnit* Intarget);

	bool Isarrive;
};