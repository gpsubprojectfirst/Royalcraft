#include "pch.h"

#include "Object.h"

Object::Object()
	: Objtype(eObject_None)
	, Enable(true)
	, ID(0)
	, ParentImg(nullptr)
	,posRc(0,0,0,0)
	, curPos{ 0, 0 }
	,frame(0)
{
};

Object::Object(EObject InType)
	:Objtype(InType)
	, Enable(true)
	, ID(0)
	, ParentImg(nullptr)
	, posRc(0, 0, 0, 0)
	, curPos{ 0, 0 }
	,frame(0)
{

}
Object::~Object()
{

}


