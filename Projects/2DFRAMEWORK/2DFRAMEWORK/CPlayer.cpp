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
		//����Ű ���� ����
		if (Key & KEY_LEFT)
		{
			// 11.11 
			// TODO õ�� ������ �ϼ��� �Ŀ� �÷��̾��� ��ǥ�� �ٲٴ� ���� ��������
			// AFTER ������ Ŭ�󿡼� �׸��� �۾��� �մϴ�. ����� ���⿡�� ��ǥ�ٲ�. 
			// 11.12 
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
	send(FRAMEWORK->GetSock(), (char*)&Key, sizeof(Key), 0);

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
