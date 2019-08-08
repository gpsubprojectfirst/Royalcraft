#include "pch.h"
#include "myMap.h"


myMap::myMap()
{
	
}
void myMap::Init()
{
	
	int k = 0, l = 0;
	for (int i = 0; i <= REAL_WINSIZE_X; i += size)
	{
		for (int j = 0; j <= REAL_WINSIZE_Y; j += size)
		{
			Infos[k][l].rc = Rect(i, j, size, size);
			Infos[k][l].flags = 0;
			++l;
		}
		++k;
		l = 0;
	}
}

void myMap::set(CPoint pt, Object* obj)
{
	Point mPoint;
	mPoint.X = pt.x;
	mPoint.Y = pt.y;

	for (int i = 0; i < REAL_WINSIZE_X/size; ++i)
	{
		for (int j = 0; j < REAL_WINSIZE_Y/size; ++j)
		{
			if (Infos[i][j].rc.Contains(mPoint) && Infos[i][j].flags == 0)
			{
				Infos[i][j].flags = 1;
				obj->posRc = Infos[i][j].rc;
				cout << "move" << i << ", " << j << endl;
				break;
			}
		}
	}
}

