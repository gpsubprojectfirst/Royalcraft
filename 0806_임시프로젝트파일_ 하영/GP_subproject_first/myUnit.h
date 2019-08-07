#pragma once
#include "Object.h"

class myUnit : public Object
{
public:
	myUnit();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);

	virtual void Move(float Delta);
	virtual void Attack(float Delta);
	virtual void ExtraAction(float Delta);

	//À¯´Ö ½ºÅÈ
	float damage;
	float hp;
	EAtkType atk_type;
	float atk_speed;
	float move_speed;
	int cost;
	float AddDelta;

	std::vector<Gdiplus::Rect> moveRc; // ÀÌµ¿
	std::vector<Gdiplus::Rect> atkRc; // °ø°Ý
};