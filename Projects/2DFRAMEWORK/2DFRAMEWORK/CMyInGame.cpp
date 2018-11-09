#include "stdafx.h"
#include "CMyInGame.h"
#include "CObjectManager.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "TimerManager.h"
#include "CMonster.h"

CMyInGame::CMyInGame()
{

	//Player *m_pPlayer = NULL;
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngameBackGroundImage", *MYRENDERMANAGER->FindCImage("IngameBackGroundImage")));
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngamePlayerImage", *MYRENDERMANAGER->FindCImage("IngamePlayerImage")));

}


CMyInGame::~CMyInGame()
{
}

void CMyInGame::Render(HDC hdc)
{

	int size = 50;

	m_PlayerImg.Load(TEXT("Player1.png"));


	PAINTSTRUCT ps;
	BeginPaint(g_hWnd, &ps);
	{
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, m_nWndClientWidth, m_nWndClientHeight);
		SelectObject(memDC, memBit);
		StretchBlt(memDC, 0, 0, 403, 599, m_IngameImageMap["IngameBackGroundImage"].begin()->GetCimage()->GetDC(), 0, 0, 360, 600, SRCCOPY);
		m_PlayerImg.Draw(memDC, m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetSize(), m_pPlayer->GetSize());
<<<<<<< HEAD
=======

	
>>>>>>> 578fee02186e0e0cc13a46f8495a6d479c5ce152
		//img.Draw(memDC, x, y, 50, 50);
		BitBlt(hdc, 0, 0, 403, 599, memDC, 0, 0, SRCCOPY);
		DeleteObject(memBit);
		DeleteDC(memDC);
	}
	EndPaint(g_hWnd, &ps);
	m_PlayerImg.Destroy();

}

void CMyInGame::Update()
{
	m_pPlayer->Update();

	int eTime = TIMEMANAGER->GetFimeElapsed()/1000;
	switch (eTime)
	{
	case 10:
		MakeEnemy.AddGameObject(m_pMonster, E_ENEMY);
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

