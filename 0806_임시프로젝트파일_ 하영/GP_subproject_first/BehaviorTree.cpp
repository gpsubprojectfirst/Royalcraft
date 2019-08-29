#include "pch.h"
#include "BehaviorTree.h"
#include "myUnit.h"
#include "CollisionMgr.h"

BlackBoard::BlackBoard(Command& InCmQ, SearchTree* InTree, MyMap* InMap)
{
	cmQ = &InCmQ;
	mTree = InTree;
	mMap = InMap;
};
void BlackBoard::UpdateData(std::vector<MyUnit*>& vec)
{
	//벡터 포인터
	playUnit = &vec;
};


BtNode::BtNode()
{
	node_state = eBTState_FAIL;
	actor = new Actor();
}

void BtNode::Set(BlackBoard* InBB)
{
	bbData = InBB;
}

bool AttackUnit::Invoke()
{
	EAction action = eAction_Attack;
	bbData->cmQ->Push(actor, action);
	return true;
}

bool RestUnit::Invoke()
{
	EAction action = eAction_Rest;
	bbData->cmQ->Push(actor, action);
	return true;
}

bool MoveUnit::Invoke()
{
	EAction action = eAction_Move;
	bbData->cmQ->Push(actor, action);
	return true;
}
void CompositeNode::AddChild(BtNode* node)
{
	node->actor->obj = this->actor->obj;
	node->Set(this->bbData);
	mChildren.emplace_back(node);
}

const std::vector<BtNode*>& CompositeNode::GetChildren()
{
	return mChildren;
}

bool Selector::Invoke()
{
	for (auto node : GetChildren())
	{
		if (node->Invoke())
			return true;
	}
	return false;
}

bool Sequence::Invoke()
{
	for (auto node : GetChildren())
	{
		if (!node->Invoke())
			return false;
	}
	return true;
}

bool IsNearObj::Invoke()
{
	//일정 거리 내에 있으면 target으로 없으면 false
	
	for (auto it : *bbData->playUnit)
	{
		if ((int)sqrt(pow(it->curPosX - actor->obj->curPosX,2)
			+ pow(it->curPosY - actor->obj->curPosY,2)) < RECOGNITION_DISTANCE &&
			it != actor->obj &&
			it->teamBlue != actor->obj->teamBlue &&
			!it->Isdead )
		{
			if(actor->obj->target == nullptr)
				actor->obj->target = it;
			//actor->obj->Set(bbData->mTree);*/
			return true;
		}
	}
	return false;
}

bool IsAbleAtk::Invoke()
{
	//유닛 사거리내에 타겟이 있으면 true
	if (sqrt(pow(actor->obj->target->curPosX - actor->obj->curPosX,2)
			+ pow(actor->obj->target->curPosY - actor->obj->curPosY,2)) 
		< actor->obj->mUnitInfo.atk_distance * ATTACK_DISTANCE
	)
	{
		return true;
	}
	if (actor->obj->target->Isdead)
		actor->obj->target = nullptr;
	return false;
}
bool IsTargetHas::Invoke()
{
	if (actor->obj->target != nullptr && !actor->obj->target->Isdead)
	{
		if (actor->obj->frame % CALC_PATH_PER_FRAME == 0)
		{
 			actor->obj->dstTile.first = actor->obj->target->curTile.first;
			actor->obj->dstTile.second = actor->obj->target->curTile.second;
			actor->obj->Set(bbData->mTree);
		}
		return true;
	}
	else
		return false;
}
bool IsBuilt::Invoke()
{
	//가까운 건물을 목적지로지정
	//test경로
	if (actor->obj->moveTilePath.empty() 
		|| actor->obj->frame % 100 == 0)
	{
		if (actor->obj->teamBlue)
		{
			actor->obj->dstTile.first = TOWER_RED_KING_X;
			actor->obj->dstTile.second = TOWER_RED_KING_Y;
			actor->obj->Set(bbData->mTree);
		}
		else
		{
			actor->obj->dstTile.first = TOWER_BLUE_KING_X;
			actor->obj->dstTile.second = TOWER_BLUE_KING_Y;
			actor->obj->Set(bbData->mTree);
		}
	}
	return true;
}

