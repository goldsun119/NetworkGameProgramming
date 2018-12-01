#include "stdafx.h"
#include "CMyInGame.h"
#include "CObjectManager.h"
#include "TimerManager.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CBullet.h"
#include "CItem.h"
#include "TimerManager.h"
#include "Framework.h"

#define g_makeEnemy1 300
#define g_makeEnemy2 400
#define g_makeEnemy3 5000
#define g_makeBoss1 61000
#define g_makeBoss2 91000

#define g_makeItem1 39000
#define g_makeBullet 4000
#define g_makePower 5000
#define g_makeSkill 61000
#define g_makeSub 40000

#define g_makeShield 91000

CMyInGame::CMyInGame()
{
	m_Monster.reserve(MAXOBJECTNUM);
	I_sub.reserve(MAXITEMNUM);
	I_bullet.reserve(MAXITEMNUM);
	I_skill.reserve(MAXITEMNUM);
	I_power.reserve(MAXITEMNUM);
	I_sheild.reserve(MAXITEMNUM);

	for (int i = 0; i < 1000; ++i) {
		m_Monster.emplace_back(new CMonster());
	}

	//m_pPlayer = new CPlayer;
	//Player *m_pPlayer = NULL;
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngameBackGroundImage", *MYRENDERMANAGER->FindCImage("IngameBackGroundImage")));
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngamePlayerImage", *MYRENDERMANAGER->FindCImage("IngamePlayerImage")));


	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("ItemBullet", *MYRENDERMANAGER->FindCImage("ItemBullet")));
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("ItemShield", *MYRENDERMANAGER->FindCImage("ItemShield")));
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("ItemUlt", *MYRENDERMANAGER->FindCImage("ItemUlt")));
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("ItemSub", *MYRENDERMANAGER->FindCImage("ItemSub")));
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("ItemPower", *MYRENDERMANAGER->FindCImage("ItemPower")));

	m_ItemBullet.Load(TEXT("image/ITEM(총알).png"));
	m_BItemShield.Load(TEXT("image/ITEM(방어막).png"));
	m_ItemPower.Load(TEXT("image/강화총알.png"));
	m_ItemSub.Load(TEXT("image/ITEM(보조).png"));
	m_ItemUlt.Load(TEXT("image/ITEM(필살기).png"));
	
	//m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("PlayerDefaultBulletImage", *MYRENDERMANAGER->FindCImage("PlayerDefaultBulletImage")));
	
	//왜 렌더매니저 안써줌 ㅠ
	if (FRAMEWORK->m_ClientInfo.PlayNum == 0) {
		m_PlayerImg.Load(TEXT("Player1.png"));
		m_2PlayerImg.Load(TEXT("image/player2.png"));
	}
	if (FRAMEWORK->m_ClientInfo.PlayNum == 1) {
		m_PlayerImg.Load(TEXT("image/player2.png"));
		m_2PlayerImg.Load(TEXT("Player1.png"));
	}

	m_PlayerBulletImg.Load(TEXT("image/총알기본.png"));
	m_MonsterImg1.Load(TEXT("enemy1.png"));
	m_MonsterImg2.Load(TEXT("enemy2.png"));
	m_MonsterImg3.Load(TEXT("enemy3.png"));
	m_BossImg1.Load(TEXT("boss1-1.png"));
	m_BossImg2.Load(TEXT("boss2.png"));

}


CMyInGame::~CMyInGame()
{
	m_PlayerImg.Destroy();
	m_2PlayerImg.Destroy();
	m_MonsterImg1.Destroy();
	m_MonsterImg2.Destroy();
	m_MonsterImg3.Destroy();
	m_BossImg1.Destroy();
	m_BossImg2.Destroy();
	m_PlayerBulletImg.Destroy();
}

