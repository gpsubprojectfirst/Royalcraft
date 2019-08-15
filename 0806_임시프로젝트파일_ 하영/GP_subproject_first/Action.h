#pragma once
#include "Actor.h"
class Action
{
public:
	virtual void execute(Actor* actor, float Delta) {}
};

class MoveAction : public Action
{
public:
	MoveAction() {};
	void execute(Actor* actor, float Delta);
};

class AttackAction : public Action
{
public:
	AttackAction() {};
	void execute(Actor* actor, float Delta);
};

class RestAction : public Action
{
public:
	RestAction() {};
	//void execute(Actor* actor, float Delta);
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