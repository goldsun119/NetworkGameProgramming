#include "stdafx.h"
#include "CItem.h"



CItem::CItem()
{
}


CItem::~CItem()
{
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
void CItem::ItemGet(vector<I_BULLET> I_bullet, vector<I_SUB> I_sub, vector<I_POWER> I_power, vector<I_SKILL> I_skill, vector<I_SHEILD> I_sheild)
{
	/*for (auto p = I_power.begin(); p < I_power.end();)
	{
		if (p->IsGet(player))
		{
			if (!player.getPowerUp())
				player.setPowerUp(true);
			Ui_Score.setScore(Ui_Score.getScore() + 50);
			p = I_power.erase(p);
		}
		else
			++p;
	}

	for (auto p = I_skill.begin(); p < I_skill.end();)
	{
		if (p->IsGet(player))
		{
			Ui_Score.setScore(Ui_Score.getScore() + 50);
			p = I_skill.erase(p);
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
			p = I_bullet.erase(p);
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
			p = I_sub.erase(p);
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
			p = I_sheild.erase(p);
		}
		else
			++p;
	}*/
}
void CItem::Update()
{
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

I_BULLET::I_BULLET()
{
	
}

void I_BULLET::Update()
{
}

I_SUB::I_SUB()
{

}

I_POWER::I_POWER()
{

}

I_SKILL::I_SKILL()
{

}

I_SHEILD::I_SHEILD()
{

}
