#pragma once
#include "Object.h"
#include "MyMap.h"
#include "BehaviorTree.h"
#include "stack"
class MyUnit : public Object
{
public:
	MyUnit();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Set(CPoint pt,MyMap* map,SearchTree* mTree);
	virtual void ParserXML();
	virtual void CopyObj( MyUnit* dst);
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
	std::stack<std::pair<int,int>> moveTilePath;

	//Asset Position
	int direction; // 0 -하, 1-좌하단, 2- 좌, 3- 우상단, 4-상
	std::vector<Gdiplus::Rect> moveRc[5]; // 이동에 쓰일 이미지 위치
	std::vector<Gdiplus::Rect> atkRc; // 공격에 쓰일 이미지 위치

	//Behavior Tree
	BehaviorTree UnitBt;
};