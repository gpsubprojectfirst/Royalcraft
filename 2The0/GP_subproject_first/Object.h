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

	tagInfo(void) 
	:fX(0.0)
	,fY(0.0)
	,fSizeX(0.0)
	,fSizeY(0.0)
	{}

	tagInfo(float _fx, float _fy)
		: fX(_fx), fY(_fy),fSizeX(0.0),fSizeY(0.0) {}
}INFO;

class Object
{
public:
	Object();
	Object(EObject InType);

	virtual ~Object();

	virtual void Begin() {} // init
	virtual void Update(float Delta) {} //frame ���� �߰�
	virtual void Render(Gdiplus::Graphics* MemG) {}
	virtual void End() {} // release

	virtual void CopyObj(Object* dst) {}
	//�� ��ǥ ��� �޼���
	virtual void Set(CPoint pt,MyMap* map, SearchTree* mTree) {}
	//action �ż���
	virtual void Move(float Delta) {}
	virtual void Attack(float Delta) {}
	virtual void ExtraAction(float Delta) {}
	RECT GetRect(void);

	//��� ���ϴ� ����
	Gdiplus::Image* ParentImg;
	Gdiplus::Rect rc; // ���� �ε�� Asset���� �ҷ��� �̹����� rect
	Gdiplus::Rect posRc; //���� Ÿ���� ��Ʈ
	Gdiplus::Rect colRc; //�浹 ��Ʈ
	float curPosX;
	float curPosY;
	int frame;
	//�ѹ� ����Ǹ� �� ������ �ʴ� ����
	EObject Objtype;
	bool Enable;
	CString name;
	int ID;
	MyMap* mMap;
	StateManager sm;


	INFO		m_tInfo;



};

