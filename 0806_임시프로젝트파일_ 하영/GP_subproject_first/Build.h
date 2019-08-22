#pragma once
#include "myUnit.h"

class Build :public MyUnit
{
public:
	Build();
	virtual void Init();
	virtual void Update(float Delta) override;
	virtual void Render(Gdiplus::Graphics* MemG) override;
	virtual void ParserXML() override;
	virtual void CopyObj(MyUnit* dst, int ix, int iy) override;
	virtual void CreateBT(BlackBoard* InBB) override;

	virtual void Rest(float Delta) override;
	std::vector<Gdiplus::Rect> restRc;
};