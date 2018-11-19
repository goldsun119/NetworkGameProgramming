#include "stdafx.h"
#include "CBullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(POINT pos, int typeNum)
{
	// -2 - ��ȭ�Ѿ�, -1 - ���� �Ѿ�, 0 - �÷��̾� �Ѿ�, 1 - ��1 �Ѿ� , 2 - ��2 �Ѿ� , 3 - ��3 �Ѿ�, 4 - ���� �Ѿ�

	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	
	m_Type = typeNum;
	switch (typeNum)
	{
	case 0:
	case -1:
	case -2:
		m_Pos.x += 25;
		m_size = 20;
		break;
	case 1:
		m_Pos.x += 25;
		m_size = 15;
		break;
	case 2:
		m_Pos.x += 25;
		m_Pos.y += 25;
		m_size = 20;
		break;
	case 3:
		m_Pos.x += 25;
		m_Pos.y += 150;
		m_size = 20;
		break;
	case 4:
		m_Pos.x += 25;
		m_Pos.y += 280;
		m_size = 25;
		break;
	case 5:
		m_Pos.x += 25;
		m_Pos.y += 15;
		m_size = 25;
		break;
	case 6:
		m_Pos.x += 25;
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

void CBullet::Render(HDC m_hdc)
{
}
