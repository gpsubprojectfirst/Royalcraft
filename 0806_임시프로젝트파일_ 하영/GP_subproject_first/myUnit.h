#pragma once
#include "Object.h"
#include "MyMap.h"
#include "BehaviorTree.h"
#include "stack"

class Bullet;
struct UnitInfo
{
	int damage;
	int hp;
	EAtkType atk_type;
	int atk_speed;
	float move_speed;
	int cost;
	int atk_distance;
};

class MyUnit : public Object
{
public:
	MyUnit();
	MyUnit(MyUnit* _dst);
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Set(SearchTree* mTree);

	virtual void Move(float Delta);
	virtual void Attack(float Delta);
	virtual void Rest(float Delta) {}
	virtual void ExtraAction(float Delta);
	virtual void CreateBT(BlackBoard* InBB);
	virtual void CalcDirection(int xvec,int yvec);

	//unit status
	UnitInfo mUnitInfo;
	
	//game flag
	bool Isdead;
	bool teamBlue; //true = blue, false = red
	
	//utill
	float AddDelta;
	BehaviorTree* UnitBt;
	MyUnit* target; //target object
	Bullet* arrow;
	//Tile Position
	std::pair<int,int> curTile; 
	std::pair<int,int> dstTile; 
	std::stack<std::pair<int,int>> moveTilePath;

	//Asset Position
	EDirectionType direction; // 0 -bottom, 1-Right bottom, 2- Rigth, 3- Rigth Top, 4- Top
	bool flipF;
	std::vector<Gdiplus::Rect> moveRc[eDirection_Cnt]; // move to img pos
	std::vector<Gdiplus::Rect> atkRc[eDirection_Cnt]; // attack  to img pos
};