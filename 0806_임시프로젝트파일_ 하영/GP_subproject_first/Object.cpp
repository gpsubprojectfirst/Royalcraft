#include "pch.h"

#include "Object.h"

Object::Object()
	: Objtype(eObject_None)
	, Enable(true)
	, ID(0)
	, ParentImg(nullptr)
	,posRc(0,0,0,0)
	, curPos{ 0, 0 }
	,frame(0)
{
};
Object::Object(EObject InType)
	:Objtype(InType)
	, Enable(true)
	, ID(0)
	, ParentImg(nullptr)
	, posRc(0, 0, 0, 0)
	, curPos{ 0, 0 }
	,frame(0)
{

}
Object::~Object()
{

}

myUnit::myUnit()
	: Object(EObject::eObject_Unit)
	, AddDelta(0.f)
{
	sm.Add(new State_Idle);
	sm.Add(new State_Move);
	sm.Add(new State_Attack);
}
void myUnit::Update(float Delta)
{
	AddDelta += Delta;
	if (AddDelta > 0.5f)
	{
		frame++;
		AddDelta = 0;
		if (frame > 10)
			frame = 0;
	}
}

void myUnit::Move(float Delta)
{
	//길찾기 알고리즘, delta
	//this->curPos.first += this->move_speed * Delta;

}

void myUnit::Attack()
{

}

void myUnit::ExtraAction()
{

}

