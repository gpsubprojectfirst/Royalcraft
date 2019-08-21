#pragma once
#include "pch.h"
#include "state.h"
#include "MyMap.h"
#include "SearchTree.h"

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fSizeX;
	float	fSizeY;

	tagInfo(void) {}

	tagInfo(float _fx, float _fy)
		: fX(_fx), fY(_fy) {}
}INFO;

class Object
{
public:
	Object();
	Object(EObject InType);

	virtual ~Object();

	virtual void Begin() {} // init
	virtual void Update(float Delta) {} //frame 변수 추가
	virtual void Render(Gdiplus::Graphics* MemG) {}
	virtual void End() {} // release

	virtual void CopyObj(Object* dst) {}
	virtual void ParserXML(Object* obj) {}
	//맵 좌표 계산 메서드
	virtual void Set(CPoint pt,MyMap* map, SearchTree* mTree) {}
	//action 매서드
	virtual void Move(float Delta) {}
	virtual void Attack(float Delta) {}
	virtual void ExtraAction(float Delta) {}
	RECT GetRect(void);

	//계속 변하는 변수
	Gdiplus::Image* ParentImg;
	Gdiplus::Rect rc; // 현재 로드된 Asset에서 불러올 이미지의 rect
	Gdiplus::Rect posRc; //현재 타일의 렉트
	float curPosX;
	float curPosY;
	int frame;
	//한번 선언되면 잘 변하지 않는 변수
	EObject Objtype;
	bool Enable;
	CString name;
	int ID;
	MyMap* mMap;
	StateManager sm;


	INFO		m_tInfo;



};

