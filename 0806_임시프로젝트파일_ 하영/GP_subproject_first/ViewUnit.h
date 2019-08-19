#pragma once
#include "Object.h"
class ViewUnit : public Object
{

public:
	int direction; // 0 -하, 1-좌하단, 2- 좌, 3- 우상단, 4-상
	std::vector<Gdiplus::Rect> moveRc[5]; // 이동에 쓰일 이미지 위치

public:
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void CopyObj(MyUnit* dst, int ix, int iy);

public:
	ViewUnit();
	~ViewUnit();
};

