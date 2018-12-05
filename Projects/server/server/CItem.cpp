#include "CItem.h"



CItem::CItem()
{
}


CItem::~CItem()
{
}

CItem::CItem(ItemInfo itemInfo)
{
	MyIndex = itemInfo.Index;
	alive = true;
	m_Type = itemInfo.Type;
	m_size = 30;
	switch (m_Type)
	{
	case E_IPOWER:
		//int i = rand() % 2;
		//m_XDir = i;
		m_Pos.x = rand() % 500;
		m_Pos.y = rand() % 11 - 70;
		break;
	case E_ISHIELD:
		//int i = rand() % 2;
		//m_XDir = i;
		m_Pos.x = rand() % 500;
		m_Pos.y = rand() % 11 - 70;
		break;
	case E_ISKILL:
		//int i = rand() % 2;
		//m_XDir = i;
		m_Pos.x = rand() % 500;
		m_Pos.y = rand() % 11 - 70;
		break;
	case E_ISUB:
		//int i = rand() % 2;
		//m_XDir = i;
		m_Pos.x = rand() % 500;
		m_Pos.y = rand() % 11 - 70;
		break;
	case E_IBULLET:
		//int i = rand() % 2;
		//m_XDir = i;
		m_Pos.x = rand() % 500;
		m_Pos.y = rand() % 11 - 70;
		break;
	}

}

void CItem::SetDir(char c, bool b)
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

bool CItem::GetDir(char c) const
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
bool CItem::IsGetItem(PlayerInfo player)
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
//void CItem::ItemGet(vector<I_BULLET> I_bullet, vector<I_SUB> I_sub, vector<I_POWER> I_power, vector<I_SKILL> I_skill, vector<I_SHEILD> I_sheild)
//{
	/*for (auto p = I_power.begin(); p < I_power.end();)
	{
		if (p->IsGet(player))
		{
			if (!player.getPowerUp())
				player.setPowerUp(true);
			Ui_Score.setScore(Ui_Score.getScore() + 50);
			p = I_power.erasep;
		}
		else
			++p;
	}

	for (auto p = I_skill.begin(); p < I_skill.end();)
	{
		if (p->IsGet(player))
		{
			Ui_Score.setScore(Ui_Score.getScore() + 50);
			p = I_skill.erasep;
			if (player.getBomb() < 3)
			{
				player.setBomb(player.getBomb() + 1);
				Ui_Bomb.setNum(player.getBomb());
			}
		}
		else
			++p;
	}

	for (auto p = I_bullet.begin(); p < I_bullet.end();)
	{
		if (p->IsGet(player))
		{
			Ui_Score.setScore(Ui_Score.getScore() + 50);
			p = I_bullet.erasep;
			if (player.getBullet() < 3)
				player.setBullet(player.getBullet() + 1);
		}
		else
			++p;
	}

	for (auto p = I_sub.begin(); p < I_sub.end();)
	{
		if (p->IsGet(player))
		{
			Ui_Score.setScore(Ui_Score.getScore() + 50);
			player.setSub(true);
			p = I_sub.erasep;
		}
		else
			++p;
	}

	for (auto p = I_sheild.begin(); p < I_sheild.end();)
	{
		if (p->IsGet(player))
		{
			Ui_Score.setScore(Ui_Score.getScore() + 50);
			if (!player.getBarrier())
				player.setBarrier(true);
			p = I_sheild.erasep;
		}
		else
			++p;
	}*/
