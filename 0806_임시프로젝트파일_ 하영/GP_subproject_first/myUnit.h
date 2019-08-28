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
	MyUnit(MyUnit* _dst, float fx, float fy);
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Set(SearchTree* mTree);
	virtual void CopyObj( MyUnit* dst, float fx, float fy );
	
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
	bool teamBlue; //true = blud, false = red
	
	//utill
	float AddDelta;
	BehaviorTree* UnitBt;
	MyUnit* target; //목적 오브젝트
	Bullet* arrow;
	//Tile Position
	std::pair<int,int> curTile; //현재 타일의 좌표
	std::pair<int,int> dstTile; //목적 타일의 좌표
	std::stack<std::pair<int,int>> moveTilePath;

	//Asset Position
	EDirectionType direction; // 0 -하, 1-좌하단, 2- 좌, 3- 우상단, 4-상
	bool flipF; //true면 이미지 대칭 flip
	std::vector<Gdiplus::Rect> moveRc[eDirection_Cnt]; // 이동에 쓰일 이미지 위치
	std::vector<Gdiplus::Rect> atkRc[eDirection_Cnt]; // 공격에 쓰일 이미지 위치
};