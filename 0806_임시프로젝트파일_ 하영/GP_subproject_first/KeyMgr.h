#pragma once
#include "SingleTon.h"
#include "pch.h"
class KeyMgr :
	public SingleTon<KeyMgr>
{
public:
	void CheckKey(void);

private:
	DWORD			m_dwKey;

public:
	DWORD GetKey(void) { return m_dwKey; }
	void SetKey(void)
	{
		m_dwKey = 0x00000000;
	}

public:
	KeyMgr(void);
	~KeyMgr(void);

};

