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

	playerNum = FRAMEWORK->m_ClientInfo.PlayNum;

	Speed = 5.0f;
	Size = 30;
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

			POINT TempPos = this->GetPos();
			//위치지정
			TempPos.x = this->GetPos().x;
			TempPos.y = this->GetPos().y;
			//총알만들기
			m_PlayerBullet.emplace_back(new CBullet(TempPos, 0));

		}
		break;
	}
	send(FRAMEWORK->GetSock(), (char*)&m_KeyInput, sizeof(m_KeyInput), 0);
	m_KeyInput.Left = false;
	m_KeyInput.Right = false;
	m_KeyInput.Up = false;
	m_KeyInput.Down = false;
	m_KeyInput.Space = false;
	
}

void CPlayer::SetReady(bool ready)
{
	m_IsReady = ready;
}

void CPlayer::Update()
{
	CheckKey();
	
	//총알 이동
	//for (auto p = m_PlayerBullet.begin(); p < m_PlayerBullet.end(); ++p)
	//	(*p)->SetYPos((*p)->GetYPos() - 13);

	//화면 밖 총알 삭제
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
