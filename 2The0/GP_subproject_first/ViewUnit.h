#pragma once
#include "Object.h"
class ViewUnit : public Object
{

public:
	int direction; // 0 -��, 1-���ϴ�, 2- ��, 3- ����, 4-��
	std::vector<Gdiplus::Rect> moveRc[5]; // �̵��� ���� �̹��� ��ġ

public:
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void CopyObj(MyUnit* dst, int ix, int iy);

public:
	ViewUnit();
	~ViewUnit();
};