//}
void CItem::Update()
{
	switch (m_Type)
	{
	case E_IPOWER:
		//m_Pos.y += 2;
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

		break;
	case E_ISHIELD:
		
		if (this->GetXPos() + this->GetSize() > WndX)
			this->SetDir('x', false);
		else if (this->GetXPos() < 0)
			this->SetDir('x', true);

		if (this->GetYPos() + this->GetSize() > WndY)
			this->SetDir('y', false);
		else if (this->GetYPos() < 0)
			this->SetDir('y', true);

		if (this->GetDir('x'))
			this->SetXPos(this->GetXPos() + 3);
		else
			this->SetXPos(this->GetXPos() - 3);

		if (this->GetDir('y'))
			this->SetYPos(this->GetYPos() + 3);
		else
			this->SetYPos(this->GetYPos() - 3);
		//send(ClientSock, (char*)&I_sheild[i]->GetPos(), sizeof(I_sheild[i]->GetPos()), 0);
		

		break;
	case E_ISKILL:
		
		if (this->GetXPos() + this->GetSize() > WndX)
			this->SetDir('x', false);
		else if (this->GetXPos() < 0)
			this->SetDir('x', true);

		if (this->GetYPos() + this->GetSize() > WndY)
			this->SetDir('y', false);
		else if (this->GetYPos() < 0)
			this->SetDir('y', true);

		if (this->GetDir('x'))
			this->SetXPos(this->GetXPos() + 3);
		else
			this->SetXPos(this->GetXPos() - 3);

		if (this->GetDir('y'))
			this->SetYPos(this->GetYPos() + 3);
		else
			this->SetYPos(this->GetYPos() - 3);
		
		break;
	case E_ISUB:
		if (this->GetXPos() + this->GetSize() > WndX)
			this->SetDir('x', false);
		else if (this->GetXPos() < 0)
			this->SetDir('x', true);

		if (this->GetYPos() + this->GetSize() > WndY)
			this->SetDir('y', false);
		else if (this->GetYPos() < 0)
			this->SetDir('y', true);

		if (this->GetDir('x'))
			this->SetXPos(this->GetXPos() + 3);
		else
			this->SetXPos(this->GetXPos() - 3);

		if (this->GetDir('y'))
			this->SetYPos(this->GetYPos() + 3);
		else
			this->SetYPos(this->GetYPos() - 3);
		break;
	case E_IBULLET:
		
		if (this->GetXPos() + this->GetSize() > WndX)
			this->SetDir('x', false);
		else if (this->GetXPos() < 0)
			this->SetDir('x', true);

		if (this->GetYPos() + this->GetSize() > WndY)
			this->SetDir('y', false);
		else if (this->GetYPos() < 0)
			this->SetDir('y', true);

		if (this->GetDir('x'))
			this->SetXPos(this->GetXPos() + 3);
		else
			this->SetXPos(this->GetXPos() - 3);

		if (this->GetDir('y'))
			this->SetYPos(this->GetYPos() + 3);
		else
			this->SetYPos(this->GetYPos() - 3);
		
		break;
	}
}
//void CItem::Update(vector<I_BULLET> I_bullet, vector<I_SUB> I_sub, vector<I_POWER> I_power, vector<I_SKILL> I_skill, vector<I_SHEILD> I_sheild)
//{
//	for (auto p = I_power.begin(); p < I_power.end(); ++p) // 파워 아이템 이동
//	{
//		if (p->GetXPos() + p->GetSize() > WndX)
//			p->SetDir('x', false);
//		else if (p->GetXPos() < 0)
//			p->SetDir('x', true);
//
//		if (p->GetYPos() + p->GetSize() > WndY)
//			p->SetDir('y', false);
//		else if (p->GetYPos() < 0)
//			p->SetDir('y', true);
//
//		if (p->GetDir('x'))
//			p->SetXPos(p->GetXPos() + 3);
//		else
//			p->SetXPos(p->GetXPos() - 3);
//
//		if (p->GetDir('y'))
//			p->SetYPos(p->GetYPos() + 3);
//		else
//			p->SetYPos(p->GetYPos() - 3);
//	}
//	for (auto p = I_skill.begin(); p < I_skill.end(); ++p) // 필살기 아이템 이동
//	{
//		if (p->GetXPos() + p->GetSize() > WndX)
//			p->SetDir('x', false);
//		else if (p->GetXPos() < 0)
//			p->SetDir('x', true);
//
//		if (p->GetYPos() + p->GetSize() > WndY)
//			p->SetDir('y', false);
//		else if (p->GetYPos() < 0)
//			p->SetDir('y', true);
//
//		if (p->GetDir('x'))
//			p->SetXPos(p->GetXPos() + 3);
//		else
//			p->SetXPos(p->GetXPos() - 3);
//
//		if (p->GetDir('y'))
//			p->SetYPos(p->GetYPos() + 3);
//		else
//			p->SetYPos(p->GetYPos() - 3);
//	}
//
//	for (auto p = I_bullet.begin(); p < I_bullet.end(); ++p) // 총알 아이템 이동
//	{
//		if (p->GetXPos() + p->GetSize() > WndX)
//			p->SetDir('x', false);
//		else if (p->GetXPos() < 0)
//			p->SetDir('x', true);
//
//		if (p->GetYPos() + p->GetSize() > WndY)
//			p->SetDir('y', false);
//		else if (p->GetYPos() < 0)
//			p->SetDir('y', true);
//
//		if (p->GetDir('x'))
//			p->SetXPos(p->GetXPos() + 3);
//		else
//			p->SetXPos(p->GetXPos() - 3);
//
//		if (p->GetDir('y'))
//			p->SetYPos(p->GetYPos() + 3);
//		else
//			p->SetYPos(p->GetYPos() - 3);
//	}
//
//	for (auto p = I_sub.begin(); p < I_sub.end(); ++p) // 보조 아이템 이동
//	{
//		if (p->GetXPos() + p->GetSize() > WndX)
//			p->SetDir('x', false);
//		else if (p->GetXPos() < 0)
//			p->SetDir('x', true);
//
//		if (p->GetYPos() + p->GetSize() > WndY)
//			p->SetDir('y', false);
//		else if (p->GetYPos() < 0)
//			p->SetDir('y', true);
//
//		if (p->GetDir('x'))
//			p->SetXPos(p->GetXPos() + 3);
//		else
//			p->SetXPos(p->GetXPos() - 3);
//
//		if (p->GetDir('y'))
//			p->SetYPos(p->GetYPos() + 3);
//		else
//			p->SetYPos(p->GetYPos() - 3);
//	}
//
//	for (auto p = I_sheild.begin(); p < I_sheild.end(); ++p) // 방어 아이템 이동
//	{
//		if (p->GetXPos() + p->GetSize() > WndX)
//			p->SetDir('x', false);
//		else if (p->GetXPos() < 0)
//			p->SetDir('x', true);
//
//		if (p->GetYPos() + p->GetSize() > WndY)
//			p->SetDir('y', false);
//		else if (p->GetYPos() < 0)
//			p->SetDir('y', true);
//
//		if (p->GetDir('x'))
//			p->SetXPos(p->GetXPos() + 3);
//		else
//			p->SetXPos(p->GetXPos() - 3);
//
//		if (p->GetDir('y'))
//			p->SetYPos(p->GetYPos() + 3);
//		else
//			p->SetYPos(p->GetYPos() - 3);
//	}
//}