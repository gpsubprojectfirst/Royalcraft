#include "pch.h"
#include "Command.h"

void Command::Push(Actor* InActor, EAction InAction)
{
	actorQue.push(InActor);
	actionQue.push(InAction);
}

void Command::Pop(float Delta)
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
bool Command::Empty()
{
	if (actorQue.empty() && actionQue.empty())
		return true;
	else
		return false;
}