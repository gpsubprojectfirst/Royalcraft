#pragma once
#include "Object.h"
#include "state.h"
class SceneManager;
class GameScene;
//Behavior Tree�� �ʿ��� ������ ������ �ִ� Ŭ����
class CurUnit
{
	//���� ������ ������
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
	//��ü ������ ������
	//��ǥ
};