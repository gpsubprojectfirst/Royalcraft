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
	
	//���� ����
	float damage;
	float hp;
	EAtkType atk_type;
	float atk_speed;
	float move_speed;
	int cost;
	float AddDelta;

	//Tile Position
	std::pair<int,int> curTile; //���� Ÿ���� ��ǥ
	std::pair<int,int> dstTile; //���� Ÿ���� ��ǥ
	std::vector<std::pair<int,int>*> moveTilePath;

	//Asset Position
	std::vector<Gdiplus::Rect> moveRc; // �̵��� ���� �̹��� ��ġ
	std::vector<Gdiplus::Rect> atkRc; // ���ݿ� ���� �̹��� ��ġ
};