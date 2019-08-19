#pragma once
#include "pch.h"

#include <atlbase.h>
#include <memory>
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "dsound.lib")


class SoundMgr
{
private:
	//directx sdk (����ũ�μ���Ʈ���� ��ǻ�Ϳ��ִ� �ϵ��� ���� ����Ҽ� �ְ�
	// �������� �Լ���, ���������� �����س��� ������ϰ� ���̺귯�������� ����.)
	//���̷�Ʈ ���� �������̽�
	LPDIRECTSOUND				m_pSound; //����ī�带 ��ǥ�ϴ� ��ü.
	vector<LPDIRECTSOUNDBUFFER> m_vecSoundBuff;	//���������� �ε��ؼ� ������ ����

public:
	HRESULT Init(void);	// ��ġ�� �ʱ�ȭ �ϴ¿�Ȱ.
	HRESULT LoadWave(TCHAR* pFileName);	//���ϰ�θ� ���� ������ �о� �帮�ڴ�.
	void SoundPlay(int iIndex /*���° ������ ����ҷ�?*/, DWORD dwFlag/*���ѷ���, �ѹ�*/); //������ ��� �ϰڴ�.
	void SoundStop(int iIndex);
	bool SoundPlaying(int iIndex);	// ���� iIndex��° ���尡 ����ǰ��ִ��� �ƴ���.

private:
	static SoundMgr* m_pInstance;

public:
	static inline SoundMgr* GetInstance(void)
	{
		if (!m_pInstance)
			m_pInstance = new SoundMgr;

		return m_pInstance;
	}
public:
	inline void DestroyInst(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

private:
	SoundMgr(void);
	~SoundMgr(void);
};

