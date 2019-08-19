#pragma once
#include "pch.h"
#include "state.h"
#include "MyMap.h"
#include "SearchTree.h"
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
	virtual void ParserXML(Object* obj) {}
	//�� ��ǥ ��� �޼���
	virtual void Set(CPoint pt,MyMap* map, SearchTree* mTree) {}
	//action �ż���
	virtual void Move(float Delta) {}
	virtual void Attack(float Delta) {}
	virtual void ExtraAction(float Delta) {}

	//��� ���ϴ� ����
	Gdiplus::Image* ParentImg;
	Gdiplus::Rect rc; // ���� �ε�� Asset���� �ҷ��� �̹����� rect
	Gdiplus::Rect posRc; //���� Ÿ���� ��Ʈ
	COORD curPos;
	int frame;
	//�ѹ� ����Ǹ� �� ������ �ʴ� ����
	EObject Objtype;
	bool Enable;
	CString name;
	int ID;

	MyMap* mMap;
	StateManager sm;


	//static void SetBmp(std::vector<Gdiplus::Image*>* _pvecbmp) { m_pVecImg = _pvecbmp; }
	//virtual void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	//virtual void Release();

protected:
	//INFO		m_tInfo;
	static std::vector<Gdiplus::Image*>* m_pVecImg;


};

