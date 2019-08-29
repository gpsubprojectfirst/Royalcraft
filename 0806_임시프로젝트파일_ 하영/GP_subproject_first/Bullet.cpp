#include "pch.h"
#include "bullet.h"

Bullet::Bullet()
	:xVec(0.0)
	, yVec(0.0)
	, isArrive(false)
{

}

Bullet::Bullet(MyUnit* dst)
	: isArrive(false)
{
	Init();
	ID = dst->ID;
	name = dst->name;
	mUnitInfo.move_speed = dst->mUnitInfo.move_speed;
	moveRc[0] = dst->moveRc[0];
	ParentImg = dst->ParentImg;

}

void Bullet::Init()
{
	Objtype = eObject_Bullet;
	isArrive = false;
	CalcVec();
}
void Bullet::Update(float Delta)
{
	if (target == nullptr)
	{
		isArrive = true;
		return;
	}

	AddDelta += Delta;
	if (AddDelta > 0.01f)
	{
		frame++;
		AddDelta = 0;

		if (frame > 10)
			frame = 0;
	}
	//CalcVec();
	curPosX += 3.0f * xVec;
	curPosY += 3.0f * yVec;

	rc = moveRc[0][0];
	
	if(target->posRc.Contains((int)curPosX, (int)curPosY) || target->Isdead)
	{
		isArrive = true;
	}
	else
	{
		//CalcVec();
	}
}
void Bullet::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;
	Gdiplus::Rect Dst1(int(curPosX - width / 2), int(curPosY - height / 2), width, height);
	
	Gdiplus::Bitmap tempBmp(width, height);
	Gdiplus::Graphics tempG(&tempBmp);
	Gdiplus::Rect tempRc(0, 0, width, height);

	tempG.DrawImage(ParentImg, tempRc, rc.X, rc.Y, width, height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	if (ID == eBullet_Arrow)
		tempBmp.RotateFlip(Rotate270FlipNone);

	MemG->DrawImage(&tempBmp, Dst1, 0, 0, width, height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
	
}
void Bullet::Release()
{
	delete this;
}

void Bullet::CalcVec()
{
	if (target == nullptr) return;

	float distanceX = target->curPosX - curPosX;
	float distanceY = target->curPosY - curPosY;

	float length = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
	xVec = (float)(length == 0.0 ? 0.0 : distanceX / length);
	yVec = (float)(length == 0.0 ? 0.0 : distanceY / length);
}


void Bullet::SetTarget(float srcx, float srcy, MyUnit* Intarget)
{
	curPosX = srcx;
	curPosY = srcy;

	target = Intarget;
}