#pragma once
#include "Object.h"

class Action
{
public:
	Action();
	virtual ~Action() {};
	virtual void execute(Object& obj);
};

class moveAction : public Action
{
public:
	virtual void execute(Object& obj)
	{
		//obj.move()
	};
	moveAction();
};

class AttackAction : public Action
{
public:
	virtual void execute(Object& obj)
	{
		//obj.attak()
	};
};