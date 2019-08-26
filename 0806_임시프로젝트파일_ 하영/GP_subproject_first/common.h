#pragma once
#define SAFE_DELETE(p)	if(p) {delete p; p = nullptr;}
#define WINSIZE_X  613
#define WINSIZE_Y 1003

#define REAL_WINSIZE_X 593
#define REAL_WINSIZE_Y 960
#define KING CString("king")

//tower position define
#define TOWER_RED_KING_X 11
#define TOWER_RED_KING_Y 3
#define TOWER_RED_SUBL_X 5
#define TOWER_RED_SUBL_Y 7
#define TOWER_RED_SUBR_X 16
#define TOWER_RED_SUBR_Y 7
#define TOWER_BLUE_KING_X 11
#define TOWER_BLUE_KING_Y 30
#define TOWER_BLUE_SUBL_X 5
#define TOWER_BLUE_SUBL_Y 26
#define TOWER_BLUE_SUBR_X 16
#define TOWER_BLUE_SUBR_Y 26
//time define
#define ENEMY_CREATE_TERM 10
#define TIME_MAX_MINUITE 2
#define TIME_MAX_SECOND 30
#define TIME_DISPLAY_X 493
#define TIME_DISPLAY_Y 0
#define TIME_DISPLAY_WIDTH 100
#define TIME_DISPLAY_HEIGHT 30
//behavior define
#define RECOGNITION_DISTANCE 200
#define ATTACK_DISTANCE 30
#define CALC_PATH_PER_FRAME 10

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

enum EUnit_ID
{
	eUnit_Knight,
	eUnit_Axeman,
	eUnit_Darknight,
	eUnit_Electric,
	eUnit_Giant,
	eUnit_Archer,
	eUnit_Lumberjack,
	eUnit_Musket,
	eUnit_Varkirey,
	eUnit_Vavarian,
	eUnit_Vendit,
	eUnit_Wizard,
	eUnit_Cnt,
};
enum EBuild_ID
{
	eBuild_RedKing,
	eBuild_RedSubL,
	eBuild_RedSubR,
	eBuild_BlueKing,
	eBuild_BlueSubL,
	eBuild_BlueSubR,
	eBuild_Cnt,
};
enum EBullet_ID
{
	eBullet_Fire,
	eBullet_Arrow,
	eBullet_Bullet,
	eBullet_Misile,
	eBullet_Cnt,
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