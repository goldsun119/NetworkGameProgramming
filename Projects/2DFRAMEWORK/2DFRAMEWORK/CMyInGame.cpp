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
	
	//�� �����Ŵ��� �Ƚ��� ��
	m_PlayerImg.Load(TEXT("Player1.png"));
	m_PlayerBulletImg.Load(TEXT("image/�Ѿ˱⺻.png"));
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
		
		//���� �׸���
		for (vector<CGameObject*>::iterator iter = ObjList.begin(); iter != ObjList.end(); ++iter)
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

		//�÷��̾� �Ѿ� �׸���
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

	//��� ������ timer�� ���������. �̾������� Ÿ�̸Ӹ� ������ �ȉ�.
	//���̴°ű��� �ϰ� �ٵȰ��ϰ� Ÿ�̸�Ŭ���� �缳���ʿ�.
	TIMEMANAGER->SetCurFimeElapsed();
	TIMEMANAGER->SetFimeElapsed();
	int eTime = TIMEMANAGER->GetFimeElapsed() / 1000;
	
	//�� ����� ����
	switch (eTime)
	{
	case 3: //1�� ������� 3�ʸ��� ����
		OBJECTMANAGER->AddGameObject(m_pMonster1, E_ENEMY1, 30,30,30);
		OBJECTMANAGER->SetObjlist(ObjList);
		/*m_pMonster1->SetSize(50);
		m_pMonster1->SetType(E_ENEMY1);*/
		break;
	case 7: //2�� ������� 7�ʸ��� ����
		OBJECTMANAGER->AddGameObject(m_pMonster2, E_ENEMY2, 100,100,50);
		OBJECTMANAGER->SetObjlist(ObjList);
	/*	m_pMonster2->SetSize(100);
		m_pMonster2->SetType(E_ENEMY2);*/
		break;
	//case 11: //3�� ������� 11�ʸ��� ����
	//	MakeEnemy.AddGameObject(m_pMonster3, E_ENEMY3);
	//	MakeEnemy.SetObjlist(ObjList);
	//	m_pMonster3->SetSize(130);
	//	m_pMonster3->SetType(E_ENEMY3);
	//	break;
	//case 61: //1�� ���� 61�ʿ� ����
	//	if (m_pBoss1->Boss1_Appear == false) {  //�̹� ���� ���ִ��� Ȯ��
	//		MakeEnemy.AddGameObject(m_pBoss1, E_BOSS1);
	//		MakeEnemy.SetObjlist(ObjList);
	//		m_pBoss1->SetSize(130);
	//		m_pBoss1->Boss1_Appear = true;
	//		m_pBoss1->SetType(E_BOSS1);
	//		break;
	//	}
	//	break;
	//case 91: //2�� ����91�ʿ� ����
	//	if (m_pBoss2->Boss2_Appear == false) { //�̹� ���� ���ִ��� Ȯ��
	//		MakeEnemy.AddGameObject(m_pBoss2, E_BOSS2);
	//		MakeEnemy.SetObjlist(ObjList);
	//		m_pBoss2->SetSize(150);
	//		m_pBoss2->Boss2_Appear = true;
	//		m_pBoss2->SetType(E_BOSS2);
	//		break;
	//	}
	//	break;
	}
	

	//�� �̵�
	for (vector<CGameObject*>::iterator iter = ObjList.begin(); iter != ObjList.end(); ++iter)
	{
		if ((*iter)->GetYPos() < WndY)
		{
			if ((*iter)->GetType() == E_ENEMY1)
			{
				(*iter)->SetYPos((*iter)->GetYPos() + 1);
			}
			else
			{
				(*iter)->SetYPos((*iter)->GetYPos() + 2);

			}
		
		}

		else //yPos�� ������ âũ�⺸�� ũ��
		{
			//���� ������.
			//swap���� �Ǵµ� �� ���پȵǳ� �ƿ�
			if (ObjList.size() > 2)
			{
				iter_swap(iter, ObjList.end());
				ObjList.pop_back();

			}
			else {
				//�ΰ� ���ϸ�

			}
			//swap()
			//iter_e
		}
	}

	OBJECTMANAGER->CheckEnemybyPlayerBulletCollision(m_pPlayer->m_PlayerBullet, OBJECTMANAGER->GetObjlist());
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

