#include "Enemy.h"

CMonster::CMonster()
{
	m_Pos.x = 200.0f;
	m_Pos.y = 50.0f;
	m_size = 50;
	switch (m_Type)
	{
	case E_ENEMY1:
		Pos.x = rand() % 500;
		Pos.y = -70;
		m_hp = 20;
		break;
	case E_ENEMY2:
		Pos.x = rand() % 500;
		Pos.y = -70;
		m_hp = 30;
		break;
	case E_ENEMY3:
		m_hp = 40;
		break;
	}
}
CMonster::CMonster(E_OBJECT typeNum)
{
	m_Type = typeNum;

	switch (m_Type)
	{
	case E_ENEMY1:
		Pos.x = rand() % 500;
		Pos.y = -70;

		//printf("x: %d, y: %d", m_Pos.x, m_Pos.y);
		m_size = 45;
		m_hp = 20;
		break;
	case E_ENEMY2:
		Pos.x = rand() % 500;
		Pos.y = -70;
		m_size = 70;
		m_hp = 30;
		break;
	case E_ENEMY3:
		Pos.x = 220;
		Pos.y = -190;
		m_size = 200;
		m_hp = 40;
		break;
	case E_BOSS1:
		m_Pos.x = 150.0f;
		m_Pos.y = 50.0f;
		m_size = 100;
		m_hp = 70;
		break;
	case E_BOSS2:
		m_Pos.x = 150.0f;
		m_Pos.y = 0.0f;
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
	switch (m_Type)
	{
	case E_ENEMY1:
		m_Pos.y += 2;
		//printf("y:%d", m_Pos.y);
		break;
	case E_ENEMY2:
		m_Pos.y += 3;
		//printf("y:%d", m_Pos.y);
		break;
	case E_ENEMY3:
		m_Pos.y += 4;
		//printf("y:%d", m_Pos.y);
		break;
	case E_BOSS1:
		m_Pos.y += 5;
		//printf("y:%d", m_Pos.y);
		break;
	case E_BOSS2:
		m_Pos.y += 6;
		//printf("y:%d", m_Pos.y);
		break;
	}
}

