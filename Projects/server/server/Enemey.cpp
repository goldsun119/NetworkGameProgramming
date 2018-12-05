#include "Enemy.h"

CMonster::CMonster()
{
	//m_Pos.x = 200.0f;
	//m_Pos.y = 50.0f;
	//m_size = 50;
	//switch (m_Type)
	//{
	//case E_ENEMY1:
	//	Pos.x = rand() % 500;
	//	Pos.y = -70;
	//	m_hp = 20;
	//	break;
	//case E_ENEMY2:
	//	Pos.x = rand() % 500;
	//	Pos.y = -70;
	//	m_hp = 30;
	//	break;
	//case E_ENEMY3:
	//	m_hp = 40;
	//	break;
	//}
}
CMonster::CMonster(EnemyInfo enemyInfo)
{

	
	m_Type = enemyInfo.Type;
	MyIndex = enemyInfo.Index;
	alive = true;
	switch (m_Type)
	{
	case E_ENEMY1:
		m_Pos.x = rand() % 500;
		m_Pos.y = -20;
		/*for(int i = 0;i<50;++i)
			m_MonsterBullet.emplace_back(this->m_Pos, 1);*/
		//printf("x: %d, y: %d", m_Pos.x, m_Pos.y);
		m_size = 45;
		m_hp = 20;
		break;
	case E_ENEMY2:
		m_Pos.x = rand() % 500;
		m_Pos.y = -20;
		m_size = 70;
		m_hp = 30;
		//m_MonsterBullet.emplace_back(CBullet(m_Pos, ));;

		break;
	case E_ENEMY3:
		m_Pos.x = 220;
		m_Pos.y = -190;
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
		m_Pos.y += 1;
		/*if (this->alive)
		{
			enemy_bullet1.emplace_back(CBullet(this->GetPos(), 1));
		}*/
		//for (int i = 0; i < m_MonsterBullet.size(); ++i)
		//{
		//	m_MonsterBullet[i].SetYPos(this->GetYPos() + 2);
		//	//printf("y:%d\n", m_MonsterBullet[i].GetYPos());
		//}
		//printf("y:%d", m_Pos.y);
		break;
	case E_ENEMY2:
		m_Pos.y += 1;
		//printf("y:%d", m_Pos.y);
		break;
	case E_ENEMY3:
		m_Pos.y += 1;
		//printf("y:%d", m_Pos.y);
		break;
	case E_BOSS1:
		m_Pos.y += 1;
		//printf("y:%d", m_Pos.y);
		break;
	case E_BOSS2:
		m_Pos.y += 1;
		//printf("y:%d", m_Pos.y);
		break;
	}
	//몬스터1 총알 이동
	for (int i = 0; i < enemy_bullet1.size(); ++i)
	{
		enemy_bullet1[i].SetYPos(enemy_bullet1[i].GetYPos()-5);
		printf("y:%d\n", enemy_bullet1[i].GetYPos() - 5);
	}
}

