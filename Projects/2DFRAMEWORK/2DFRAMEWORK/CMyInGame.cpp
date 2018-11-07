#include "stdafx.h"
#include "CMyInGame.h"


CMyInGame::CMyInGame()
{
	m_IngameImageMap.insert(pair<std::string, std::vector<MyImage>>("IngameBackGroundImage", *MYRENDERMANAGER->FindCImage("IngameBackGroundImage")));

}


CMyInGame::~CMyInGame()
{
}

void CMyInGame::Render(HDC hdc)
{

	CImage img;
	//img.Load(*MYRENDERMANAGER->FindCImage("MenuImage"));

	//img.Load(TEXT("background.png"));
	//img.Create(m_nWndClientWidth, m_nWndClientHeight, 24);
	PAINTSTRUCT ps;
	BeginPaint(g_hWnd, &ps);
	{
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, m_nWndClientWidth, m_nWndClientHeight);
		SelectObject(memDC, memBit);

		//img.Draw(memDc, 0, 0,360,600);

		StretchBlt (hdc, 0, 0, 403, 599, m_IngameImageMap["IngameBackGroundImage"].begin()->GetCimage()->GetDC(), 0, 0,360,600, SRCCOPY);
		DeleteObject(memBit);
		DeleteDC(memDC);
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

