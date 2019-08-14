#pragma once
#include "pch.h"
#include "Action.h"
enum BTState {
	eBTState_SUCC,
	eBTState_FAIL,
	eBTState_RUN,
};

class BtNode
{
public:
	BtNode();
	virtual bool Invoke() = 0;
	BTState node_state; //= eBTState_FAIL;
};

class ActionNode : public BtNode
{
public:
	//void doActor();
private:
	
};
class CheckUnit : public ActionNode
{
public:
	virtual bool Invoke()
	{
		//À¯´ÖÀ» Ã¼Å©
		return true;
	}
};
class AttackUnit : public ActionNode
{
public:
	virtual bool Invoke()
	{
		//À¯´ÖÀ» °ø°Ý
		return true;
	}
};
class RestUnit : public ActionNode
{
public:
	virtual bool Invoke()
	{
		//À¯´Ö ÈÞ½Ä
		return true;
	}
};
class MoveUnit : public ActionNode
{
public:
	virtual bool Invoke()
	{
		//À¯´Ö ÀÌµ¿
		return true;
	}
};
class CompositeNode : public BtNode
{
public:
	void AddChild(BtNode* node)
	{
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
	virtual bool Invoke() override
	{
		return true;
	}
};
class BehaviorTree
{
public:
	BehaviorTree()
		:root(nullptr)
	{
		Init();
	}
	void Init()
	{
		root = new Sequence();
		
		//composite
		Selector* RootSelector = new Selector();
		Sequence* sequence = new Sequence();
		Sequence* seqMove = new Sequence();
		Sequence* seqAttack = new Sequence();
		Selector* selAtktype = new Selector();
		//action
		AttackUnit* actAtkUnit = new AttackUnit();
		MoveUnit* actMoveUnit = new MoveUnit();
		//condition
		ConditionNode* IsNearTarget = new ConditionNode();
		ConditionNode* IsMelee = new ConditionNode();
		
		//Æ®¸® ±¸¼º xml·Î ¸ÊÇÎ
		root->AddChild(RootSelector);
		
		RootSelector->AddChild(seqAttack);
		RootSelector->AddChild(seqMove);

		seqAttack->AddChild(IsNearTarget);
		seqAttack->AddChild(selAtktype);
		
		selAtktype->AddChild(IsMelee);
		
		seqAttack->AddChild(actMoveUnit);
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
			//Æ®¸® ¼øÈ¸
		}
	}
private:
	Sequence* root;
	//Actor actor;
	//std::vector<Action*> actionQueue;
};
