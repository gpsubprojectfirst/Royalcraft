#pragma once
#include "Object.h"

class GameScene;

class UITimeEvent
{
public:
	int runTime;
	int curTime;
	GameScene* curScene;
	Object startUI;
	Object boostUpUI;

	Gdiplus::Rect blackWnd;
	Gdiplus::RectF* tempFRc;
	Gdiplus::Font font;
	Gdiplus::SolidBrush sbrush;
	Gdiplus::StringFormat format;
	std::string tempstr;
	std::wstring wide_string;
	const WCHAR* result;

	UITimeEvent();
	void Init(GameScene* inScene);
	void Update(int inTime);
	void Render(Gdiplus::Graphics* MemG);
	void CreateEnemy();
};