#pragma once
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
#include <Digitalv.h>

class MCISound
{
public:
	const WCHAR* strName;
public:
	MCISound();
	MCISound(const WCHAR* str);
	~MCISound();
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	MCI_STATUS_PARMS mciStatus;
	MCI_GENERIC_PARMS mciGenericParms;
	MCI_SEEK_PARMS mciSeek;
	DWORD wDeviceID = 0;

	DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);
	void PlayWAV(HWND hWnd, DWORD dwID);
	void PlayWAV_Repeat(HWND hWnd, DWORD dwID);
	void StopWAV(HWND hWnd, DWORD dwID);
	void PauseWAV(HWND hWnd, DWORD dwID); //�Ͻ� ����
	void ResumeWAV(HWND hWnd, DWORD dwID); //�Ͻ� ������ ���� �ٽ� �÷���
	void CloseWAV(HWND hWnd, DWORD dwID);
	void MoveStartPosition(HWND hWnd, DWORD dwID);
	//void Release();

};
/////ref https://blog.naver.com/delpinion/90002442985
