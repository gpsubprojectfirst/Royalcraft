#pragma once
#define SAFE_DELETE(p)	if(p) {delete p; p = NULL;}
enum EState {
	eState_Idle,
	eState_Move,
	eState_Attack,
	eState_Cnt
};
enum EObject
{
	eObject_None,
	eObject_Unit,
	eObject_Build,
	eObject_Bullet,
	eObject_Cnt,
};

enum SCENE
{
	SCENE_LOGO,
	SCENE_LOBBY,
	SCENE_GAME,
	SCENE_END,
};