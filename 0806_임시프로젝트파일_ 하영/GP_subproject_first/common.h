#pragma once
#define SAFE_DELETE(p)	if(p) {delete p; p = NULL;}
#define WINSIZE_X  660//520
#define WINSIZE_Y 1003//860

#define REAL_WINSIZE_X 593//640
#define REAL_WINSIZE_Y 960

const static int TILESIZEX = 27;
const static int TILESIZEY = 22;

const static int TILECNTX = 22;
const static int TILECNTY = 44;

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

enum EAtkType
{
	eAttack_None,
	eAttack_Melee,
	eAttack_NonMelee,
	eAttack_Cnt,
};

enum SCENE
{
	SCENE_LOGO,
	SCENE_LOBBY,
	SCENE_GAME,
	SCENE_END,
};
