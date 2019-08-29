#include "pch.h"
#include "MyUnit.h"
#include "SoundMgr.h"

MyUnit::MyUnit()
	: Object(EObject::eObject_Unit)
	, AddDelta(0.f)
{
	curTile = std::make_pair(0, 0);
	dstTile = std::make_pair(0, 0);

	mUnitInfo.hp = INIT_HP;
	mUnitInfo.move_speed = INIT_SPEED;
	mUnitInfo.atk_distance = INIT_ATK_DIST;
	mUnitInfo.damage = INIT_DAMAGE;
	
	Isdead = false;

	sm.Add(new State_Idle);
	sm.Add(new State_Move);
	sm.Add(new State_Attack);
	sm.Add(new State_Dead);
}
MyUnit::MyUnit(MyUnit* _dst, float fx, float fy)
{
	ID = _dst->ID;
	name = _dst->name;
	mUnitInfo = _dst->mUnitInfo;
	for (int i = 0; i < eDirection_Cnt; i++)
	{
		moveRc[i] = _dst->moveRc[i];
	}
	for (int i = 0; i < eDirection_Cnt; i++)
	{
		atkRc[i] = _dst->atkRc[i];
	}

	curPosX = fx;
	curPosY = fy;
}
void MyUnit::Update(float Delta)
{
	if (!Isdead)
	{
		
		AddDelta += Delta;
		
		if (AddDelta > UNIT_FRAME_INC_DELTA)
		{
			frame++;
			AddDelta = 0;

			if (frame > MAX_FRAME)
				frame = 0;
		}
		//상태 변화, 추후 행동 트리에 추가
		UnitBt->Tick();

		if (sm.GetCurState() == eState_Idle)
		{
			rc = moveRc[direction][0];
		}
		else if (sm.GetCurState() == eState_Move)
		{
			int frame_ = frame % moveRc[direction].size();
			rc = moveRc[direction][frame_];
			//Move(Delta);
		}
		else if (sm.GetCurState() == eState_Attack)
		{
			int frame_ = frame % atkRc[direction].size();
			rc = atkRc[direction][frame_];
			//Attack(Delta);
		}
		else if (sm.GetCurState() == eState_Dead)
		{
			rc = moveRc[eDirection_Bottom][0];
		}
	}
	if (mUnitInfo.atk_type == 1 && arrow != nullptr)
	{
		arrow->Update(Delta);
	}
}

