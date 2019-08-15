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
	actor->obj->Attack(Delta);
};