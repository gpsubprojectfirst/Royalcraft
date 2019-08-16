#pragma once
//action À» ÇÏ´Â obj, unit, build, bullet
class MyUnit;
class Actor
{
public:
	Actor()
	{

	}

	Actor(EObject _Intype)
	{
		if(_Intype == eObject_Unit ||
			_Intype == eObject_Build ||
			_Intype == eObject_Bullet)
		actor_type = _Intype;
	}
	MyUnit* obj;
	EObject actor_type;
};

