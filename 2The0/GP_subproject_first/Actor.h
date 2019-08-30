#pragma once
//action who obj, unit, build, bullet
class MyUnit;
class Actor
{
public:
	Actor()
		: obj(nullptr)
		, actor_type()
	{
		
	}

	Actor(EObject _Intype)
		: obj(nullptr)
		, actor_type()
	{
		if(_Intype == eObject_Unit ||
			_Intype == eObject_Build ||
			_Intype == eObject_Bullet)
		actor_type = _Intype;
	}
	MyUnit* obj;
	EObject actor_type;
};

