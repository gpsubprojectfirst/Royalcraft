#pragma once
#include "Command.h"
//#include "GameScene.h"
class MyUnit;
//class GameScene;

enum BTState {
	eBTState_SUCC,
	eBTState_FAIL,
	eBTState_RUN,
};

//Behavior Tree에 필요한 정보를 가지고 있는 클래스
class BlackBoard
{
public:
	BlackBoard(Command& InCmQ,SearchTree* InTree,MyMap* InMap);
	void UpdateData(std::vector<MyUnit*>& vec);
	MyMap* mMap;
	Command* cmQ;
	SearchTree* mTree;
	std::vector<MyUnit*>* playUnit;
};



class BtNode
{
public:
	BtNode();
	virtual bool Invoke() = 0;
	void Set(BlackBoard* InBB);
	BTState node_state; //= eBTState_FAIL;
	Actor* actor;
	BlackBoard* bbData;
};

class ActionNode : public BtNode
{
public:
private:
	//EAction action_num;
};
class CheckUnit : public ActionNode
{
public:
	virtual bool Invoke();
};
class AttackUnit : public ActionNode
{
public:
	virtual bool Invoke();
};
class RestUnit : public ActionNode
{
public:
	virtual bool Invoke();
};
class MoveUnit : public ActionNode
{
public:
	virtual bool Invoke();
};
class CompositeNode : public BtNode
{
public:
	void AddChild(BtNode* node);
	const std::vector<BtNode*>& GetChildren();

private:
	std::vector<BtNode*> mChildren;
};

class Selector : public CompositeNode
{
public:
	virtual bool Invoke() override;
};

class Sequence : public CompositeNode
{
public:
	virtual bool Invoke() override;
};
class ConditionNode : public BtNode
{
public:
};
class IsNearObj : public ConditionNode
{
public:
	virtual bool Invoke() override;
};
class IsAbleAtk : public ConditionNode
{
public:
	virtual bool Invoke() override;
};
class IsTargetHas : public ConditionNode
{
public:
	virtual bool Invoke() override;
};
class IsBuilt : public ConditionNode
{
public:
	virtual bool Invoke() override;
};
class IsDead : public ConditionNode
{
public:
	virtual bool Invoke() override;
};
class IsCollision : public ConditionNode
{
public:
	virtual bool Invoke() override;
};
class BehaviorTree
{
public:
	BehaviorTree(MyUnit* InActor, BlackBoard* InBB);
	void SetActor(MyUnit* InActor);
	void Init(MyUnit* InActor, BlackBoard* InBB);
	void InitTower(MyUnit* InActor, BlackBoard* InBB);

	void Tick();
private:
	Sequence* root;
};
