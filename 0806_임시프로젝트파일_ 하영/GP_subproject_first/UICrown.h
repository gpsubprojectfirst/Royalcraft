#pragma once
#pragma once
#include "Object.h"

class UICrown :
	public Object
{
public:
	UICrown();
	//���� ���ϸ��̼��� ���� ������ ���� �����ʿ�
	std::vector<Gdiplus::Rect> animRc;
	float AddDelta;
	virtual void ParserXML();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
};