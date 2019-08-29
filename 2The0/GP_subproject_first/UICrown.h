#pragma once
#include "Object.h"

class UICrown :
	public Object
{
public:
	bool bSoundOn;
public:
	UICrown();
	//엔딩 에니메이션을 위한 변수들 추후 수정필요
	std::vector<Gdiplus::Rect> animRc[2];
	float AddDelta;
	bool teamblue; //true- blue, false- red
	Gdiplus::Image* bluecrown;
	Gdiplus::Image* redcrown;
	virtual void ParserXML();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* MemG);
	void SetTeam(bool Tflag);
};