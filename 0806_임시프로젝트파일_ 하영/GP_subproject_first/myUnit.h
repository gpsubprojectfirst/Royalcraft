#pragma once
#include "Object.h"
#include "MyMap.h"
#include "BehaviorTree.h"
#include "stack"
struct UnitInfo
{
	int damage;
	int hp;
	EAtkType atk_type;
	float atk_speed;
	float move_speed;
	int cost;
	int atk_distance;
};
class MyUnit : public Object
{
public:
	MyUnit();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	virtual void Set(SearchTree* mTree);
	virtual void ParserXML();
	virtual void CopyObj( MyUnit* dst, int ix, int iy );
	
	virtual void Move(float Delta);
	virtual void Attack(float Delta);
	virtual void Rest(float Delta) {}
	virtual void ExtraAction(float Delta);
	virtual void CreateBT(BlackBoard* InBB);

	void CalcDirection(int xvec,int yvec);
	//unit status
	UnitInfo mUnitInfo;
	
	//game flag
	bool Isdead;
	bool teamBlue; //true = blud, false = red
	
	//utill
	float AddDelta;
	BehaviorTree* UnitBt;
	MyUnit* target; //목적 오브젝트

	//Tile Position
	std::pair<int,int> curTile; //현재 타일의 좌표
	std::pair<int,int> dstTile; //목적 타일의 좌표
	std::stack<std::pair<int,int>> moveTilePath;

	//Asset Position
	int direction; // 0 -하, 1-좌하단, 2- 좌, 3- 우상단, 4-상
	bool flipF; //true면 이미지 대칭 flip
	std::vector<Gdiplus::Rect> moveRc[5]; // 이동에 쓰일 이미지 위치
	std::vector<Gdiplus::Rect> atkRc[5]; // 공격에 쓰일 이미지 위치
};