void CMyInGame::Render(HDC hdc)
{

	int size = 50;

	//m_PlayerImg = MYRENDERMANAGER->FindCImage("IngamePlayerImage")->begin()->GetCimage();
	PAINTSTRUCT ps;
	BeginPaint(g_hWnd, &ps);
	{
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, m_nWndClientWidth, m_nWndClientHeight);
		SelectObject(memDC, memBit);
		StretchBlt(memDC, 0, 0, 403, 599, m_IngameImageMap["IngameBackGroundImage"].begin()->GetCimage()->GetDC(), 0, 0, 360, 600, SRCCOPY);
		
		
		m_PlayerImg.Draw(memDC, m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetSize(), m_pPlayer->GetSize());
		
		
		
		m_2PlayerImg.Draw(memDC, m_p2Player->GetPos().x, m_p2Player->GetPos().y, m_p2Player->GetSize(), m_p2Player->GetSize());

	
		//몬스터 그리기
		for (vector<CMonster*>::iterator iter = m_Monster.begin();
			iter != m_Monster.end(); ++iter)
		{	
			if ((*iter)->getAlive() == true) {
				if ((*iter)->GetHp() > 0)
				{
					if ((*iter)->GetType() == E_ENEMY1)
						m_MonsterImg1.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
					if ((*iter)->GetType() == E_ENEMY2)
						m_MonsterImg2.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
					if ((*iter)->GetType() == E_ENEMY3)
						m_MonsterImg3.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
					if ((*iter)->GetType() == E_BOSS1)
						m_BossImg1.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
					if ((*iter)->GetType() == E_BOSS2)
						m_BossImg2.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
				}
			}

		}

		//아이템 - 총알
		for (vector<I_BULLET*>::iterator iter = m_Ibullet.begin();
			iter != m_Ibullet.end(); ++iter)
		{
			m_ItemBullet.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}
		//아이템 - 방어막
		for (vector<I_SHEILD*>::iterator iter = m_Isheild.begin();
			iter != m_Isheild.end(); ++iter)
		{
			m_BItemShield.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}
		//아이템 - 궁아이템획득
		for (vector<I_SKILL*>::iterator iter = m_Iskill.begin();
			iter != m_Iskill.end(); ++iter)
		{
			m_ItemUlt.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}
		//아이템 - 보조
		for (vector<I_SUB*>::iterator iter = m_Isub.begin();
			iter != m_Isub.end(); ++iter)
		{
			m_ItemSub.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}
		//아이템 - 강화
		for (vector<I_POWER*>::iterator iter = I_power.begin();
			iter != I_power.end(); ++iter)
		{
			m_ItemPower.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}

		//플레이어 총알 그리기
		vector<CBullet*>::iterator iter = m_pPlayer->m_PlayerBullet.begin();
		while (iter != m_pPlayer->m_PlayerBullet.end())
		{
			m_PlayerBulletImg.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
			iter++;
		}

		BitBlt(hdc, 0, 0, 403, 599, memDC, 0, 0, SRCCOPY);
		DeleteObject(memBit);
		DeleteDC(memDC);
	}
	EndPaint(g_hWnd, &ps);
	

}

