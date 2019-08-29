#pragma once
#define SAFE_DELETE(p)	if(p) {delete p; p = nullptr;}
#define WINSIZE_X  613
#define WINSIZE_Y 1003

#define REAL_WINSIZE_X 593
#define REAL_WINSIZE_Y 960
#define MY_FONT_SIZE 30
#define MY_FONT_SIZE_SMALL 20
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
#define ENEMY_CREATE_TERM 30
#define TIME_MAX_MINUITE 2
#define TIME_MAX_SECOND 30
#define TIME_DISPLAY_X 493
#define TIME_DISPLAY_Y 0
#define TIME_DISPLAY_WIDTH 100
#define TIME_DISPLAY_HEIGHT 30
#define COLOR_BLACK_ALPHA (Gdiplus::Color(120, 0, 0, 0)) 
#define BRUSH_BLACK_ALPHA (Gdiplus::SolidBrush(COLOR_BLACK_ALPHA))
//behavior define
#define RECOGNITION_DISTANCE 200
#define ATTACK_DISTANCE 30
#define CALC_PATH_PER_FRAME 10
//ElixirBar define
#define ELIXIR_DISPLAY_X 155
#define ELIXIR_DISPLAY_Y 910
#define ELIXIR_DISPLAY_WIDTH 400
#define ELIXIR_DISPLAY_HEIGHT 50
#define ELIXIR_COUNT_WIDTH 80
#define GAGE_FULL 100.0
#define GAGE_EMPTY 0.0
#define MAX_COST 10
#define INCREASE_TIME_TERM 0.01f
#define INCREASE_GAGE_TERM 0.1f
//HPBar define
#define HP_BAR_WIDTH 100
#define HP_BAR_HEIGHT 20
#define BASE_RECT_RATE 0.2f
#define GAGE_RECT_RATE 0.8f
#define COLOR_ERASE (Gdiplus::Color(0, 255, 255, 255))
#define BRUSH_ERASE (Gdiplus::SolidBrush(COLOR_ERASE))
//MyUnit define
#define INIT_HP 100
#define INIT_SPEED 1
#define INIT_ATK_DIST 10
#define INIT_DAMAGE 10
#define MAX_FRAME 2400
#define UNIT_FRAME_INC_DELTA 0.1f
//DeckWnd define
#define SLOT_ONE_X 167
#define SLOT_ONE_Y 808
#define SLOR_ARRANG_X 102
#define SLOT_SIZE_WIDTH 72
#define SLOT_SIZE_HEIGHT 92
#define COST_VIEW_WIDTH 50
#define COST_VIEW_HEIGHT 50

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

enum EDirectionType{
	eDirection_Bottom,
	eDirection_RightBottom,
	eDirection_Right,
	eDirection_RightTop,
	eDirection_Top,
	eDirection_Cnt,
};
enum EColDirectionType {
	eColDirection_Bottom,
	eColDirection_RightBottom,
	eColDirection_Right,
	eColDirection_RightTop,
	eColDirection_Top,
	eColDirection_LeftTop,
	eColDirection_Left,
	eColDirection_LeftBottom,
	eColDirection_Cnt,
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
	EDeck_Cnt,
};

enum EDeckSlot_Num
{
	eDeckSlot_One,
	eDeckSlot_Two,
	eDeckSlot_Three,
	eDeckSlot_Four,
	eDeckSlot_Cnt,
};