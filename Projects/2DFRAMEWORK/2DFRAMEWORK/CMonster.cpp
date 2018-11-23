#include "stdafx.h"
#include "CMonster.h"


CMonster::CMonster()
{
	m_Pos.x = 200.0f;
	m_Pos.y = 50.0f;
	m_size = 50;
	switch (m_Type)
	{
	case E_ENEMY1:
		m_hp = 20;
		break;
	case E_ENEMY2:
		m_hp = 30;
		break;
	case E_ENEMY3:
		m_hp = 40;
		break;
	}
}
CMonster::~CMonster()
{

}

void CMonster::Update()
{

}

void CMonster::Render(HDC m_hdc)
{

}