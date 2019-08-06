#include "pch.h"

#include "Object.h"

Object::Object()
	: Objtype(eObject_None)
	, Enable(true)
	, ID(0)
	, ParentImg(nullptr)
{

};
Object::Object(EObject InType)
	:Objtype(InType)
	, Enable(true)
	, ID(0)
	, ParentImg(nullptr)
{

}
Object::~Object()
{

}

myUnit::myUnit()
	: Object(EObject::eObject_Unit)
{
	sm.Add(new State_Idle);
	sm.Add(new State_Move);
	sm.Add(new State_Attack);
}
void myUnit::Update(float Delta)
{

}

