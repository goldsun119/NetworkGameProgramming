#include "stdafx.h"
#include "CMyInGame.h"
#include "CObjectManager.h"
#include "TimerManager.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CBullet.h"
#include "TimerManager.h"
CMyInGame::CMyInGame()
{

	//Player *m_pPlayer = NULL;
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngameBackGroundImage", *MYRENDERMANAGER->FindCImage("IngameBackGroundImage")));
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngamePlayerImage", *MYRENDERMANAGER->FindCImage("IngamePlayerImage")));
	//m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("PlayerDefaultBulletImage", *MYRENDERMANAGER->FindCImage("PlayerDefaultBulletImage")));
	
	//왜 렌더매니저 안써줌 ㅠ
	m_PlayerImg.Load(TEXT("Player1.png"));
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
		
		//몬스터 그리기
		for (vector<CMonster*>::iterator iter = m_Monster.begin();
			iter != m_Monster.end(); ++iter)
		{	
			if ((*iter)->GetHp() > 0)
			{
				if((*iter)->GetType() == E_ENEMY1)
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

	//적 비행기 생성
	switch (eTime)
	{
	case 30: //1번 적비행기 3초마다 생성
		m_Monster.push_back(new CMonster(E_ENEMY1));
		break;
	case 70: //2번 적비행기 7초마다 생성
		m_Monster.push_back(new CMonster(E_ENEMY2));
		break;
	case 110: //3번 적비행기 11초마다 생성
		m_Monster.push_back(new CMonster(E_ENEMY3));
		break;
	case 61: //1번 보스 61초에 생성
		if (Boss1_Appear == false) {  //이미 생성 되있는지 확인
			m_Monster.push_back(new CMonster(E_BOSS1));
			Boss1_Appear = true;
			break;
		}
		break;
	case 91: //2번 보스91초에 생성
		if (Boss2_Appear == false) { //이미 생성 되있는지 확인
			m_Monster.push_back(new CMonster(E_BOSS2));
			Boss2_Appear = true;
			break;
		}
		break;
	}
	eTime++;
	// 문제인부분이 
	//적 이동
	//if (m_Monster.size() > 0)
	{
		for (int i = 0; i < m_Monster.size(); ++i)
		{
			
				if (m_Monster[i]->GetYPos() < WndY)
				{
					if (m_Monster[i]->GetType() == E_ENEMY1)
					{
						m_Monster[i]->SetYPos(m_Monster[i]->GetYPos() + 2);
					}
					else
					{
						m_Monster[i]->SetYPos(m_Monster[i]->GetYPos() + 3);

					}

					for (auto bullet = m_pPlayer->m_PlayerBullet.begin(); bullet < m_pPlayer->m_PlayerBullet.end(); ++bullet)
					{
						if ((*bullet)->GetActive())
						{

							RECT rt1, rt2, rt3;
							rt1.top = (*bullet)->GetYPos(), rt1.bottom = (*bullet)->GetYPos() + (*bullet)->GetSize(), rt1.left = (*bullet)->GetXPos(), rt1.right = (*bullet)->GetXPos() + (*bullet)->GetSize();
							switch (m_Monster[i]->GetType())
							{
							case 1:
								rt2.top = m_Monster[i]->GetYPos(), rt2.bottom = m_Monster[i]->GetYPos() + m_Monster[i]->GetSize(), rt2.left = m_Monster[i]->GetYPos(), rt2.right = m_Monster[i]->GetXPos() + m_Monster[i]->GetSize();
								break;
							//case 2:
							//	rt2.top = m_Monster[i]->GetYPos(), rt2.bottom = m_Monster[i]->GetYPos() + (*iter)->GetSize(), rt2.left = (*iter)->GetYPos(), rt2.right = (*iter)->GetXPos() + (*iter)->GetSize();

							//	//rt2.top = (*iter)->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 50, rt2.left = enemy->GetXPos(), rt2.right = enemy->GetXPos() + enemy->GetSize();
							//	break;
							//case 3:
							//	rt2.top = (*iter)->GetYPos(), rt2.bottom = (*iter)->GetYPos() + (*iter)->GetSize() - 50, rt2.left = (*iter)->GetYPos(), rt2.right = (*iter)->GetXPos() + (*iter)->GetSize();

							//	//rt2.top = (*iter)->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 50, rt2.left = enemy->GetXPos() + 50, rt2.right = enemy->GetXPos() + enemy->GetSize() - 50;
							//	break;
							//case 4:
							//	rt2.top = (*iter)->GetYPos(), rt2.bottom = (*iter)->GetYPos() + (*iter)->GetSize() - 200, rt2.left = (*iter)->GetYPos(), rt2.right = (*iter)->GetXPos() + (*iter)->GetSize();

							//	//rt2.top = (*iter)->GetYPos(), rt2.bottom = enemy->GetYPos() + enemy->GetSize() - 200, rt2.left = enemy->GetXPos() + 50, rt2.right = enemy->GetXPos() + enemy->GetSize() - 50;
							//	break;
							}

							/*if (IntersectRect(&rt3, &rt1, &rt2))
							{
								(*iter)->SetHp((*iter)->GetHp() - 10);
								(*bullet)->SetActive(false);
							}*/
						}
					}



				}
				if (m_Monster[i]->GetYPos() > WndY)
				{


				iter_swap(m_Monster[i], m_Monster.back());
				if (m_Monster.back())
				{
					delete m_Monster.back();
					m_Monster.back() = nullptr;
				}
				m_Monster.pop_back();
				}

		}

	}
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

