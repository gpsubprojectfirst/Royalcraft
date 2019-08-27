#include "pch.h"

Build::Build()
{
	Init();
}
void Build::Init()
{
	Objtype = eObject_Build;
	curTile = std::make_pair(0, 0);

	Isdead = false;

	sm.Add(new State_Idle);
	sm.Add(new State_Attack);
}
void Build::Update(float Delta)
{
	if (!Isdead)
	{
		AddDelta += Delta;
		if (AddDelta > 0.1f)
		{
			frame++;
			AddDelta = 0;

			if (frame > 10)
				frame = 0;
		}
		UnitBt->Tick();
		if (sm.GetCurState() == eState_Idle)
		{
			adjustedVal = rc.Height - pivotVal;
			int frame_ = frame % restRc.size();
			rc = restRc[frame_];
		}
		else if (sm.GetCurState() == eState_Attack)
		{
			int frame_ = frame % atkRc[direction].size();
			rc = atkRc[direction][frame_];
		}
		else if (sm.GetCurState() == eState_Dead)
		{
			//rc = atkRc[0];
		}
	}
	if (mUnitInfo.atk_type == 1 && arrow != nullptr)
	{
		arrow->Update(Delta);
	}
}
void Build::Render(Gdiplus::Graphics* MemG)
{
	if (!Isdead)
	{
		int width = rc.Width;
		int height = rc.Height;

		Gdiplus::Rect Dst1(curPosX - width / 4, curPosY - height / 4 - adjustedVal/4 , width /2, height/2);
		MemG->DrawImage(ParentImg, Dst1, rc.X, rc.Y, width,height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
	if (mUnitInfo.atk_type == 1 && arrow != nullptr)
	{
		if (arrow->Isarrive == true)
		{
			arrow->Release();
			arrow = nullptr;
		}
		else
			arrow->Render(MemG);
	}
}

void Build::CopyObj(MyUnit* dst, int ix, int iy)
{
	ID = dst->ID;
	name = dst->name;
	mUnitInfo = dst->mUnitInfo;
	for (int i = 0; i < 5; i++)
	{
		atkRc[i] = dst->atkRc[i];
	}

	restRc = ((Build*)dst)->restRc;
	curPosX = ix;
	curPosY = iy;
}

void Build::CreateBT(BlackBoard* InBB)
{
	UnitBt = new BehaviorTree(this, InBB);
	UnitBt->InitTower(this, InBB);
}

void Build::Rest(float Delta)
{

}

void Build::CalcDirection(int xvec, int yvec)
{
	if (teamBlue)
	{
		if (xvec > 0 && yvec != 0)
		{
			direction = eDirection_RightTop;//3
		}
		if (xvec == 0)
		{
			direction = eDirection_Right;//2
		}
		if (xvec < 0 && yvec != 0)
		{
			direction = eDirection_RightBottom;//1
		}
		if (xvec > 0 && yvec == 0)
		{
			direction = eDirection_Bottom;//0
		}
		if (xvec < 0 && yvec == 0)
		{
			direction = eDirection_Top;//4
		}
	}
	if (!teamBlue)
	{
		if (xvec > 0 && yvec != 0)
		{
			direction = eDirection_RightBottom;//1
		}
		if (xvec == 0)
		{
			direction = eDirection_Right;//2
		}
		if (xvec < 0 && yvec != 0)
		{
			direction = eDirection_RightTop;//3
		}
		if (xvec > 0 && yvec == 0)
		{
			direction = eDirection_Bottom;//0
		}
		if (xvec < 0 && yvec == 0)
		{
			direction = eDirection_Top;//4
		}
	}
}