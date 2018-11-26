#include "stdafx.h"
#include "CPlayer.h"
#include "CGameObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "CBullet.h"
CPlayer::CPlayer()
{
	//Speed = 5.0f;
	//m_Pos.x = 200.0f;
	//m_Pos.y = 500.0f;
	//Size = 30;
	//m_size = 50;
	//m_PlayerBullet.reserve(1000); //�̸� ���� �������

	
	switch (FRAMEWORK->m_ClientInfo.PlayNum)
	{
	case 0:
		m_Pos.x = 100.0f;
		m_Pos.y = 500.0f;
		break;

	case 1:
		m_Pos.x = 300.0f;
		m_Pos.y = 500.0f;
		break;
	}

	Speed = 5.0f;
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
			TempPos.x = this->GetPos().x;
			TempPos.y = this->GetPos().y;
			//�Ѿ˸����
			m_PlayerBullet.emplace_back(new CBullet(TempPos, 0));

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
		(*p)->SetYPos((*p)->GetYPos() - 13);

	//ȭ�� �� �Ѿ� ����
	//for (auto p = m_PlayerBullet.begin(); p < m_PlayerBullet.end();)
	//{
	//	{

	//	}
	//	if ((*p)->GetYPos() < 250 && (*p)->GetXPos() > 270 && (*p)->GetXPos() < 350)
	//	{
	//	//if (m_PlayerBullet.size() > 2)

	//		p = m_PlayerBullet.erase(p);
	//		iter_swap(p, m_PlayerBullet.end());
	//	}
	//	else
	//		++p;
	//}

	for (int i = 0; i < m_PlayerBullet.size(); ++i)
	{
		if (m_PlayerBullet[i]->GetYPos() > WndY)
		{
			iter_swap(m_PlayerBullet[i], m_PlayerBullet.back());
			if (m_PlayerBullet.back())
			{
				delete m_PlayerBullet.back();
				m_PlayerBullet.back() = nullptr;
			}
			m_PlayerBullet.pop_back();
		}
	}
}

void CPlayer::Render(HDC m_hdc)
{

}
