#pragma once
#include "Object.h"
class UIDeck :
	public Object
{
private:
	DECKINFO	m_tDeckInfo[4];

public:
	Gdiplus::Image* img;
public:
	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Release();

public:
	UIDeck(void);
	~UIDeck(void);
};

