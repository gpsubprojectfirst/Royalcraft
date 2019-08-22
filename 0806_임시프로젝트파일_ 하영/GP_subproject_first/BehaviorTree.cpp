#include "pch.h"
#include "BehaviorTree.h"
#include "myUnit.h"

BlackBoard::BlackBoard(Command& InCmQ,SearchTree* InTree)
{
	cmQ = &InCmQ;
	mTree = InTree;
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

bool CheckUnit::Invoke()
{
	node_state = eBTState_RUN;

	//

	node_state = eBTState_SUCC;
	return true;
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
			+ pow(it->curPosY - actor->obj->curPosY,2)) < 400 &&
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
		< actor->obj->mUnitInfo.atk_distance * 30
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
	if (actor->obj->target != nullptr )
	{
		if (actor->obj->frame == 0)
		{
			actor->obj->frame++;
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
	if (actor->obj->moveTilePath.empty())
	{
		actor->obj->dstTile.first = 10;
		actor->obj->dstTile.second = 3;
		actor->obj->Set(bbData->mTree);
	}
	return true;
}

bool IsDead::Invoke()
{
	if (actor->obj->Isdead)
		return false;
	return true;
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

	//action
	AttackUnit* actAtkUnit = new AttackUnit();
	MoveUnit* actMoveUnit = new MoveUnit();
	//condition
	IsNearObj* IsNear = new IsNearObj();
	IsAbleAtk* IsAttack = new IsAbleAtk();
	IsTargetHas* IsTarget = new IsTargetHas();
	IsBuilt* IsBuild = new IsBuilt();
	IsDead* IsDeadUnit = new IsDead();
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
	seqMoveToTarget->AddChild(actMoveUnit);

	seqMoveToBuild->AddChild(IsBuild);
	seqMoveToBuild->AddChild(actMoveUnit);
	//Tick();
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

	root->AddChild(RootSelector);
	root->AddChild(IsDeadUnit);
	RootSelector->AddChild(actRestUnit);

	RootSelector->AddChild(seqNearObj);
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

void BehaviorTree::RunSelector(Selector _InSelector)
{
	for (auto& it : _InSelector.GetChildren())
	{
		if (it->Invoke())
		{
			;
		}
	}
}

void BehaviorTree::RunSequencer(Sequence _InSequence)
{
	for (auto& it : _InSequence.GetChildren())
	{
		if (!it->Invoke())
		{
			;
		}
	}
}

void BehaviorTree::Tick()
{
	root->Invoke();
}

void BehaviorTree::TraverseTree()
{

}