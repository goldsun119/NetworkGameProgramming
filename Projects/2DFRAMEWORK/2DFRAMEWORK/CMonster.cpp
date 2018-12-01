#include "stdafx.h"
#include "CMonster.h"
#include "Framework.h"

CMonster::CMonster()
{
	m_size = 70;
	alive = false;
	//m_Pos.x = 200.0f;
	//m_Pos.y = 50.0f;
	//m_size = 50;
	//switch (m_Type)
	//{
	//case E_ENEMY1:
	//	m_hp = 20;
	//	break;
	//case E_ENEMY2:
	//	m_hp = 30;
	//	break;
	//case E_ENEMY3:
	//	m_hp = 40;
	//	break;
	//}
}
CMonster::CMonster(E_OBJECT typeNum)
{
	m_Type = typeNum;
	alive = false;
	switch (m_Type)
	{
	case E_ENEMY1:
		//m_Pos.x = 200.0f;
		//m_Pos.y = 50.0f;
		m_size = 50;
		m_hp = 20;
		break;
	case E_ENEMY2:
		//m_Pos.x = 220.0f;
		//m_Pos.y = 100.0f;
		m_size = 70;
		m_hp = 30;
		break;
	case E_ENEMY3:
		//m_Pos.x = 150.0f;
		//m_Pos.y = 150.0f;
		m_size = 90;
		m_hp = 40;
		break;
	case E_BOSS1:
	//	m_Pos.x = 150.0f;
	//	m_Pos.y = 150.0f;
		m_size = 100;
		m_hp = 70;
		break;
	case E_BOSS2:
	//	m_Pos.x = 150.0f;
	//	m_Pos.y = 150.0f;
		m_size = 150;
		m_hp = 100;
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