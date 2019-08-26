#pragma once
#define SAFE_DELETE(p)	if(p) {delete p; p = nullptr;}
#define WINSIZE_X  613
#define WINSIZE_Y 1003

#define REAL_WINSIZE_X 593
#define REAL_WINSIZE_Y 960
#define KING CString("king")

const static int TILESIZEX = 27;
const static int TILESIZEY = 22;

const static int TILECNTX = 22;
const static int TILECNTY = 44;

const DWORD		KEY_SPACE = 0x00000001;
const DWORD		KEY_RBUTTON = 0x00000002;
const DWORD		KEY_LBUTTON = 0x00000004;
const DWORD		KEY_Z = 0x00000008;
const DWORD		KEY_F1 = 0x00000010;
const DWORD		KEY_ESC = 0x00000020;
const DWORD		KEY_ENTER = 0x0000040;

enum EState {
	eState_Idle,
	eState_Move,
	eState_Attack,
	eState_Dead,
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
	eAttack_Melee,
	eAttack_NonMelee,
};

enum EScene
{
	EScene_Logo,
	EScene_Lobby,
	EScene_Editor,
	EScene_Game,
	EScene_End,
};

enum EDeck_type
{
	EDeck_Knight,
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