void CMyInGame::Update()
{
	m_pPlayer->Update();

	//좌표값 설정
	recv(FRAMEWORK->GetSock(), (char*)&playerInfo[0], sizeof(playerInfo[0]), 0);
	recv(FRAMEWORK->GetSock(), (char*)&playerInfo[1], sizeof(playerInfo[1]), 0);
	
	//ItemRecv();

	switch (FRAMEWORK->m_ClientInfo.PlayNum)
	{
	case 0:
		m_pPlayer->SetPos(playerInfo[0].Pos.x, playerInfo[0].Pos.y);
		m_p2Player->SetPos(playerInfo[1].Pos.x, playerInfo[1].Pos.y);
		break;
	case 1:
		m_pPlayer->SetPos(playerInfo[1].Pos.x, playerInfo[1].Pos.y);
		m_p2Player->SetPos(playerInfo[0].Pos.x, playerInfo[0].Pos.y);
		break;
	}
	MakeEnemys();
	//MakeItem();
	//for (vector<CMonster*>::iterator iter = m_Monster.begin();
	//	iter != m_Monster.end(); ++iter)
	//{
	//	FRAMEWORK->recvn(FRAMEWORK->GetSock(), (char*)&enemyInfo.pos, sizeof(enemyInfo.pos), 0);
	//	(*iter)->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
	//}
	/*for (vector<CMonster*>::iterator iter = m_Monster.begin();
		iter != m_Monster.end(); ++iter)
	{
		FRAMEWORK->recvn(FRAMEWORK->GetSock(), (char*)&enemyInfo.pos, sizeof(enemyInfo.pos), 0);
		(*iter)->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
	}*/

	//for (int i = 0; i < I_power.size(); ++i)
	//{
	//	recv(FRAMEWORK->GetSock(), (char*)&tempXY, sizeof(tempXY), 0);
	//	I_power[i]->SetPoint(tempXY);
	//}

	//for (int i = 0; i < I_skill.size(); ++i) // 필살기 아이템 이동
	//{
	//	recv(FRAMEWORK->GetSock(), (char*)&tempXY, sizeof(tempXY), 0);
	//	I_skill[i]->SetPoint(tempXY);
	//}

	//for (int i = 0; i < I_bullet.size(); ++i) // 총알 아이템 이동
	//{
	//	recv(FRAMEWORK->GetSock(), (char*)&tempXY, sizeof(tempXY), 0);
	//	I_bullet[i]->SetPoint(tempXY);
	//}

	//for (int i = 0; i < I_sub.size(); ++i)
	//{
	//	recv(FRAMEWORK->GetSock(), (char*)&tempXY, sizeof(tempXY), 0);
	//	I_sub[i]->SetPoint(tempXY);
	//}

	//for (int i = 0; i < I_sheild.size(); ++i) // 방어 아이템 이동
	//{
	//	recv(FRAMEWORK->GetSock(), (char*)&tempXY, sizeof(tempXY), 0);
	//	I_power[i]->SetPoint(tempXY);
	//}
	//sendAllIngamePack();
	//적 비행기 생성

	// 문제인부분이 
	//적 이동
	//if (m_Monster.size() > 0)
	//{
	//	for (int i = 0; i < m_Monster.size(); ++i)
	//	{
	//		
	//			if (m_Monster[i]->GetYPos() < WndY)
	//			{
	//				몬스터 이동
	//				if (m_Monster[i]->GetType() == E_ENEMY1)
	//				{
	//					m_Monster[i]->SetYPos(m_Monster[i]->GetYPos() + 2);
	//				}
	//				else
	//				{
	//					m_Monster[i]->SetYPos(m_Monster[i]->GetYPos() + 3);

	//				}

	//				for (auto bullet = m_pPlayer->m_PlayerBullet.begin(); bullet < m_pPlayer->m_PlayerBullet.end(); ++bullet)
	//				{
	//					if ((*bullet)->GetActive())
	//					{

	//						RECT rt1, rt2, rt3;
	//						rt1.top = (*bullet)->GetYPos(), rt1.bottom = (*bullet)->GetYPos() + (*bullet)->GetSize(), rt1.left = (*bullet)->GetXPos(), rt1.right = (*bullet)->GetXPos() + (*bullet)->GetSize();
	//						
	//						switch (m_Monster[i]->GetType())
	//						{
	//						case E_ENEMY1:
	//							rt2.top = m_Monster[i]->GetYPos(), rt2.bottom = m_Monster[i]->GetYPos() + m_Monster[i]->GetSize(), rt2.left = m_Monster[i]->GetYPos(), rt2.right = m_Monster[i]->GetXPos() + m_Monster[i]->GetSize();
	//							
	//							break;
	//						case E_ENEMY2:
	//							rt2.top = m_Monster[i]->GetYPos(), rt2.bottom = m_Monster[i]->GetYPos() + (*iter)->GetSize(), rt2.left = (*iter)->GetYPos(), rt2.right = (*iter)->GetXPos() + (*iter)->GetSize();
	//							rt2.top = m_Monster[i]->GetYPos(), rt2.bottom = m_Monster[i]->GetYPos() + m_Monster[i]->GetSize(), rt2.left = m_Monster[i]->GetYPos(), rt2.right = m_Monster[i]->GetXPos() + m_Monster[i]->GetSize();

	//							rt2.top = (*iter)->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 50, rt2.left = enemy->GetXPos(), rt2.right = enemy->GetXPos() + enemy->GetSize();
	//							break;
	//						case E_ENEMY3:
	//							rt2.top = m_Monster[i]->GetYPos(), rt2.bottom = m_Monster[i]->GetYPos() + m_Monster[i]->GetSize() - m_Monster[i]->GetSize() / 2, rt2.left = m_Monster[i]->GetYPos(), rt2.right = m_Monster[i]->GetXPos() + m_Monster[i]->GetSize();

	//							rt2.top = (*iter)->GetYPos(), rt2.bottom = (*iter)->GetYPos() + (*iter)->GetSize() - 50, rt2.left = (*iter)->GetYPos(), rt2.right = (*iter)->GetXPos() + (*iter)->GetSize();

	//							rt2.top = (*iter)->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 50, rt2.left = enemy->GetXPos() + 50, rt2.right = enemy->GetXPos() + enemy->GetSize() - 50;
	//							break;
	//						case E_BOSS1:
	//						case E_BOSS2:
	//							rt2.top = m_Monster[i]->GetYPos(), rt2.bottom = m_Monster[i]->GetYPos() + m_Monster[i]->GetSize() - m_Monster[i]->GetSize()/ 2, rt2.left = m_Monster[i]->GetYPos(), rt2.right = m_Monster[i]->GetXPos() + m_Monster[i]->GetSize();

	//							rt2.top = (*iter)->GetYPos(), rt2.bottom = (*iter)->GetYPos() + (*iter)->GetSize() - 200, rt2.left = (*iter)->GetYPos(), rt2.right = (*iter)->GetXPos() + (*iter)->GetSize();

	//							rt2.top = (*iter)->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 200, rt2.left = enemy->GetXPos() + 50, rt2.right = enemy->GetXPos() + enemy->GetSize() - 50;
	//							break;
	//						}

	//						if (IntersectRect(&rt3, &rt1, &rt2))
	//						{
	//							m_Monster[i]->SetHp(m_Monster[i]->GetHp() - 10);
	//							(*bullet)->SetActive(false);
	//						}
	//					
	//					}
	//				}



	//			}
	//			 몬스터 삭제
	//			if (m_Monster[i]->GetYPos() > WndY)
	//			{
	//				iter_swap(m_Monster[i], m_Monster.back());
	//			if (m_Monster.back())
	//			{
	//				delete m_Monster.back();
	//				m_Monster.back() = nullptr;
	//			}
	//			m_Monster.pop_back();
	//			}

	//	}

	//}
	//for (auto iter = m_Monster.begin(); iter != m_Monster.end(); ++iter)
	//{
	//	if ((*iter)->GetYPos() < WndY)
	//	{
	//		if ((*iter)->GetType() == E_ENEMY1)
	//		{
	//			(*iter)->SetYPos((*iter)->GetYPos() + 2);
	//		}
	//		else
	//		{
	//			(*iter)->SetYPos((*iter)->GetYPos() + 3);

	//		}

	//		for (auto bullet = m_pPlayer->m_PlayerBullet.begin(); bullet < m_pPlayer->m_PlayerBullet.end(); ++bullet)
	//		{
	//			if ((*bullet)->GetActive())
	//			{

	//			RECT rt1, rt2, rt3;
	//			rt1.top = (*bullet)->GetYPos(), rt1.bottom = (*bullet)->GetYPos() + (*bullet)->GetSize(), rt1.left = (*bullet)->GetXPos(), rt1.right = (*bullet)->GetXPos() + (*bullet)->GetSize();
	//			switch ((*iter)->GetType())
	//			{
	//			case 1:
	//				rt2.top = (*iter)->GetYPos(), rt2.bottom = (*iter)->GetYPos() + (*iter)->GetSize(), rt2.left = (*iter)->GetYPos(), rt2.right = (*iter)->GetXPos() + (*iter)->GetSize();
	//				break;
	//			case 2:
	//				rt2.top = (*iter)->GetYPos(), rt2.bottom = (*iter)->GetYPos() + (*iter)->GetSize(), rt2.left = (*iter)->GetYPos(), rt2.right = (*iter)->GetXPos() + (*iter)->GetSize();

	//				//rt2.top = (*iter)->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 50, rt2.left = enemy->GetXPos(), rt2.right = enemy->GetXPos() + enemy->GetSize();
	//				break;
	//			case 3:
	//				rt2.top = (*iter)->GetYPos(), rt2.bottom = (*iter)->GetYPos() + (*iter)->GetSize() - 50, rt2.left = (*iter)->GetYPos(), rt2.right = (*iter)->GetXPos() + (*iter)->GetSize();

	//				//rt2.top = (*iter)->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 50, rt2.left = enemy->GetXPos() + 50, rt2.right = enemy->GetXPos() + enemy->GetSize() - 50;
	//				break;
	//			case 4:
	//				rt2.top = (*iter)->GetYPos(), rt2.bottom = (*iter)->GetYPos() + (*iter)->GetSize() - 200, rt2.left = (*iter)->GetYPos(), rt2.right = (*iter)->GetXPos() + (*iter)->GetSize();

	//				//rt2.top = (*iter)->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 200, rt2.left = enemy->GetXPos() + 50, rt2.right = enemy->GetXPos() + enemy->GetSize() - 50;
	//				break;
	//			}

	//			if (IntersectRect(&rt3, &rt1, &rt2))
	//			{
	//				(*iter)->SetHp((*iter)->GetHp() - 10);
	//				(*bullet)->SetActive(false);
	//			}
	//			}
	//		}


	//	
	//	}

		//else if((*iter)->GetYPos()> WndY)
		//	//yPos가 윈도우 창크기보다 크면
		//{
		//	//벡터 지워라.
		//	//swap쓰면 되는데 왜 접근안되냐 아오
		//	if (m_Monster.size() > 1 )
		//	{

		//		iter_swap((*iter), m_Monster.back());
		//		if (m_Monster.back())
		//		{
		//			delete m_Monster.back();
		//			m_Monster.back() = nullptr;
		//		}
		//		m_Monster.pop_back();

		//	}
		//	else {
		//		//두개 이하면
		//		m_Monster.erase(m_Monster.begin());
		//		m_Monster.clear();
		//		return;

		//	}
		//	//swap()
		//	//iter_e
		//	//m_Monster.erase(iter); //이건 또 왜안돼
		//}
	
	
}
	
	//OBJECTMANAGER->CheckEnemybyPlayerBulletCollision(m_pPlayer->m_PlayerBullet, ObjList);

