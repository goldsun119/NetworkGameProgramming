#include "Enemy.h"

CMonster::CMonster()
{
	//m_Pos.x = 200.0f;
	//m_Pos.y = 50.0f;
	//m_size = 50;
	//switch (m_Type)
	//{
	//case E_ENEMY1:
	//   Pos.x = rand() % 500;
	//   Pos.y = -70;
	//   m_hp = 20;
	//   break;
	//case E_ENEMY2:
	//   Pos.x = rand() % 500;
	//   Pos.y = -70;
	//   m_hp = 30;
	//   break;
	//case E_ENEMY3:
	//   m_hp = 40;
	//   break;
	//}
}
CMonster::CMonster(EnemyInfo enemyInfo)
{
	m_EnemyBullet.reserve(55);

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
	for (int i = 0; i < 50; ++i)
	{
		m_EnemyBullet.emplace_back(m_Pos, 0);
	}
}
CMonster::~CMonster()
{

}

void CMonster::SetDir(char c, bool b)
{
	switch (c) {
	case 'x':
		m_XDir = b;
		break;
	case 'y':
		m_YDir = b;
		break;
	}
}

bool CMonster::GetDir(char c) const
{
	switch (c)
	{
	case 'x':
		return m_XDir;
		break;
	case 'y':
		return m_YDir;
		break;
	}
}

void CMonster::Update()
{
	switch (m_Type)
	{
	case E_ENEMY1:
		m_Pos.y += 1;
		for (int i = 0; i < m_EnemyBullet.size(); ++i)
		{
			if (this->alive)
			{
				m_EnemyBullet[i].SetYPos(GetYPos() + 10);
			}
		}
		//printf("y:%d", m_Pos.y);
		break;
	case E_ENEMY2:
		m_Pos.y += 2;
		for (int i = 0; i < m_EnemyBullet.size(); ++i)
		{
			if (this->alive)
			{
				m_EnemyBullet[i].SetYPos(this->GetYPos() + 2);
			}
		}
		//printf("y:%d", m_Pos.y);
		break;
	case E_ENEMY3:
		m_Pos.x += 1;
		(m_Pos.x > WndX) ? m_Pos.x -= 1 : m_Pos.x += 1;
		(m_Pos.x < WndX) ? m_Pos.x += 1 : m_Pos.x -= 1;

		m_Pos.y += 1;
		for (int i = 0; i < m_EnemyBullet.size(); ++i)
		{
			if (this->alive)
			{
				m_EnemyBullet[i].SetYPos(this->GetYPos() + 2);
			}
		}
		//printf("y:%d", m_Pos.y);
		break;
	case E_BOSS1:
		if (!Boss1_Stop)
			m_Pos.y += 1;
		if (m_Pos.y > 40 && Boss1_Stop == false)
		{
			Boss1_Stop = true;

		}

		if (Boss1_Stop == true)
		{
			for (int i = 0; i < m_EnemyBullet.size(); ++i)
			{
				if (this->alive)
				{
					if (this->GetXPos() + this->GetSize() > WndX)
						this->SetDir('x', false);
					else if (this->GetXPos() < 0)
						this->SetDir('x', true);

					if (this->GetYPos() + this->GetSize() > WndY)
						this->SetDir('y', false);
					else if (this->GetYPos() < 0)
						this->SetDir('y', true);

					if (this->GetDir('x'))
					{
						this->SetXPos(this->GetXPos() + 3);
						//printf("아이템의 x좌표: %d\n", I_power[i]->GetPos());
					}
					else
						this->SetXPos(this->GetXPos() - 3);

					if (this->GetDir('y'))
						this->SetYPos(this->GetYPos() + 3);
					else
						this->SetYPos(this->GetYPos() - 3);
				}
			}
		}

		for (int i = 0; i < m_EnemyBullet.size(); ++i)
		{
			if (this->alive)
			{
				m_EnemyBullet[i].SetYPos(this->GetYPos() + 2);
			}
		}
		//printf("y:%d", m_Pos.y);
		break;
	case E_BOSS2:
		if (!Boss2_Stop)
			m_Pos.y += 1;
		if (m_Pos.y > 40 && Boss2_Stop == false)
		{
			Boss2_Stop = true;
		}
		if (Boss2_Stop == true)
		{
			for (int i = 0; i < m_EnemyBullet.size(); ++i)
			{
				if (this->alive)
				{
					if (this->GetXPos() + this->GetSize() > WndX)
						this->SetDir('x', false);
					else if (this->GetXPos() < 0)
						this->SetDir('x', true);

					if (this->GetYPos() + this->GetSize() > WndY)
						this->SetDir('y', false);
					else if (this->GetYPos() < 0)
						this->SetDir('y', true);

					if (this->GetDir('x'))
					{
						this->SetXPos(this->GetXPos() + 3);
						//printf("아이템의 x좌표: %d\n", I_power[i]->GetPos());
					}
					else
						this->SetXPos(this->GetXPos() - 3);

					if (this->GetDir('y'))
						this->SetYPos(this->GetYPos() + 3);
					else
						this->SetYPos(this->GetYPos() - 3);
				}
			}
		}
		for (int i = 0; i < m_EnemyBullet.size(); ++i)
		{
			if (this->alive)
			{
				m_EnemyBullet[i].SetYPos(this->GetYPos() + 2);
			}
		}
		//printf("y:%d", m_Pos.y);
		break;
	}

}
