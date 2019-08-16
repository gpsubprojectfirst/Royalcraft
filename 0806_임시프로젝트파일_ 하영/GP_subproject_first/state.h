#pragma once
static bool bleft = false;

class State
{
public:
	State();
	State(EState InState);
	virtual bool ChangeState(EState InState) = 0;

protected:
	EState statetype;
};

class State_Idle : public State
{
public:
	State_Idle();
	virtual bool ChangeState(EState InState) override;
};

class State_Move : public State
{
public:
	State_Move();
	virtual bool ChangeState(EState InState) override;
};

class State_Attack : public State
{
public:
	State_Attack();
	virtual bool ChangeState(EState InState) override;
};

class StateManager
{
public:
	StateManager()
		: CurState(eState_Idle)
	{

	}

	void Add(State* pState)
	{
		statelist.emplace_back(pState);
	}

	bool ChangeState(EState InState)
	{
		if (statelist[CurState]->ChangeState(InState))
		{
			CurState = InState;
			return true;
		}

		return false;
	}

	void Update()
	{
		
	}

	EState GetCurState()
	{
		return CurState;
	}
private:
	EState CurState;
	std::vector<State*> statelist;
};