void CMyInGame::sendAllIngamePack() //인게임 아이템
{
	recv(FRAMEWORK->GetSock(), (char*)&I_power, sizeof(I_power), 0);
	recv(FRAMEWORK->GetSock(), (char*)&I_skill, sizeof(I_skill), 0);
	recv(FRAMEWORK->GetSock(), (char*)&I_bullet, sizeof(I_bullet), 0);
	recv(FRAMEWORK->GetSock(), (char*)&I_sub, sizeof(I_sub), 0);
	recv(FRAMEWORK->GetSock(), (char*)&I_sheild, sizeof(I_sheild), 0);
}
void CMyInGame::MakeItem()
{
	recv(FRAMEWORK->GetSock(), (char*)&ItemTimeCount, sizeof(ItemTimeCount), 0);
	if (ItemTimeCount /= g_makeItem1)
	{
		I_power.push_back(new I_POWER());

		//printf("파워 생성");
	}
	if (ItemTimeCount /= g_makeSkill)
	{
		I_skill.push_back(new I_SKILL());

		//printf("스킬 생성");

	}
	if (ItemTimeCount /= g_makeBullet)
	{
		I_bullet.push_back(new I_BULLET());

		//printf("보조총알 생성");

	}
	if (ItemTimeCount /= g_makeSub)
	{
		I_sub.push_back(new I_SUB());

	}
	if (ItemTimeCount /= g_makeShield)
	{
		I_sheild.push_back(new I_SHEILD());

	}
}
void CMyInGame::MakeEnemys()
{
	int num;
	recv(FRAMEWORK->GetSock(), (char*)&num, sizeof(num), 0);
	for (int i = 0; i < num; ++i) {
		recv(FRAMEWORK->GetSock(), (char*)&enemyInfo, sizeof(enemyInfo), 0);
		if (enemyInfo.alive == true)
		{
			switch (enemyInfo.Type)
			{
			case E_ENEMY1:
				m_Monster[enemyInfo.index]->SetType(E_ENEMY1);
				m_Monster[enemyInfo.index]->SetAlive(true);
				m_Monster[enemyInfo.index]->SetHp(enemyInfo.Hp);
				m_Monster[enemyInfo.index]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
				break;
			case E_ENEMY2:
				m_Monster[enemyInfo.index]->SetType(E_ENEMY2);
				m_Monster[enemyInfo.index]->SetAlive(true);
				m_Monster[enemyInfo.index]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
				break;
			case E_ENEMY3:
				m_Monster[enemyInfo.index]->SetType(E_ENEMY3);
				m_Monster[enemyInfo.index]->SetAlive(true);
				m_Monster[enemyInfo.index]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
				break;
			case E_BOSS1:
				m_Monster[enemyInfo.index]->SetType(E_BOSS1);
				m_Monster[enemyInfo.index]->SetAlive(true);
				m_Monster[enemyInfo.index]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
				break;
			case E_BOSS2:
				m_Monster[enemyInfo.index]->SetType(E_BOSS2);
				m_Monster[enemyInfo.index]->SetAlive(true);
				m_Monster[enemyInfo.index]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
				break;
			}
		}

	}
}
void CMyInGame::Destroy()
{

}

void CMyInGame::Enter()
{
	
}

void CMyInGame::Exit()
{
}

void CMyInGame::CheckKey()
{
}

