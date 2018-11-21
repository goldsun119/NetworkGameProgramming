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
		m_Pos.x += 14;
		m_size = 20;
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

bool CBullet::IsCrashtoEnemy(CGameObject* enemy)
{
	RECT rt1, rt2, rt3;
	rt1.top = m_Pos.y, rt1.bottom = m_Pos.y + m_size, rt1.left = m_Pos.x, rt1.right = m_Pos.x + m_size;
	switch (enemy->GetType())
	{
	case 1:
		rt2.top = enemy->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize(), rt2.left = enemy->GetYPos(), rt2.right = enemy->GetXPos() + enemy->GetSize();
		break;
	case 2:
		rt2.top = enemy->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 50, rt2.left = enemy->GetXPos(), rt2.right = enemy->GetXPos() + enemy->GetSize();
		break;
	case 3:
		rt2.top = enemy->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 50, rt2.left = enemy->GetXPos() + 50, rt2.right = enemy->GetXPos() + enemy->GetSize() - 50;
		break;
	case 4:
		rt2.top = enemy->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 200, rt2.left = enemy->GetXPos() + 50, rt2.right = enemy->GetXPos() + enemy->GetSize() - 50;
		break;
	}

	if (IntersectRect(&rt3, &rt1, &rt2))
		return true;
	else
		return false;
}

void CBullet::Render(HDC m_hdc)
{
}
