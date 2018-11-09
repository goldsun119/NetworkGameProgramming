#include "stdafx.h"
#include "CMyInGame.h"
#include "CObjectManager.h"
#include "CGameObject.h"
#include "CPlayer.h"


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
	CImage img;

	img.Load(TEXT("Player1.png"));
	PAINTSTRUCT ps;
	BeginPaint(g_hWnd, &ps);
	{
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, m_nWndClientWidth, m_nWndClientHeight);
		SelectObject(memDC, memBit);
		StretchBlt(memDC, 0, 0, 403, 599, m_IngameImageMap["IngameBackGroundImage"].begin()->GetCimage()->GetDC(), 0, 0, 360, 600, SRCCOPY);
		img.Draw(memDC, m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetSize(), m_pPlayer->GetSize());
		//img.Draw(memDC, x, y, 50, 50);
		BitBlt(hdc, 0, 0, 403, 599, memDC, 0, 0, SRCCOPY);
		DeleteObject(memBit);
		DeleteDC(memDC);
	}
	EndPaint(g_hWnd, &ps);
	img.Destroy();

}

void CMyInGame::Update()
{
	m_pPlayer->Update();

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

