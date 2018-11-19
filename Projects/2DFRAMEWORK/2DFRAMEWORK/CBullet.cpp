#include "stdafx.h"
#include "CBullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(POINT pos, int typeNum)
{
	// -2 - °­È­ÃÑ¾Ë, -1 - º¸Á¶ ÃÑ¾Ë, 0 - ÇÃ·¹ÀÌ¾î ÃÑ¾Ë, 1 - Àû1 ÃÑ¾Ë , 2 - Àû2 ÃÑ¾Ë , 3 - Àû3 ÃÑ¾Ë, 4 - º¸½º ÃÑ¾Ë

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
