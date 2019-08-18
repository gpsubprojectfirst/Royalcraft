#pragma once
#include "myUnit.h"

class Build :public MyUnit
{
public:
	Build();
	virtual void Update(float Delta) override;
	virtual void Render(Gdiplus::Graphics* MemG) override;
	virtual void CopyObj(MyUnit* dst, int ix, int iy) override;
	virtual void CreateBT(BlackBoard* InBB) override;
};