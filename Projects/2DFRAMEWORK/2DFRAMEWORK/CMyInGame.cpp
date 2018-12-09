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

#define g_makeItem1 39000
#define g_makeBullet 4000
#define g_makePower 5000
#define g_makeSkill 61000
#define g_makeSub 40000

#define g_makeShield 91000

CMyInGame::CMyInGame()
{
	m_pMonster = new CMonster;
	m_Monster.reserve(MAXOBJECTNUM);
	I_sub.reserve(MAXITEMNUM);
	I_bullet.reserve(MAXITEMNUM);
	I_skill.reserve(MAXITEMNUM);
	I_power.reserve(MAXITEMNUM);
	I_sheild.reserve(MAXITEMNUM);

	for (int i = 0; i < 300; ++i) {
		m_Monster.emplace_back(new CMonster());
		for (int j = 0; j < 50; ++j)
			m_Monster[i]->enemy_bullet.emplace_back();
	}

	for (int i = 0; i < 3000; ++i) {
		m_pPlayer->m_PlayerBullet.emplace_back(new CBullet());
		m_p2Player->m_PlayerBullet.emplace_back(new CBullet());
	}
	
	for (int i = 0; i < 100; ++i)
	{
		I_bullet.emplace_back(new I_BULLET(itemInfo));
		I_sheild.emplace_back(new I_SHEILD(itemInfo));
		I_sub.emplace_back(new I_SUB(itemInfo));
		I_power.emplace_back(new I_POWER(itemInfo));
		I_skill.emplace_back(new I_SKILL(itemInfo));
	}

	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngameBackGroundImage", *MYRENDERMANAGER->FindCImage("IngameBackGroundImage")));
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngamePlayerImage", *MYRENDERMANAGER->FindCImage("IngamePlayerImage")));
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngameHPImage", *MYRENDERMANAGER->FindCImage("IngameHPImage")));
	

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
	m_PlayerLifeImg.Load(TEXT("image/목숨.png"));

	m_PlayerBulletImg.Load(TEXT("image/총알기본.png"));
	m_MonsterImg1.Load(TEXT("enemy1.png"));
	m_MonsterImg2.Load(TEXT("enemy2.png"));
	m_MonsterImg3.Load(TEXT("enemy3.png"));
	m_BossImg1.Load(TEXT("boss1-1.png"));
	m_BossImg2.Load(TEXT("boss2.png"));
	m_SkillImg.Load(TEXT("skill.png"));
	//적총알 이미지
	m_MonsterBullet1.Load(TEXT("image/적총알기본.png"));
	m_MonsterBullet2.Load(TEXT("image/적총알2.png"));
	m_MonsterBullet3.Load(TEXT("image/적총알3.png"));
	m_BossBullet1.Load(TEXT("image/적총알4.png"));
	m_BossBullet2.Load(TEXT("image/적총알5.png"));
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
	m_SkillImg.Destroy();
}

