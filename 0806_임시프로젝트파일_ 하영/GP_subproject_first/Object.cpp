#include "pch.h"
#include "Object.h"


Object::Object()
	: Objtype(eObject_None)
	, Enable(true)
	, ID(0)
	, ParentImg(nullptr)
	,posRc(0,0,0,0)
	, curPosX(0.0)
	, curPosY(0.0)
	,frame(0)
{
	
};

Object::Object(EObject InType)
	:Objtype(InType)
	, Enable(true)
	, ID(0)
	, ParentImg(nullptr)
	, posRc(0, 0, 0, 0)
	, curPosX(0.0)
	, curPosY(0.0)
	,frame(0)
{

}

RECT Object::GetRect(void)
{
	RECT rc =
	{
		long(m_tInfo.fX - m_tInfo.fSizeX / 2),
		long(m_tInfo.fY - m_tInfo.fSizeY / 2),
		long(m_tInfo.fX + m_tInfo.fSizeX / 2),
		long(m_tInfo.fY + m_tInfo.fSizeY / 2)
	};

	return rc;
}

Object::~Object()
{

}


