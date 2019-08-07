#pragma once
#include "pch.h"
#include "Action.h"
class btNode
{
public:
	virtual bool Invoke() = 0;
};

class ActionNode : public btNode
{
public:
	void doActor();
private:
	
};
class CompositeNode : public btNode
{
public:
	void AddChild(btNode* node)
	{
		mChildren.emplace_back(node);
	}
	const std::vector<btNode*>& GetChildren()
	{
		return mChildren;
	}

private:
	std::vector<btNode*> mChildren;
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

class BehaviorTree
{
public:
private:
	//Actor actor;
	//std::vector<Action*> actionQueue;
};
