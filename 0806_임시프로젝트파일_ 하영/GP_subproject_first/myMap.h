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
	void Init();
	GridInfo Infos[101][163];
};