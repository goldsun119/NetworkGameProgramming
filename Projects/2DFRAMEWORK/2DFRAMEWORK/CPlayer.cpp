#include "stdafx.h"
#include "CPlayer.h"
#include "CGameObject.h"
#include "InputManager.h"
#include "SceneManager.h"

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

	switch (SCENEMANAGER->GetScene())
	{
	case E_INGAME:
		//방향키 정보 전송
		if (Key & KEY_LEFT)
		{
			// 11.11 
			// TODO 천기 서버가 완성된 후에 플레이어의 좌표를 바꾸는 일은 서버에서
			// AFTER 소현은 클라에서 그리는 작업만 합니다. 현재는 여기에서 좌표바꿈. 

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
	
		break;
	}
	
}

void CPlayer::Update()
{
	CheckKey();
	DWORD Key = INPUTMANAGER->GetKeyState();
	send(FRAMEWORK->GetSock(), (char*)&Key, sizeof(Key), 0);

}

void CPlayer::Render(HDC m_hdc)
{

}
