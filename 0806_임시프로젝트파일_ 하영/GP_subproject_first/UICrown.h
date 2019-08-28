#pragma once
#include "Object.h"

class UICrown :
	public Object
{
public:
	bool bSoundOn;
public:
	UICrown();
	//���� ���ϸ��̼��� ���� ������ ���� �����ʿ�
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