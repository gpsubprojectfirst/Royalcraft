#include "pch.h"
#include "Action.h"

void MoveAction::execute(Actor* actor, float Delta)
{
	actor->obj->sm.ChangeState(eState_Move);
	actor->obj->Move(Delta);
};
void AttackAction::execute(Actor* actor, float Delta)
{
	actor->obj->sm.ChangeState(eState_Attack);
	if (actor->obj->frame == 10)
	{
		actor->obj->Attack(Delta);
		actor->obj->frame++;
	}
};