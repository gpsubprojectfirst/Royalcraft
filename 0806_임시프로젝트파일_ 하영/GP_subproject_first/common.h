#pragma once
#define SAFE_DELETE(p)	if(p) {delete p; p = NULL;}
#define WINSIZE_X  613
#define WINSIZE_Y 1003

#define REAL_WINSIZE_X 593
#define REAL_WINSIZE_Y 960

const static int TILESIZEX = 27;
const static int TILESIZEY = 22;

const static int TILECNTX = 22;
const static int TILECNTY = 44;

const DWORD		KEY_LBUTTON = 0x00000004;
const DWORD		KEY_RBUTTON = 0x00000002;
const DWORD		KEY_SPACE = 0x00000001;
const DWORD		KEY_Z = 0x00000008;
const DWORD		KEY_F1 = 0x00000010;

enum EState {
	eState_Idle,
	eState_Move,
	eState_Attack,
	eState_Cnt,
};

enum EObject
{
	eObject_None,
	eObject_Unit,
	eObject_Build,
	eObject_Bullet,
	eObject_Ui,
	eObject_Cnt,
};

enum EAction
{
	eAction_Rest,
	eAction_Move,
	eAction_Attack,
};
enum EAtkType
{
	eAttack_None,
	eAttack_Melee,
	eAttack_NonMelee,
	eAttack_Cnt,
};

enum EScene
{
	EScene_LOGO,
	EScene_LOBBY,
	EScene_EDITOR,
	EScene_GAME,
	EScene_END,
};

enum EUnit_ID
{
	UNIT_Knight,
	UNIT_Barbarian,
	UNIT_Giant,
	UNIT_END,
};

enum EDeck_type
{
	EDeck_KNIGHT,
	EDeck_Axeman,
	EDeck_Darknight,
	EDeck_Electric,
	EDeck_Giant,
	EDeck_Archer,
	EDeck_Lumberjack,
	EDeck_Musket,
	EDeck_Varkirey,
	EDeck_Vavarian,
	EDeck_Vendit,
	EDeck_Wizard,
};