void MyUnit::Render(Gdiplus::Graphics* MemG)
{
	if (!Isdead)
	{
		int width = rc.Width;
		int height = rc.Height;
		
		Gdiplus::Rect Dst1(curPosX - width/4, curPosY - height/4, width / 2, height / 2);
	
		Gdiplus::Bitmap tempBmp(width, height);
		Gdiplus::Graphics tempG(&tempBmp);
		Gdiplus::Rect tempRc(0, 0, width, height);
		tempG.DrawImage(ParentImg,tempRc,rc.X,rc.Y,width,height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
		
		if(flipF)
			tempBmp.RotateFlip(RotateNoneFlipX);

		MemG->DrawImage(&tempBmp, Dst1, 0, 0, width, height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);

	}
	if (mUnitInfo.atk_type == 1 && arrow != nullptr)
	{
		if (arrow->IsArrive == true)
		{
			arrow->Release();
			arrow = nullptr;
		}
		else
			arrow->Render(MemG);
	}
}
void MyUnit::CopyObj(MyUnit* dst, float fx, float fy)
{
 	ID = dst->ID;
	name = dst->name;
	mUnitInfo = dst->mUnitInfo;
	for (int i = 0; i < eDirection_Cnt; i++)
	{
		moveRc[i] = dst->moveRc[i];
	}
	for (int i = 0; i < eDirection_Cnt; i++)
	{
		atkRc[i] = dst->atkRc[i];
	}
	
	curPosX = fx;
	curPosY = fy;
}


void MyUnit::Set(SearchTree* mTree)
{
	while (!moveTilePath.empty())
		moveTilePath.pop();
	mTree->FindPath(curTile, dstTile, &moveTilePath);
	mTree->Set(mMap);
	
}

void MyUnit::Move(float Delta)
{
	if (moveTilePath.empty())
	{
		return;
	}

	//moveTilePath큐에 이동경로가 저장되어있음
	if (curTile == moveTilePath.top())
	{
		moveTilePath.pop();
	}
	else
	{
		//시작 좌표의 타일 렉트 가져오기
		Gdiplus::Rect strTile = mMap->Infos[curTile.first][curTile.second].rc;
		
		//다음 목적지 좌표의 타일 렉트 가져오기
		int dstX = moveTilePath.top().first;
		int dstY = moveTilePath.top().second;
		Gdiplus::Rect tempDstTile = mMap->Infos[dstX][dstY].rc;
		
		//거리 계산
		//this->curPos.first += this->move_speed * Delta;
		/*
		int distanceX = tempDstTile.X - strTile.X;
		int distanceY = tempDstTile.Y - strTile.Y;
		*/
		float distanceX = tempDstTile.X + (TILESIZEX / 2) - this->curPosX;
		float distanceY = tempDstTile.Y + (TILESIZEY / 2) - this->curPosY;

		float length = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
		
		float xvec = (float)(length == 0.0 ? 0.0 : distanceX / length);
		float yvec = (float)(length == 0.0 ? 0.0 : distanceY / length);
		
		CalcDirection(xvec, yvec);
		
		 //위치 이동
		
		curPosX += xvec * mUnitInfo.move_speed * 0.5f;
		curPosY += yvec * mUnitInfo.move_speed * 0.5f;

		//std::cout << curPosX << " , " << curPosY << std::endl;
		//현재 목적지에 캐릭터가 도착했는지
		//if(sqrt(pow(tempDstTile.X + 13 - curPosX,2)+ pow(tempDstTile.Y + 11 - curPosY,2))<10)
		if (pow(tempDstTile.X + (TILESIZEX / 2) - curPosX,2) +
			pow(tempDstTile.Y + (TILESIZEY / 2) - curPosY,2) < 2)
		{
			curTile = moveTilePath.top();

			posRc.X = tempDstTile.X;
			posRc.Y = tempDstTile.Y;

			curPosX = posRc.X + TILESIZEX/2;
			curPosY = posRc.Y + TILESIZEY/2;
		}
	}
}

void MyUnit::Attack(float Delta)
{
	if (target == nullptr)
	{
		return;
	}
	//타입이 nonmelee라면 atk_type = 1
	if (target->mUnitInfo.hp > 0)
	{
		float distanceX = target->curPosX - this->curPosX;
		float distanceY = target->curPosY - this->curPosY;

		float xvec = distanceX == 0 ? 0 : distanceX / abs(distanceX);
		float yvec = distanceY == 0 ? 0 : distanceY / abs(distanceY);
		
		CalcDirection(xvec, yvec);

		target->mUnitInfo.hp -= this->mUnitInfo.damage;
	}
	else
	{
		target->Isdead = true;
		target = nullptr;
		if (this->mUnitInfo.atk_type == 1 && arrow != nullptr)
		{
			arrow->Release();
			arrow = nullptr;
		}
	}
	if (this->mUnitInfo.atk_type == 1 && arrow == nullptr)
	{
		arrow = new Bullet();
		EBullet_ID bulletID = eBullet_Fire;
		if (this->Objtype == eObject_Unit && this->ID == eUnit_Archer)
		{
			SoundMgr::GetInstance()->SoundPlay(2, 0);
			bulletID = eBullet_Arrow;
		}
		if (this->Objtype == eObject_Unit && this->ID == eUnit_Wizard)
		{
			SoundMgr::GetInstance()->SoundPlay(13, 0);
			bulletID = eBullet_Fire;
		}
		if (this->Objtype == eObject_Unit && this->ID == eUnit_Electric)
		{
			SoundMgr::GetInstance()->SoundPlay(12, 0);
			bulletID = eBullet_Fire;
		}
		if (this->Objtype == eObject_Unit && this->ID == eUnit_Musket)
		{
			SoundMgr::GetInstance()->SoundPlay(11, 0);
			bulletID = eBullet_Bullet;
		}
		if (this->Objtype == eObject_Build)
		{
			SoundMgr::GetInstance()->SoundPlay(10, 0);
			bulletID = eBullet_Bullet;
		}
		arrow->CopyObj((Bullet*)ObjectManager::GetInstance().GetBullet(bulletID), curPosX, curPosY);
		arrow->SetTarget(this->curPosX,this->curPosY,this->target);
		arrow->Init();
	}
}

void MyUnit::ExtraAction(float Delta)
{

}

void MyUnit::CreateBT(BlackBoard* InBB)
{
	UnitBt = new BehaviorTree(this,InBB);
	UnitBt->Init(this, InBB);
}

void MyUnit::CalcDirection(float xvec,float yvec)
{
	if (xvec == 0 && yvec > 0)
	{
		flipF = true;
		direction = eDirection_Bottom;
	}
	if (xvec == 0 && yvec < 0)
	{
		flipF = false;
		direction = eDirection_Top;
	}
	if (xvec > 0 && yvec > 0)
	{
		flipF = false;
		direction = eDirection_RightBottom;
	}
	if (xvec > 0 && yvec == 0)
	{
		flipF = false;
		direction = eDirection_Right;
	}
	if (xvec > 0 && yvec < 0)
	{
		flipF = false;
		direction = eDirection_RightTop;
	}
	if (xvec < 0 && yvec > 0)
	{
		flipF = true;
		direction = eDirection_RightBottom;
	}
	if (xvec < 0 && yvec == 0)
	{
		flipF = true;
		direction = eDirection_Right;
	}
	if (xvec < 0 && yvec < 0)
	{
		flipF = true;
		direction = eDirection_RightTop;
	}
}