void CMyInGame::Render(HDC hdc)
{

	//m_PlayerImg = MYRENDERMANAGER->FindCImage("IngamePlayerImage")->begin()->GetCimage();
	PAINTSTRUCT ps;
	BeginPaint(g_hWnd, &ps);
	{
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, m_nWndClientWidth, m_nWndClientHeight);
		SelectObject(memDC, memBit);
		StretchBlt(memDC, 0, 0, 403, 599, m_IngameImageMap["IngameBackGroundImage"].begin()->GetCimage()->GetDC(), 0, 0, 360, 600, SRCCOPY);
		
		if(m_pPlayer->GetHp() >0)
			m_PlayerImg.Draw(memDC, m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetSize(), m_pPlayer->GetSize());

		if (m_p2Player->GetHp() > 0)
			m_2PlayerImg.Draw(memDC, m_p2Player->GetPos().x, m_p2Player->GetPos().y, m_p2Player->GetSize(), m_p2Player->GetSize());
		//UI - HP
		if (m_pPlayer->GetHp() != 0)
		{
			for (int i = 0; i < m_pPlayer->GetHp(); ++i)
			{
				m_PlayerLifeImg.Draw(memDC, WndX- (m_UiSize * 2) - (m_UiSize * i), 10, m_UiSize, m_UiSize);
			}
		}
		//UI - SKILL
		if (m_pPlayer->GetSkillCount() != 0)
		{
			for (int i = 0; i < m_pPlayer->GetSkillCount(); ++i)
			{
				m_ItemUlt.Draw(memDC, WndX - (m_UiSize * 2) - (m_UiSize * i), (WndY - m_UiSize*2), m_UiSize, m_UiSize);
			}
		}
		//몬스터 그리기
		for (vector<CMonster*>::iterator iter = m_Monster.begin();
			iter != m_Monster.end(); ++iter)
		{	
			if ((*iter)->alive == true) {
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
		//총알 그리기
		//적1
		for (vector<CMonster*>::iterator iter = m_Monster.begin(); iter != m_Monster.end(); ++iter) {
			if ((*iter)->alive == true) {
				for (vector<CBullet>::iterator bulletiter = (*iter)->enemy_bullet.begin(); bulletiter != (*iter)->enemy_bullet.end(); ++bulletiter)
				{
					m_MonsterBullet1.Draw(memDC, (bulletiter)->GetPos().x, (bulletiter)->GetPos().y, (bulletiter)->GetSize(), (bulletiter)->GetSize());
				}
			}
		}


		//아이템 - 총알
		for (vector<I_BULLET*>::iterator iter = I_bullet.begin();
			iter != I_bullet.end(); ++iter)
		{
			if ((*iter)->alive == true) 
				m_ItemBullet.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}
		//아이템 - 방어막
		for (vector<I_SHEILD*>::iterator iter = I_sheild.begin();
			iter != I_sheild.end(); ++iter)
		{
			if ((*iter)->alive == true)
				m_BItemShield.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}
		//아이템 - 궁아이템획득
		for (vector<I_SKILL*>::iterator iter = I_skill.begin();
			iter != I_skill.end(); ++iter)
		{
			if ((*iter)->alive == true)
				m_ItemUlt.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}
		//아이템 - 보조
		for (vector<I_SUB*>::iterator iter = I_sub.begin();
			iter != I_sub.end(); ++iter)
		{
			if ((*iter)->alive == true)
				m_ItemSub.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}
		//아이템 - 강화
		for (vector<I_POWER*>::iterator iter = I_power.begin();
			iter != I_power.end(); ++iter)
		{
			if ((*iter)->alive == true)
				m_ItemPower.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}

		//플레이어 총알 그리기
		vector<CBullet*>::iterator iter = m_pPlayer->m_PlayerBullet.begin();
		while (iter != m_pPlayer->m_PlayerBullet.end())
		{
			if ((*iter)->alive == true) {
				m_PlayerBulletImg.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
			}
			iter++;
		}

		//플레이어2 총알 그리기
		vector<CBullet*>::iterator iter2 = m_p2Player->m_PlayerBullet.begin();
		while (iter2 != m_p2Player->m_PlayerBullet.end())
		{
			if ((*iter2)->alive == true) {
				m_PlayerBulletImg.Draw(memDC, (*iter2)->GetPos().x, (*iter2)->GetPos().y, (*iter2)->GetSize(), (*iter2)->GetSize());
			}
			iter2++;
		}
		//스킬
		if (m_pPlayer->GetSkillPlay() == true || m_p2Player->GetSkillPlay() == true) {
			if (m_pPlayer->GetSkillCount() > 0 || m_p2Player->GetSkillCount() > 0) {
				m_SkillImg.Draw(memDC, skillPosX, skillPosY, 400, 400);
			}
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
	
	switch (FRAMEWORK->m_ClientInfo.PlayNum) //플레이어의 위치
	{
	case 0:
		m_pPlayer->SetPos(playerInfo[0].Pos.x, playerInfo[0].Pos.y);
		m_pPlayer->SetHp(playerInfo[0].Hp);
		m_p2Player->SetPos(playerInfo[1].Pos.x, playerInfo[1].Pos.y);
		m_p2Player->SetHp(playerInfo[1].Hp);
		m_pPlayer->SetSkillPlay(playerInfo[0].skill);
		m_p2Player->SetSkillPlay(playerInfo[1].skill);
		break;
	case 1:
		m_pPlayer->SetPos(playerInfo[1].Pos.x, playerInfo[1].Pos.y);
		m_pPlayer->SetHp(playerInfo[1].Hp);
		m_p2Player->SetPos(playerInfo[0].Pos.x, playerInfo[0].Pos.y);
		m_p2Player->SetHp(playerInfo[0].Hp);
		m_pPlayer->SetSkillPlay( playerInfo[1].skill);
		m_p2Player->SetSkillPlay(playerInfo[0].skill);
		break;
	}
	//스킬업뎃	
	if (m_pPlayer->GetSkillPlay() == true || m_p2Player->GetSkillPlay() == true) {
		
		skillPosY -= 1.5f;
		if (skillPosY < 0.0f) {

			skillPosY = 400.0f;
			
			m_pPlayer->Skillplay = false;
			m_p2Player->Skillplay = false;
			if (m_pPlayer->GetSkillPlay() == false || m_p2Player->GetSkillPlay() == false) {
				m_pPlayer->SetSkillCount(m_pPlayer->GetSkillCount() - 1);
				m_p2Player->SetSkillCount(m_p2Player->GetSkillCount() - 1);
				
			}
			
		}
	}
	send(FRAMEWORK->GetSock(), (char*)&m_pPlayer->skillPlaying, sizeof(m_pPlayer->skillPlaying), 0);

	if (m_pPlayer->skillPlaying == true) {
		int monsize = 0;
		recv(FRAMEWORK->GetSock(), (char*)&monsize, sizeof(monsize), 0);
		//미리 사이즈를 알려줌
		for (int i = 0; i < monsize; ++i)
		{
			recv(FRAMEWORK->GetSock(), (char*)&enemyInfo, sizeof(enemyInfo), 0);
			m_Monster[i]->alive = enemyInfo.alive;
			m_Monster[i]->SetHp(enemyInfo.Hp);
			
		}
		m_pPlayer->skillPlaying = false;
	}
	MakeEnemys();
	int num2 = 0;

	MakeItem();

	int Bnum = 0;
	int B2num = 0;

	if (FRAMEWORK->m_ClientInfo.PlayNum == 0)
	{
		recv(FRAMEWORK->GetSock(), (char*)&Bnum, sizeof(Bnum), 0);


		if (Bnum > 0) {
			for (int i = 0; i < m_pPlayer->m_PlayerBullet.size(); ++i)
			{
				if (i < Bnum)
				{
					recv(FRAMEWORK->GetSock(), (char*)&bulletInfo, sizeof(bulletInfo), 0);
					m_pPlayer->m_PlayerBullet[i]->alive = bulletInfo.Active;
					m_pPlayer->m_PlayerBullet[i]->SetPos(bulletInfo.Pos.x, bulletInfo.Pos.y);
				}
				else
				{
					m_pPlayer->m_PlayerBullet[i]->alive = false;
					m_pPlayer->m_PlayerBullet[i]->SetPos(0, 0);
				}
			}
			int msize = 0;
			recv(FRAMEWORK->GetSock(), (char*)& msize, sizeof(msize), 0);
			//미리 사이즈를 알려줌
			for (int i = 0; i < msize; ++i)
			{
				recv(FRAMEWORK->GetSock(), (char*)&enemyInfo, sizeof(enemyInfo), 0);
				m_Monster[i]->alive = enemyInfo.alive;
				m_Monster[i]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
			}
		}

		recv(FRAMEWORK->GetSock(), (char*)&B2num, sizeof(B2num), 0);

		if (B2num > 0) {
			for (int i = 0; i < m_p2Player->m_PlayerBullet.size(); ++i)
			{
				if (i < B2num)
				{
					recv(FRAMEWORK->GetSock(), (char*)&bulletInfo, sizeof(bulletInfo), 0);
					m_p2Player->m_PlayerBullet[i]->alive = bulletInfo.Active;
					m_p2Player->m_PlayerBullet[i]->SetPos(bulletInfo.Pos.x, bulletInfo.Pos.y);
				}
				else
				{
					m_p2Player->m_PlayerBullet[i]->alive = false;
					//m_p2Player->m_PlayerBullet[i]->SetPos(0,0);
				}
			}
			int msize = 0;
			recv(FRAMEWORK->GetSock(), (char*)& msize, sizeof(msize), 0);
			//미리 사이즈를 알려줌
			for (int i = 0; i < msize; ++i)
			{
				recv(FRAMEWORK->GetSock(), (char*)&enemyInfo, sizeof(enemyInfo), 0);
				m_Monster[i]->alive = enemyInfo.alive;
				m_Monster[i]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
			}
		}
	}
	else
	{
		recv(FRAMEWORK->GetSock(), (char*)&Bnum, sizeof(Bnum), 0);


		if (Bnum > 0) {
			for (int i = 0; i < m_p2Player->m_PlayerBullet.size(); ++i)
			{
				if (i < Bnum)
				{
					recv(FRAMEWORK->GetSock(), (char*)&bulletInfo, sizeof(bulletInfo), 0);
					m_p2Player->m_PlayerBullet[i]->alive = bulletInfo.Active;
					m_p2Player->m_PlayerBullet[i]->SetPos(bulletInfo.Pos.x, bulletInfo.Pos.y);
				}
				else
				{
					m_p2Player->m_PlayerBullet[i]->alive = false;
					m_p2Player->m_PlayerBullet[i]->SetPos(0, 0);
				}
			}
			int msize = 0;
			recv(FRAMEWORK->GetSock(), (char*)& msize, sizeof(msize), 0);
			//미리 사이즈를 알려줌
			for (int i = 0; i < msize; ++i)
			{
				recv(FRAMEWORK->GetSock(), (char*)&enemyInfo, sizeof(enemyInfo), 0);
				m_Monster[i]->alive = enemyInfo.alive;
				m_Monster[i]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
			}
		}

		recv(FRAMEWORK->GetSock(), (char*)&B2num, sizeof(B2num), 0);

		if (B2num > 0) {
			for (int i = 0; i < m_pPlayer->m_PlayerBullet.size(); ++i)
			{
				if (i < B2num)
				{
					recv(FRAMEWORK->GetSock(), (char*)&bulletInfo, sizeof(bulletInfo), 0);
					m_pPlayer->m_PlayerBullet[i]->alive = bulletInfo.Active;
					m_pPlayer->m_PlayerBullet[i]->SetPos(bulletInfo.Pos.x, bulletInfo.Pos.y);
				}
				else
				{
					m_pPlayer->m_PlayerBullet[i]->alive = false;
					//m_p2Player->m_PlayerBullet[i]->SetPos(0,0);
				}
			}
			int msize = 0;
			recv(FRAMEWORK->GetSock(), (char*)& msize, sizeof(msize), 0);
			//미리 사이즈를 알려줌
			for (int i = 0; i < msize; ++i)
			{
				recv(FRAMEWORK->GetSock(), (char*)&enemyInfo, sizeof(enemyInfo), 0);
				m_Monster[i]->alive = enemyInfo.alive;
				m_Monster[i]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
			}
		}
	}

}
	
	


void CMyInGame::MakeItem()
{
	int num = 0;
	recv(FRAMEWORK->GetSock(), (char*)&num, sizeof(num), 0);

		for (int i = 0; i < num; ++i)
		{
			recv(FRAMEWORK->GetSock(), (char*)&itemInfo, sizeof(itemInfo), 0);
			if (itemInfo.Index < 10) {
				switch (itemInfo.Type)
				{
				case E_IPOWER:
					
					I_power[itemInfo.Index]->alive = itemInfo.alive;
					I_power[itemInfo.Index]->SetPos(itemInfo.pos.x, itemInfo.pos.y);
					I_power[itemInfo.Index]->SetSize(10);
					//printf("파워 생성");
					break;

				case E_ISKILL:
					I_skill[itemInfo.Index]->alive = itemInfo.alive;
					I_skill[itemInfo.Index]->SetPos(itemInfo.pos.x, itemInfo.pos.y);
					I_skill[itemInfo.Index]->SetSize(10);
					//printf("스킬 생성");
					break;

				case E_IBULLET:
					I_bullet[itemInfo.Index]->alive = itemInfo.alive;
					I_bullet[itemInfo.Index]->SetPos(itemInfo.pos.x, itemInfo.pos.y);
					I_bullet[itemInfo.Index]->SetSize(10);
					break;

				case E_ISUB:
					I_sub[itemInfo.Index]->alive = itemInfo.alive;
					I_sub[itemInfo.Index]->SetPos(itemInfo.pos.x, itemInfo.pos.y);
					I_sub[itemInfo.Index]->SetSize(10);
					//printf("보조총알 생성");
					break;

				case E_ISHIELD:
					I_sheild[itemInfo.Index]->alive = itemInfo.alive;
					I_sheild[itemInfo.Index]->SetPos(itemInfo.pos.x, itemInfo.pos.y);
					I_sheild[itemInfo.Index]->SetSize(10);
					break;

				}
			}
		}
}

void CMyInGame::MakeEnemys()
{
	
	int num=0;
	int num2 = 0;
	recv(FRAMEWORK->GetSock(), (char*)&num, sizeof(num), 0);
	for (int i = 0; i < num; ++i) {
		recv(FRAMEWORK->GetSock(), (char*)&enemyInfo, sizeof(enemyInfo), 0);
			switch (enemyInfo.Type)
			{
			case E_ENEMY1:
				m_Monster[enemyInfo.index]->SetType(E_ENEMY1);
				m_Monster[enemyInfo.index]->alive = true;
				m_Monster[enemyInfo.index]->SetHp(enemyInfo.Hp);
				m_Monster[enemyInfo.index]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
				m_Monster[enemyInfo.index]->SetSize(60);
				break;
			case E_ENEMY2:
				m_Monster[enemyInfo.index]->SetType(E_ENEMY2);
				m_Monster[enemyInfo.index]->alive = true;
				m_Monster[enemyInfo.index]->SetHp(enemyInfo.Hp);
				m_Monster[enemyInfo.index]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
				m_Monster[enemyInfo.index]->SetSize(70);
				break;
			case E_ENEMY3:
				m_Monster[enemyInfo.index]->SetType(E_ENEMY3);
				m_Monster[enemyInfo.index]->alive = true;
				m_Monster[enemyInfo.index]->SetHp(enemyInfo.Hp);
				m_Monster[enemyInfo.index]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
				m_Monster[enemyInfo.index]->SetSize(80);
				break;
			case E_BOSS1:
				m_Monster[enemyInfo.index]->SetType(E_BOSS1);
				m_Monster[enemyInfo.index]->alive = true;
				m_Monster[enemyInfo.index]->SetHp(enemyInfo.Hp);
				m_Monster[enemyInfo.index]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
				m_Monster[enemyInfo.index]->SetSize(90);
				break;
			case E_BOSS2:
				m_Monster[enemyInfo.index]->SetType(E_BOSS2);
				m_Monster[enemyInfo.index]->alive = true;
				m_Monster[enemyInfo.index]->SetHp(enemyInfo.Hp);
				m_Monster[enemyInfo.index]->SetPos(enemyInfo.pos.x, enemyInfo.pos.y);
				m_Monster[enemyInfo.index]->SetSize(100);
				break;
			}
			recv(FRAMEWORK->GetSock(), (char*)&num2, sizeof(num2), 0);
			if (num2 != 0) {
				for (int i = 0; i < num2; ++i)
				{
					recv(FRAMEWORK->GetSock(), (char*)&enemybulletInfo, sizeof(enemybulletInfo), 0);
					m_Monster[enemyInfo.index]->enemy_bullet[i].alive = enemybulletInfo.Active;
					m_Monster[enemyInfo.index]->enemy_bullet[i].SetPos(enemybulletInfo.Pos.x, enemybulletInfo.Pos.y);
				}
			}

	}
	//m_Monster[0]->alive = false;
	//m_Monster[1]->alive = false;
	//m_Monster[2]->alive = false;
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

