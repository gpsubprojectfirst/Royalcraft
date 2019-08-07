#include "pch.h"
#include "myUnit.h"

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
	if (AddDelta > 0.2f)
	{
		frame++;
		AddDelta = 0;
		if (frame > 10)
			frame = 0;
	}
	sm.Update();
	if (sm.GetCurState() == eState_Idle)
	{
		rc = moveRc[0];
	}
	else if (sm.GetCurState() == eState_Move)
	{
		rc = moveRc[frame];
		Move(Delta);
	}
	else if (sm.GetCurState() == eState_Attack)
	{
		rc = atkRc[frame];
		Attack(Delta);
	}
}

void myUnit::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;

	Gdiplus::Rect Dst1(0, 0, width, height);
	MemG->DrawImage(ParentImg, Dst1, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
}
void myUnit::Move(float Delta)
{
	//길찾기 알고리즘, delta
	//this->curPos.first += this->move_speed * Delta;

}

void myUnit::Attack(float Delta)
{

}

void myUnit::ExtraAction(float Delta)
{

}
