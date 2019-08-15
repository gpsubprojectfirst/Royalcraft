#pragma once
#include "Command.h"
//#include "GameScene.h"
//class MyUnit;
//class GameScene;

//Behavior Tree에 필요한 정보를 가지고 있는 클래스
class BlackBoard
{
public:
	BlackBoard(Command& InCmQ)
	{
		cmQ = &InCmQ;
	};
	void UpdateData(std::vector<MyUnit>& vec)
	{
		//벡터 복사
		//playUnit.copy = vec;
	};
	Command* cmQ;
	std::vector<MyUnit> playUnit;
};

enum BTState {
	eBTState_SUCC,
	eBTState_FAIL,
	eBTState_RUN,
};

class BtNode
{
public:
	BtNode()
	{
		node_state = eBTState_FAIL;
		actor = new Actor();
	}
	virtual bool Invoke() = 0;
	void Set(BlackBoard* InBB)
	{
		bbData = InBB;
	}
	BTState node_state; //= eBTState_FAIL;
	Actor* actor;
	BlackBoard* bbData;
};

class ActionNode : public BtNode
{
public:
	/*virtual bool Invoke()
	{
		return true;
	}*/
	//void doActor();
private:
	//EAction action_num;
};
class CheckUnit : public ActionNode
{
public:
	virtual bool Invoke()
	{
		node_state = eBTState_RUN;

		//
		
		node_state = eBTState_SUCC;
		return true;
	}
};
class AttackUnit : public ActionNode
{
public:
	
	virtual bool Invoke()
	{
		EAction action = eAction_Attack;
		bbData->cmQ->Push(actor,action);
		return true;
	}
};
class RestUnit : public ActionNode
{
public:
	virtual bool Invoke()
	{
		EAction action = eAction_Rest;
		bbData->cmQ->Push(actor, action);
		return true;
	}
};
class MoveUnit : public ActionNode
{
public:
	virtual bool Invoke()
	{
		EAction action = eAction_Move;
		bbData->cmQ->Push(actor, action);
		return true;
	}
};
class CompositeNode : public BtNode
{
public:
	void AddChild(BtNode* node)
	{
		node->actor->obj = this->actor->obj;
		node->Set(this->bbData);
		mChildren.emplace_back(node);
	}
	const std::vector<BtNode*>& GetChildren()
	{
		return mChildren;
	}

private:
	std::vector<BtNode*> mChildren;
};

class Selector : public CompositeNode
{
public:
	virtual bool Invoke() override
	{
		for (auto node : GetChildren())
		{
			if (node->Invoke())
				return true;
		}
		return false;
	}
};

class Sequence : public CompositeNode
{
public:
	virtual bool Invoke() override
	{
		for (auto node : GetChildren())
		{
			if (!node->Invoke())
				return false;
		}
		return true;
	}
};
class ConditionNode : public BtNode
{
public:
};
class IsNearObj : public ConditionNode
{
public:
	virtual bool Invoke() override
	{
		//일정 거리 내에 있으면 target으로 없으면 false
		/*for (auto& it : bbData->playUnit)
		{
			if (abs(it->posRc.X < 3
				&& abs(it->posRc.Y < 3)))
			{
				actor->obj->target = it;
				return true;
			}
		}*/
		return true;
		return false;
	}
};
class IsAbleAtk : public ConditionNode
{
public:
	virtual bool Invoke() override
	{
		return true;
	}
};
class BehaviorTree
{
public:
	BehaviorTree(MyUnit* InActor,BlackBoard* InBB)
		:root(nullptr)
	{
		Init(InActor,InBB);
	}
	void SetActor(MyUnit* InActor)
	{
		root->actor->obj = InActor;
	}
	void Init(MyUnit* InActor,BlackBoard* InBB)
	{
		root = new Sequence();
		root->bbData = InBB;
		SetActor(InActor);
		//composite
		Selector* RootSelector = new Selector();
		Sequence* seqMove = new Sequence();
		Sequence* seqNearObj = new Sequence();
		Selector* selMoveTarget = new Selector();
		Sequence* seqAttack = new Sequence();
		//action
		AttackUnit* actAtkUnit = new AttackUnit();
		MoveUnit* actMoveUnit = new MoveUnit();
		//condition
		IsNearObj* IsNear = new IsNearObj();
		IsAbleAtk* IsAttack = new IsAbleAtk();
		
		//트리 구성 xml로 맵핑
		root->AddChild(RootSelector);
		
		RootSelector->AddChild(seqNearObj);
		RootSelector->AddChild(seqMove);

		seqNearObj->AddChild(IsNear);
		seqNearObj->AddChild(selMoveTarget);
		
		selMoveTarget->AddChild(seqAttack);
		selMoveTarget->AddChild(seqMove);

		seqAttack->AddChild(IsAttack);
		seqAttack->AddChild(actAtkUnit);

		seqMove->AddChild(actMoveUnit);		
		//Tick();
	}
	void RunSelector(Selector _InSelector)
	{
		for (auto& it : _InSelector.GetChildren())
		{
			if (it->Invoke())
			{
				;
			}
		}
	}
	void RunSequencer(Sequence _InSequence)
	{
		for (auto& it : _InSequence.GetChildren())
		{
			if (!it->Invoke())
			{
				;
			}
		}
	}

	void Tick()
	{
		while (!root->Invoke())
		{
			RunSequencer(*root);
		}
	}
	void TraverseTree()
	{

	}
private:
	Sequence* root;
};
