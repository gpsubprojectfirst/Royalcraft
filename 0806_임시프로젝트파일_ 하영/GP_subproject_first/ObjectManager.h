#pragma once
#include "SingleTon.h"
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
	virtual void Update(float Delta, int frame) {} //frame 변수 추가
	virtual void End() {} // release

	Gdiplus::Image* ParentImg;
	Gdiplus::Rect rc; // 현재 rect
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

	std::vector<Gdiplus::Rect> moveRc; // 이동
	std::vector<Gdiplus::Rect> atkRc; // 공격
};

class ObjectManager 
	: public SingleTon<ObjectManager>
{
public:
	ObjectManager();
	Object* GetObj(int n);
	myUnit* GetMyUnit(int n);
	//static ObjectManager& GetInstance();
	//void Update(float Delta);
private:
	std::vector<Object*> mObj;
	std::vector<myUnit*> UnitObj;
	Object* curObj;
	myUnit* curUnit;
};
