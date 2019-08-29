#include "pch.h"

State::State()
	: statetype(eState_Cnt)
{

}

State::State(EState InState)
	: statetype(InState)
{

}

State_Idle::State_Idle()
{
}

bool State_Idle::ChangeState(EState InState)
{
	switch (InState)
	{
	case eState_Move:
		return true;
	case eState_Attack:
		return true;
	case eState_Dead:
		return true;
	}
	return	false;
};

State_Move::State_Move()
{
	
}



bool State_Move::ChangeState(EState InState)
{
	switch (InState)
	{
	case eState_Idle:
		return true;
	case eState_Attack:
		return true;
	case eState_Dead:
		return true;
	}
	return false;
};

// АјАн
State_Attack::State_Attack()
{
	
}

bool State_Attack::ChangeState(EState InState)
{
	switch (InState)
	{
	case eState_Idle:
		return true;
	case eState_Move:
		return true;
	case eState_Dead:
		return true;

	}
	return false;
};

State_Dead::State_Dead()
{

}

bool State_Dead::ChangeState(EState InState)
{
	return false;
};