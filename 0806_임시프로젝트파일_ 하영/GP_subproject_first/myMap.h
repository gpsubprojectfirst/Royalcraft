#pragma once
#include "pch.h"
//#include "Object.h"
class Object;
class GridInfo
{
public:
	Gdiplus::Rect rc;
	int flags;

};
class myMap
{
	int size;
public:
	myMap();
	void Init();
	void set(CPoint pt,Object* obj);
	GridInfo Infos[65][97];
};