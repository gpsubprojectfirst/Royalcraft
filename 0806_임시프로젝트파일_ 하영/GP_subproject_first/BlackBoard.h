#pragma once
#include "Object.h"
#include "state.h"
class SceneManager;
class GameScene;
//Behavior Tree에 필요한 정보를 가지고 있는 클래스
class CurUnit
{
	//현재 유닛의 정보들
public:
private:
	Unit* curUnit;
	Object* curTarget;
	StateManager* sm;
	std::pair<int, int>* curTile;
	float atk_dist;
};
class BlackBoard
{
public:
	BlackBoard()
	{
		GameScene gs;
		playUnit = &gs.playUnit;
		cmQ = &gs.CommandQueue;
	}
	CurUnit curUnit;
	Command* cmQ;
	std::vector<MyUnit>* playUnit;
private:
	//전체 유닛의 정보들
	//좌표
};