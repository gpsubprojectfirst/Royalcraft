#include "pch.h"
#include "myMap.h"

myMap::myMap()
{
	
}
void myMap::Init()
{
	//testmap ±¸¼º
	int k = 0, l = 0;
	for (int i = 0; i < 1010; i += 10)
	{
		for (int j = 0; j < 1630; j += 10)
		{
			Infos[k][l].rc = Rect(i, j, 10, 10);
			Infos[k][l].flags = 0;
			++l;
		}
		++k;
		l = 0;
	}
}
