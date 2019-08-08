#include "pch.h"
#include "myMap.h"

myMap::myMap()
{
	//testmap
	int k = 0, l = 0;
	for (int i = 0; i <= 1080; i += 60)
	{
		for (int j = 0; j <= 1920; j += 60)
		{
			Infos[k][l].rc =Rect(i, j, 60, 60);
			Infos[k][l].flags = 0;
			++l;
		}
		++k;
		l = 0;
	}
}
void myMap::set(CPoint pt,Object* obj)
{
	Point mPoint;
	mPoint.X = pt.x;
	mPoint.Y = pt.y;

	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < 33; ++j)
		{
			if (Infos[i][j].rc.Contains(mPoint) && Infos[i][j].flags == 0)
			{
				Infos[i][j].flags = 1;
				obj->posRc = Infos[i][j].rc;
				cout <<"move"<< i << ", " << j << endl;
				break;
			}
		}
	}
}