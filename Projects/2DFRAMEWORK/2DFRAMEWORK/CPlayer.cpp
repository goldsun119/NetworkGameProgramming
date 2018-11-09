#include "stdafx.h"
#include "CPlayer.h"
#include "CGameObject.h"
#include "InputManager.h"

CPlayer::CPlayer()
{
	Speed = 3.0f;
	m_Pos.x = 200.0f;
	m_Pos.y = 500.0f;
	Size = 30;
	m_size = 50;
}


CPlayer::~CPlayer()
{
}

void CPlayer::CheckKey()
{

	DWORD Key = INPUTMANAGER->GetKeyState();

	if (Key & KEY_LEFT)
	{
		m_Pos.x -= Speed;
	}
	if (Key & KEY_RIGHT)
	{
		m_Pos.x += Speed;
	}
	if (Key & KEY_UP)
	{
		m_Pos.y -= Speed;
	}
	if (Key & KEY_DOWN)
	{
		m_Pos.y += Speed;
	}
}

void CPlayer::Update()
{
	CheckKey();

}

void CPlayer::Render(HDC m_hdc)
{

}
