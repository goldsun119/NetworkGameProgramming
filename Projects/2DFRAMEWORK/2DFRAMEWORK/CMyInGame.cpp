#include "stdafx.h"
#include "CMyInGame.h"


CMyInGame::CMyInGame()
{
}


CMyInGame::~CMyInGame()
{
}

void CMyInGame::Render(HDC memDc)
{

	CImage img;
	//img.Load(*MYRENDERMANAGER->FindCImage("MenuImage"));

	img.Load(TEXT("background.png"));
	//img.Create(m_nWndClientWidth, m_nWndClientHeight, 24);
	PAINTSTRUCT ps;
	BeginPaint(g_hWnd, &ps);
	{
		//HDC memDC = CreateCompatibleDC(hdc);
		//HBITMAP memBit = CreateCompatibleBitmap(hdc, m_nWndClientWidth, m_nWndClientHeight);
		//SelectObject(memDC, memBit);

		img.Draw(memDc, 100, 100,200,200);

		//BitBlt(memDc, 0, 0, 800, 600, m_MenuImageMap["MenuBackGroundImage"].begin()->GetCimage()->GetDC(), 0, 0, SRCCOPY);
		//DeleteObject(memBit);
		//DeleteDC(memDC);
	}
	EndPaint(g_hWnd, &ps);
	img.Destroy();
}

void CMyInGame::Update()
{
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

