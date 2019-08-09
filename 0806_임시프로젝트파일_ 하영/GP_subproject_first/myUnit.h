#pragma once
#include "Object.h"
#include "myMap.h"

class myUnit : public Object
{
public:
	myUnit();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);

	virtual void Set(CPoint pt,myMap* map);
	void SchPath(myMap* map);

	virtual void Move(float Delta);
	virtual void Attack(float Delta);
	virtual void ExtraAction(float Delta);
	
	//유닛 스탯
	float damage;
	float hp;
	EAtkType atk_type;
	float atk_speed;
	float move_speed;
	int cost;
	float AddDelta;

	//Tile Position
	std::pair<int,int> curTile; //현재 타일의 좌표
	std::pair<int,int> dstTile; //목적 타일의 좌표
	std::vector<std::pair<int,int>*> moveTilePath;

	//Asset Position
	std::vector<Gdiplus::Rect> moveRc; // 이동에 쓰일 이미지 위치
	std::vector<Gdiplus::Rect> atkRc; // 공격에 쓰일 이미지 위치
};