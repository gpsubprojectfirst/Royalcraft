#pragma once
#pragma once
#include "Object.h"

class UICrown :
	public Object
{
public:
	UICrown();
	//엔딩 에니메이션을 위한 변수들 추후 수정필요
	std::vector<Gdiplus::Rect> animRc;
	float AddDelta;
	virtual void ParserXML();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
};