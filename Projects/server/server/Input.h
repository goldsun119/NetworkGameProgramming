#pragma once
#include "stdafx.h"

class InputManager 
{
public:
	DWORD m_dwKey;
	void SetKeyState();
	DWORD KeyState();
};
