#include "stdafx.h"
#include "CMyInGame.h"
#include "CObjectManager.h"
#include "TimerManager.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CBullet.h"

CMyInGame::CMyInGame()
{

	//Player *m_pPlayer = NULL;
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngameBackGroundImage", *MYRENDERMANAGER->FindCImage("IngameBackGroundImage")));
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngamePlayerImage", *MYRENDERMANAGER->FindCImage("IngamePlayerImage")));
	//m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("PlayerDefaultBulletImage", *MYRENDERMANAGER->FindCImage("PlayerDefaultBulletImage")));


}


CMyInGame::~CMyInGame()
{
}

void CMyInGame::Render(HDC hdc)
{

	int size = 50;

	//왜 렌더매니저 안써줌 ㅠ
	m_PlayerImg.Load(TEXT("Player1.png"));
	m_MonsterImg.Load(TEXT("enemy1.png"));

	m_PlayerBulletImg.Load(TEXT("image/총알기본.png"));


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
		for (vector<CGameObject*>::iterator iter = ObjList.begin(); iter != ObjList.end(); ++iter)
		{
			m_MonsterImg.Draw(memDC, (*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		}
		//플레이어 총알 그리기
		//1119 stl고수 천기님
		//for (vector<CBullet>::iterator iter = m_pPlayer->m_PlayerBullet.begin(); iter != m_pPlayer->m_PlayerBullet.end(); ++iter)
		//{
		//	m_PlayerBulletImg.Draw(memDC, iter->GetPos().x, (iter)->GetPos().y, (*iter)->GetSize(), (*iter)->GetSize());
		//}
		vector<CBullet>::iterator iter = m_pPlayer->m_PlayerBullet.begin();
		while (iter != m_pPlayer->m_PlayerBullet.end())
		{
				m_PlayerBulletImg.Draw(memDC, (*iter).GetPos().x, (*iter).GetPos().y, (*iter).GetSize(), (*iter).GetSize());
			iter++;
		}


		BitBlt(hdc, 0, 0, 403, 599, memDC, 0, 0, SRCCOPY);
		DeleteObject(memBit);
		DeleteDC(memDC);
	}
	EndPaint(g_hWnd, &ps);
	m_PlayerImg.Destroy();
	m_MonsterImg.Destroy();
	m_PlayerBulletImg.Destroy();

}

void CMyInGame::Update()
{
	m_pPlayer->Update();
	
	int eTime = TIMEMANAGER->GetFimeElapsed()/1000;
	
	switch (eTime)
	{
	case 5:
		MakeEnemy.AddGameObject(m_pMonster, E_ENEMY);
		MakeEnemy.SetObjlist(ObjList);
		break;
	default:
		break;
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

