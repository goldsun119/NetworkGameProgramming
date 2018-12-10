#include "stdafx.h"
#include "CBullet.h"
#include "MyPacket.h"

CBullet::CBullet()
{
	m_size = 20;
}

CBullet::CBullet(POINT pos, int typeNum)
{
	// -2 - ��ȭ�Ѿ�, -1 - ���� �Ѿ�, 0 - �÷��̾� �Ѿ�, 1 - ��1 �Ѿ� , 2 - ��2 �Ѿ� , 3 - ��3 �Ѿ�, 4 - ���� �Ѿ�
	
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	m_hp = 10;
	m_Type = typeNum;
	//m_Count += 1;
	switch (typeNum)
	{
	case 0:
	case -1:
	case -2:
		alive = true;
		m_Pos.x += 18;
		m_size = 10;
		break;
	case 1:
		m_Pos.x += 15;
		m_size = 15;
		break;
	case 2:
		m_Pos.x += 63;
		m_Pos.y += 25;
		m_size = 20;
		break;
	case 3:
		m_Pos.x += 91;
		m_Pos.y += 150;
		m_size = 20;
		break;
	case 4:
		m_Pos.x += 285;
		m_Pos.y += 280;
		m_size = 25;
		break;
	case 5:
		m_Pos.x += 0;
		m_Pos.y += 15;
		m_size = 25;
		break;
	case 6:
		m_Pos.x += 270;
		m_Pos.y += 280;
		m_size = 50;
		break;
	case 7:
		m_Pos.x += 145;
		m_Pos.y += 130;
		m_size = 20;
		break;
	}
	
}


CBullet::~CBullet()
{
}

bool CBullet::IsCrashtoEnemy(CGameObject enemy)
{
	RECT rt1, rt2, rt3;
	rt1.top = m_Pos.y, rt1.bottom = m_Pos.y + m_size, rt1.left = m_Pos.x, rt1.right = m_Pos.x + m_size;
	switch (enemy.GetType())
	{
	case 1:
		rt2.top = enemy.GetYPos(), rt2.bottom = enemy.GetYPos() + enemy.GetSize(), rt2.left = enemy.GetXPos(), rt2.right = enemy.GetXPos() + enemy.GetSize();
		break;
	case 2:
		rt2.top = enemy.GetYPos(), rt2.bottom = enemy.GetYPos() + enemy.GetSize(), rt2.left = enemy.GetXPos(), rt2.right = enemy.GetXPos() + enemy.GetSize();
		break;
	case 3:
		rt2.top = enemy.GetYPos(), rt2.bottom = enemy.GetYPos() + enemy.GetSize(), rt2.left = enemy.GetXPos(), rt2.right = enemy.GetXPos() + enemy.GetSize();
		break;
	case 4:
		rt2.top = enemy.GetYPos(), rt2.bottom = enemy.GetYPos() + enemy.GetSize(), rt2.left = enemy.GetXPos(), rt2.right = enemy.GetXPos() + enemy.GetSize();
		break;
	}

	if (IntersectRect(&rt3, &rt1, &rt2))
		return true;
	else
		return false;
}

void CBullet::Update()
{
	
}

bool CBullet::IsShootPlayer(PlayerInfo player)
{
	RECT rt1, rt2, rt3;
	rt1.top = m_Pos.y;
	rt1.bottom = m_Pos.y + m_size;
	rt1.left = m_Pos.x;
	rt1.right = m_Pos.x + m_size;

	rt2.top = player.Pos.y;
	rt2.bottom = player.Pos.y + 50;
	rt2.left = player.Pos.x;
	rt2.right = player.Pos.x + 50;

	if (IntersectRect(&rt3, &rt1, &rt2))
		return true;
	else
		return false;
}

