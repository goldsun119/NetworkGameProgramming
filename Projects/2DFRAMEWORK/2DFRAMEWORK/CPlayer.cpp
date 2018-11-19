#include "stdafx.h"
#include "CPlayer.h"
#include "CGameObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "CBullet.h"
CPlayer::CPlayer()
{
	Speed = 3.0f;
	m_Pos.x = 200.0f;
	m_Pos.y = 500.0f;
	Size = 30;
	m_size = 50;
	m_PlayerBullet.reserve(1000); //�̸� ���� �������
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
		if (Key & KEY_SPACE)
		{
			POINT TempPos = this->GetPos();
			//��ġ����
			TempPos.x = this->GetPos().x - 40;
			TempPos.y = this->GetPos().y + 25;
			//�Ѿ˸����
			m_PlayerBullet.emplace_back(TempPos, -1);

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
	
	//�Ѿ� �̵�
	for (auto p = m_PlayerBullet.begin(); p < m_PlayerBullet.end(); ++p)
		p->SetYPos(p->GetYPos() - 13);

	//ȭ�� �� �Ѿ� ����
	for (auto p = m_PlayerBullet.begin(); p < m_PlayerBullet.end();)
	{
		if (p->GetYPos() < 250 && p->GetXPos() > 270 && p->GetXPos() < 350)
		{
			p = m_PlayerBullet.erase(p);
		}
		else
			++p;
	}
}

void CPlayer::Render(HDC m_hdc)
{

}
