#pragma once
#include "stdafx.h"
#include "Player.h"

class InputManager 
{
public:
	DWORD m_dwKey;
	void SetKeyState();
	DWORD KeyState();
	KeyIn m_KeyInput;
};