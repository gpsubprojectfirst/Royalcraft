#pragma once
#include "Object.h"

class Action
{
public:
	Action();
	virtual ~Action() {};
	virtual void execute(Object& obj) {}
};

class moveAction : public Action
{
public:
	virtual void execute(Object& obj,float Delta)
	{
		//obj.Move(Delta);
	};
};

class AttackAction : public Action
{
public:
	virtual void execute(Object& obj)
	{
		//obj.Attack();
	};
};

class ExtraAction : public Action
{
public:
	virtual void execute(Object& obj)
	{
		//obj.ExtraAction();
	};
};