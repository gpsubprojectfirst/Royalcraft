#include "pch.h"
#include "bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(MyUnit* dst, float fx, float fy)
{
	Init();
	ID = dst->ID;
	name = dst->name;
	mUnitInfo.move_speed = dst->mUnitInfo.move_speed;
	moveRc[0] = dst->moveRc[0];
	ParentImg = dst->ParentImg;
	curPosX = fx;
	curPosY = fy;
}

void Bullet::Init()
{
	Objtype = eObject_Bullet;
	curTile = std::make_pair(0, 0);
	dstTile = std::make_pair(0, 0);
	Isarrive = false;
}
void Bullet::Update(float Delta)
{
	if (target == nullptr)
	{
		Isarrive = true;
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
	float distanceX = target->curPosX - curPosX;
	float distanceY = target->curPosY - curPosY;

	//TODO
	float xvec = distanceX == 0 ? 0 : distanceX / abs(distanceX);
	float yvec = distanceY == 0 ? 0 : distanceY / abs(distanceY);

	
	curPosX += 3 * xvec;
	curPosY += 3 * yvec;

	//int frame_ = frame % moveRc->size();
	rc = moveRc[0][0];
	
	if(target->posRc.Contains((float)curPosX, (float)curPosY) || target->Isdead)
	{
		Isarrive = true;
	}
}
void Bullet::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;
	Gdiplus::Rect Dst1(curPosX - width / 2, curPosY - height / 2, width, height);
	Gdiplus::Bitmap* tempBmp = new Bitmap(width, height);
	Gdiplus::Graphics* tempG = new Gdiplus::Graphics(tempBmp);
	Gdiplus::Rect tempRc(0, 0, width, height);
	tempG->DrawImage(ParentImg, tempRc, rc.X, rc.Y, width, height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	if (ID == eBullet_Arrow)
		tempBmp->RotateFlip(Rotate270FlipNone);

	//Gdiplus::Rect Dst1(posRc.X, posRc.Y, width /2, height / 2);
	MemG->DrawImage(tempBmp, Dst1, 0, 0, width, height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
	
	delete tempBmp;
	delete tempG;
}
void Bullet::Release()
{
	delete this;
}

//void Bullet::CopyObj(MyUnit* dst, float fx, float fy)
//{
//	ID = dst->ID;
//	name = dst->name;
//	mUnitInfo.move_speed = dst->mUnitInfo.move_speed;
//	moveRc[0] = dst->moveRc[0];
//	ParentImg = dst->ParentImg;
//	curPosX = fx;                         
//	curPosY = fy;
//}
void Bullet::SetTarget(float srcx, float srcy, MyUnit* Intarget)
{
	curPosX = srcx;
	curPosY = srcy;

	target = Intarget;
}