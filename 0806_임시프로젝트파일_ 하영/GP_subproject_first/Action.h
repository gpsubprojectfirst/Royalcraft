#pragma once
class Action
{
public:
	Action() {};
	virtual void execute(Actor* actor, float Delta) {}
};

class MoveAction : public Action
{
public:
	MoveAction() {};
	virtual void execute(Actor* actor, float Delta);
};

class AttackAction : public Action
{
public:
	AttackAction() {};
	virtual void execute(Actor* actor, float Delta);
};

class RestAction : public Action
{
public:
	RestAction() {};
	virtual void execute(Actor* actor, float Delta);
};
class ExtraAction : public Action
{
public:
	ExtraAction() {};
	void execute(Object* obj,float Delta)
	{
		//obj.ExtraAction();
	};
};