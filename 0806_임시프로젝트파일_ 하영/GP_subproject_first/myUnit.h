#pragma once
#include "Object.h"

class myUnit : public Object
{
public:
	myUnit();
	virtual void Update(float Delta);

	virtual void Move(float Delta);
	virtual void Attack();
	virtual void ExtraAction();

	//���� ����
	float damage;
	float hp;
	EAtkType atk_type;
	float atk_speed;
	float move_speed;
	int cost;
	float AddDelta;

	std::vector<Gdiplus::Rect> moveRc; // �̵�
	std::vector<Gdiplus::Rect> atkRc; // ����
};