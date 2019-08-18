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
	//���� ������
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
	//���� �Ÿ� ���� ������ target���� ������ false
	
	for (auto it : *bbData->playUnit)
	{
		if (sqrt(pow(it->curPos.X - actor->obj->curPos.X,2)
			+ pow(it->curPos.Y - actor->obj->curPos.Y,2)) < 100 &&
			it != actor->obj &&
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
	//���� ��Ÿ����� Ÿ���� ������ true
	if (sqrt(pow(actor->obj->target->curPos.X - actor->obj->curPos.X,2)
			+ pow(actor->obj->target->curPos.Y - actor->obj->curPos.Y,2)) 
		< actor->obj->atk_distance
	)
	{
			return true;
	}
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
	//����� �ǹ��� ������������
	//test���
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
	if (!actor->obj->Isdead)
		return true;
	return false;
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
	IsDead* IsDeadUnit = new IsDead();
	//Ʈ�� ���� ���� xml�� ����
	root->AddChild(RootSelector);
	root->AddChild(IsDeadUnit);

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
	root->Invoke();
}

void BehaviorTree::TraverseTree()
{

}