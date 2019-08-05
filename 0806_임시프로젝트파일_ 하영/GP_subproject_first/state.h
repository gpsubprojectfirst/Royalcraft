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
		: CurState(eState_Attack)
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
		bleft = false;
		if (GetAsyncKeyState(VK_LEFT) & 0x8001)
		{
			bleft = false;
			ChangeState(eState_Move);
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
		{
			bleft = true;
			ChangeState(eState_Attack);
		}
		else if (GetAsyncKeyState('A'||'a') & 0x8001)
		{
			bleft = false;
			ChangeState(eState_Attack);
		}
		else
		{
			//bleft = true;
			ChangeState(eState_Idle);
		}
	}

	EState GetCurState()
	{
		return CurState;
	}
private:
	EState CurState;
	std::vector<State*> statelist;
};
