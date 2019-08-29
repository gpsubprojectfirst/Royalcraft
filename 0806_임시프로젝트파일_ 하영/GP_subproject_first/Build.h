#pragma once
#include "myUnit.h"

class Build :public MyUnit
{
public:
	int pivotVal;
	int adjustedVal;

public:
	Build();
	virtual void Init();
	virtual void Update(float Delta) override;
	virtual void Render(Gdiplus::Graphics* MemG) override;

	virtual void CopyObj(MyUnit* dst, float fx, float fy) override;
	virtual void CreateBT(BlackBoard* InBB) override;

	virtual void Rest(float Delta) override;

	void CalcDirection(float xvec, float yvec) override;
	std::vector<Gdiplus::Rect> restRc;
};