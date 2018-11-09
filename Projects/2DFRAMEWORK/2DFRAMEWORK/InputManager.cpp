#include "stdafx.h"
#include "InputManager.h"
#include "Framework.h"

CInputManager::CInputManager()
{
}


CInputManager::~CInputManager()
{
}
void CInputManager::SetKeyState()
{
	m_dwKey = 0;

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_dwKey |= KEY_RIGHT;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_dwKey |= KEY_LEFT;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_dwKey |= KEY_UP;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_dwKey |= KEY_DOWN;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_dwKey |= KEY_SPACE;
	}

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_dwKey |= KEY_LBUTTON;
	}

	if (GetAsyncKeyState(VK_F5))
	{
		FRAMEWORK->SetClientReadyInfo(TRUE);
		m_dwKey |= KEY_READY;
	}
}

DWORD CInputManager::GetKeyState()
{
	return m_dwKey;

}

void CInputManager::SetPos(void)
{
	GetCursorPos(&m_ptMousePos);
	ScreenToClient(g_hWnd, &m_ptMousePos);
}

POINT CInputManager::GetPos(void)
{
	return m_ptMousePos;

}
