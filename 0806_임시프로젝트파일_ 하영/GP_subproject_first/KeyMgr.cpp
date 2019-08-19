#include "pch.h"
#include "KeyMgr.h"

KeyMgr::KeyMgr(void)
{
}

KeyMgr::~KeyMgr(void)
{
}

void KeyMgr::CheckKey(void)
{
	m_dwKey = 0x00000000;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
		m_dwKey |= KEY_LBUTTON;

	if (GetAsyncKeyState(VK_RBUTTON) & 0x0001)
		m_dwKey |= KEY_RBUTTON;

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
		m_dwKey |= KEY_SPACE;

	if (GetAsyncKeyState('Z') & 0x0001)
		m_dwKey |= KEY_Z;

	if (GetAsyncKeyState(VK_F1) & 0x8001)
		m_dwKey |= KEY_F1;
}