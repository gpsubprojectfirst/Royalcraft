#pragma once
#include "pch.h"
#include "state.h"

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
	virtual void Update(float Delta) {} //frame ���� �߰�
	virtual void End() {} // release

	//action �ż���
	virtual void Move(float Delta) {}
	virtual void Attack() {}
	virtual void ExtraAction() {}

	//��� ���ϴ� ����
	Gdiplus::Image* ParentImg;
	Gdiplus::Rect rc; // ���� �ε�� Asset���� �ҷ��� �̹����� rect
	Gdiplus::Rect posRc;
	std::pair <float, float> curPos; //������Ʈ�� �� ��ġ, ���� �߽�
	int frame;
	//�ѹ� ����Ǹ� �� ������ �ʴ� ����
	EObject Objtype;
	bool Enable;
	CString name;
	int ID;
	
	StateManager sm;
	//static void SetBmp(std::vector<Gdiplus::Image*>* _pvecbmp) { m_pVecImg = _pvecbmp; }
	//virtual void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	//virtual void Release();

protected:
	INFO		m_tInfo;
	static std::vector<Gdiplus::Image*>* m_pVecImg;

};

class myUnit : public Object
{
public:
	myUnit();
	virtual void Update(float Delta);

	virtual void Move(float Delta);
	virtual void Attack();
	virtual void ExtraAction();

	//���� ����
	float damage;
	float hp;
	EAtkType atk_type;
	float atk_speed;
	float move_speed;
	int cost;
	float AddDelta;

	std::vector<Gdiplus::Rect> moveRc; // �̵�
	std::vector<Gdiplus::Rect> atkRc; // ����
};