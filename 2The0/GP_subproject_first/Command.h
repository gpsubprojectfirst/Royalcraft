#pragma once
#include "Actor.h"
#include "Action.h"

class Command
{
public:
	Command()
	{

	};
	virtual ~Command() {}
	void Push(Actor* InActor, EAction InAction)
	{
		actorQue.push(InActor);
		actionQue.push(InAction);
	}
	void Pop(float Delta)
	{
		if (actionQue.front() == eAction_Rest)
		{
			RestAction rest;
			rest.execute(actorQue.front(), Delta);
		}
		if (actionQue.front() == eAction_Move)
		{
			MoveAction move;
			move.execute(actorQue.front(), Delta);
		}
		if (actionQue.front() == eAction_Attack)
		{
			AttackAction attack;
			attack.execute(actorQue.front(), Delta);
		}
		
		actorQue.pop();
		actionQue.pop();
	}

	bool Empty()
	{
		if (actorQue.empty() && actionQue.empty())
			return true;
		else
			return false;
	}

private:
	std::queue<Actor*> actorQue;
	std::queue<EAction> actionQue;
};


