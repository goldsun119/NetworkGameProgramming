#include "stdafx.h"
#include "CPlayer.h"
#include "CGameObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "CBullet.h"
CPlayer::CPlayer()
{
	m_KeyInput.Left = false;
	m_KeyInput.Right = false;
	m_KeyInput.Up = false;
	m_KeyInput.Down = false;
	m_KeyInput.Space = false;
	m_KeyInput.Skill = false;

	BulletCount=0;
	Shield=false;
	SubWeapon = false;
	Power = false;
	SkillCount=3;
	Skillplay = false;

	playerNum = FRAMEWORK->m_ClientInfo.PlayNum;

	Speed = 5.0f;
	Size = 30;
	m_hp = 3;
	m_size = 50;
	m_PlayerBullet.reserve(1000); //미리 공간 만들어줌

}

CPlayer::~CPlayer()
{
}

void CPlayer::CheckKey()
{

	DWORD Key = INPUTMANAGER->GetKeyState();

	switch (SCENEMANAGER->GetScene())
	{
	case E_INGAME:
		//방향키 정보 전송
		if (Key&KEY_LEFT)
		{
			m_KeyInput.Left = true;

		}
		if (Key&KEY_RIGHT)
		{
			m_KeyInput.Right = true;

		}
		if (Key&KEY_UP)
		{
			m_KeyInput.Up = true;
		}
		if (Key&KEY_DOWN)
		{
			m_KeyInput.Down = true;
		}
		
		if (Key & KEY_SPACE)
		{
			m_KeyInput.Space = true;
		}
		
		if (Key & KEY_SKILL)
		{
			if (SkillCount > 0) {
				m_KeyInput.Skill = true;
				SkillCount--;
			}
		}
		break;
	}
	send(FRAMEWORK->GetSock(), (char*)&m_KeyInput, sizeof(m_KeyInput), 0);
	m_KeyInput.Left = false;
	m_KeyInput.Right = false;
	m_KeyInput.Up = false;
	m_KeyInput.Down = false;
	m_KeyInput.Space = false;
	m_KeyInput.Skill = false;
	
}

void CPlayer::SetReady(bool ready)
{
	m_IsReady = ready;
}

void CPlayer::Update()
{
	CheckKey();
	
	
}

void CPlayer::Render(HDC m_hdc)
{

}