bool IsDead::Invoke()
{
	if (actor->obj->Isdead)
		return false;
	return true;
}
bool IsCollision::Invoke()
{
	if (CollisionMgr::GetInstance().IsCollision(actor->obj,bbData->playUnit)
		&& actor->obj->frame % 10 == 0)
	{
		int curX = actor->obj->curTile.first;
		int curY = actor->obj->curTile.second;

		if (CollisionMgr::GetInstance().direction == eColDirection_Bottom)
		{
			bbData->mTree->SetTile(curX - 1, curY +1);
			bbData->mTree->SetTile(curX , curY + 1);
			bbData->mTree->SetTile(curX + 1, curY + 1);
			actor->obj->Set(bbData->mTree);
		}
		if (CollisionMgr::GetInstance().direction == eColDirection_RightBottom)
		{
			bbData->mTree->SetTile(curX + 1, curY);
			bbData->mTree->SetTile(curX , curY + 1);
			bbData->mTree->SetTile(curX + 1, curY + 1);
			actor->obj->Set(bbData->mTree);
		}
		if (CollisionMgr::GetInstance().direction == eColDirection_Right)
		{
			bbData->mTree->SetTile(curX + 1, curY - 1);
			bbData->mTree->SetTile(curX + 1, curY );
			bbData->mTree->SetTile(curX + 1, curY + 1);
			actor->obj->Set(bbData->mTree);
		}
		if (CollisionMgr::GetInstance().direction == eColDirection_RightTop)
		{
			bbData->mTree->SetTile(curX + 1, curY );
			bbData->mTree->SetTile(curX + 1, curY - 1);
			bbData->mTree->SetTile(curX , curY - 1);
			actor->obj->Set(bbData->mTree);
		}
		if (CollisionMgr::GetInstance().direction == eColDirection_Top)
		{
			bbData->mTree->SetTile(curX - 1, curY - 1);
			bbData->mTree->SetTile(curX, curY - 1);
			bbData->mTree->SetTile(curX + 1, curY - 1);
			actor->obj->Set(bbData->mTree);
		}
		if (CollisionMgr::GetInstance().direction == eColDirection_LeftTop)
		{
			bbData->mTree->SetTile(curX - 1, curY - 1);
			bbData->mTree->SetTile(curX - 1, curY );
			bbData->mTree->SetTile(curX - 1, curY + 1);
			actor->obj->Set(bbData->mTree);
		}
		if (CollisionMgr::GetInstance().direction == eColDirection_Left)
		{
			bbData->mTree->SetTile(curX - 1, curY - 1);
			bbData->mTree->SetTile(curX - 1, curY );
			bbData->mTree->SetTile(curX - 1, curY + 1);
			actor->obj->Set(bbData->mTree);
		}
		if (CollisionMgr::GetInstance().direction == eColDirection_LeftBottom)
		{
			bbData->mTree->SetTile(curX - 1, curY + 1);
			bbData->mTree->SetTile(curX - 1, curY );
			bbData->mTree->SetTile(curX , curY + 1);
			actor->obj->Set(bbData->mTree);
		}

		bbData->mTree->Set(bbData->mMap);
		return true;
	}
	return false;
}
BehaviorTree::BehaviorTree(MyUnit* InActor, BlackBoard* InBB)
	:root(nullptr)
{
}

void BehaviorTree::Init(MyUnit* InActor, BlackBoard* InBB)
{
	root = new Sequence();
	root->bbData = InBB;
	SetActor(InActor);
	//composite
	Selector* RootSelector = new Selector();
	Sequence* seqNearObj = new Sequence();
	Selector* selAttackTarget = new Selector();
	Sequence* seqAttack = new Sequence();
	Selector* selMoveTarget = new Selector();
	Sequence* seqMoveToTarget = new Sequence();
	Sequence* seqMoveToBuild = new Sequence();
	Selector* selMove = new Selector();
	Sequence* seqMoveCol = new Sequence();
	//action
	AttackUnit* actAtkUnit = new AttackUnit();
	MoveUnit* actMoveUnit = new MoveUnit();
	//condition
	IsNearObj* IsNear = new IsNearObj();
	IsAbleAtk* IsAttack = new IsAbleAtk();
	IsTargetHas* IsTarget = new IsTargetHas();
	IsBuilt* IsBuild = new IsBuilt();
	IsDead* IsDeadUnit = new IsDead();
	IsCollision* IsCol = new IsCollision();
	//트리 구성 추후 xml로 맵핑

	root->AddChild(IsDeadUnit);
	root->AddChild(RootSelector);

	RootSelector->AddChild(seqNearObj);
	RootSelector->AddChild(selMoveTarget);
	//
	seqNearObj->AddChild(IsNear);
	seqNearObj->AddChild(selAttackTarget);

	selMoveTarget->AddChild(seqMoveToTarget);
	selMoveTarget->AddChild(seqMoveToBuild);
	///
	selAttackTarget->AddChild(seqAttack);
	selAttackTarget->AddChild(selMoveTarget);
	////
	seqAttack->AddChild(IsAttack);
	seqAttack->AddChild(actAtkUnit);
	/////
	seqMoveToTarget->AddChild(IsTarget);
	seqMoveToTarget->AddChild(selMove);

	seqMoveToBuild->AddChild(IsBuild);
	seqMoveToBuild->AddChild(selMove);
	//////
	selMove->AddChild(seqMoveCol);
	selMove->AddChild(actMoveUnit);
	///////
	seqMoveCol->AddChild(IsCol);
	seqMoveCol->AddChild(actMoveUnit);
}

void BehaviorTree::InitTower(MyUnit* InActor, BlackBoard* InBB)
{
	root = new Sequence();
	root->bbData = InBB;
	SetActor(InActor);

	Selector* RootSelector = new Selector();
	Sequence* seqNearObj = new Sequence();
	Sequence* seqAttack = new Sequence();
	
	AttackUnit* actAtkUnit = new AttackUnit();
	RestUnit* actRestUnit = new RestUnit();

	IsNearObj* IsNear = new IsNearObj();
	IsAbleAtk* IsAttack = new IsAbleAtk();
	IsTargetHas* IsTarget = new IsTargetHas();
	IsDead* IsDeadUnit = new IsDead();

	root->AddChild(IsDeadUnit);
	root->AddChild(RootSelector);
	
	RootSelector->AddChild(seqNearObj);
	RootSelector->AddChild(actRestUnit);

	//
	seqNearObj->AddChild(IsNear);
	seqNearObj->AddChild(seqAttack);
	////
	seqAttack->AddChild(IsAttack);
	seqAttack->AddChild(actAtkUnit);
	/////
}
void BehaviorTree::SetActor(MyUnit* InActor)
{
	root->actor->obj = InActor;
}

void BehaviorTree::Tick()
{
	root->Invoke();
}
