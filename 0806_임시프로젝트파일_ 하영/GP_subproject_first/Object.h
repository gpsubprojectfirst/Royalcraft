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
	virtual void Update(float Delta) {} //frame 변수 추가
	virtual void End() {} // release

	//action 매서드
	virtual void Move(float Delta) {}
	virtual void Attack() {}
	virtual void ExtraAction() {}

	//계속 변하는 변수
	Gdiplus::Image* ParentImg;
	Gdiplus::Rect rc; // 현재 로드된 Asset에서 불러올 이미지의 rect
	Gdiplus::Rect posRc;
	std::pair <float, float> curPos; //오브젝트의 현 위치, 원의 중심
	int frame;
	//한번 선언되면 잘 변하지 않는 변수
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

	//유닛 스탯
	float damage;
	float hp;
	EAtkType atk_type;
	float atk_speed;
	float move_speed;
	int cost;
	float AddDelta;

	std::vector<Gdiplus::Rect> moveRc; // 이동
	std::vector<Gdiplus::Rect> atkRc; // 공격
};