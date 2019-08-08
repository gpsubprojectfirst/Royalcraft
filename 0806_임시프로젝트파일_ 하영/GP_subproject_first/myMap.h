#pragma once
#include "pch.h"
class GridInfo
{
public:
	Gdiplus::Rect rc;
	int flags;
};
class myMap
{
public:
	myMap();
	void set(CPoint pt,Object* obj);
	GridInfo Infos[19][33];
};