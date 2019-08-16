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
	
	for (auto& it : *bbData->playUnit)
	{
		if (sqrt(abs(it->posRc.X - actor->obj->posRc.X)
			+ abs(it->posRc.Y - actor->obj->posRc.Y)) < 30 &&
			it != actor->obj)
		{
			actor->obj->target = it;
			actor->obj->Set(bbData->mTree);
			return true;
		}
	}
	return false;
}

bool IsAbleAtk::Invoke()
{
	//유닛 사거리내에 다른 유닛이 있으면 true
	for (auto& it : *bbData->playUnit)
	{
		//제곱근 연산 느리면 변경
		if (sqrt(abs(it->posRc.X - actor->obj->posRc.X)
			+ abs(it->posRc.Y - actor->obj->posRc.Y)) < actor->obj->atk_distance &&
			it != actor->obj)
		{
			return true;
		}
	}
	return false;
}
bool IsTargetHas::Invoke()
{
	if (actor->obj->target != nullptr)
		return true;
	else
		return false;
}
bool IsBuilt::Invoke()
{
	actor->obj->Set(bbData->mTree);
	return true;
}
BehaviorTree::BehaviorTree(MyUnit* InActor, BlackBoard* InBB)
	:root(nullptr)
{
	Init(InActor, InBB);
}
void BehaviorTree::Init(MyUnit* InActor, BlackBoard* InBB)
{
	root = new Sequence();
	root->bbData = InBB;
	SetActor(InActor);
	//composite
	Selector* RootSelector = new Selector();
	Selector* selMoveTarget = new Selector();
	Sequence* seqNearObj = new Sequence();
	Selector* selAttackTarget = new Selector();
	Sequence* seqAttack = new Sequence();
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

	//트리 구성 추후 xml로 맵핑
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
	while (!root->Invoke())
	{
		RunSequencer(*root);
	}
}

void BehaviorTree::TraverseTree()
{

}