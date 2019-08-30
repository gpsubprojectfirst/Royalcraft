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
	void Push(Actor* InActor, EAction InAction);
	void Pop(float Delta);
	bool Empty();

private:
	std::queue<Actor*> actorQue;
	std::queue<EAction> actionQue;
};


