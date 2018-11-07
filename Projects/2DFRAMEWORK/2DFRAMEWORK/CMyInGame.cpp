#include "stdafx.h"
#include "CMyInGame.h"
#include "CGameObject.h"

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
	int x = 100;
	int y = 500;
	int size = 50;
	CImage img;
	PAINTSTRUCT ps;
	img.Load(TEXT("Player1.png"));
	BeginPaint(g_hWnd, &ps);
	{
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, m_nWndClientWidth, m_nWndClientHeight);
		SelectObject(memDC, memBit);

		StretchBlt(memDC, 0, 0, 403, 599, m_IngameImageMap["IngameBackGroundImage"].begin()->GetCimage()->GetDC(), 0, 0, 360, 600, SRCCOPY);
		img.Draw(memDC, x, y, size, size);
		//TransparentBlt(memDC, 0, 0, 100, 100, m_IngameImageMap["IngamePlayerImage"].begin()->GetCimage()->GetDC(), 0, 0, 100, 100, RGB(0, 255, 0));
		BitBlt(hdc, 0, 0, 403, 599, memDC, 0, 0, SRCCOPY);
		//BitBlt(hdc, 0, 0, 800, 599, memDC, 0, 0, SRCCOPY);

		DeleteObject(memBit);
		DeleteDC(memDC);
	}
	EndPaint(g_hWnd, &ps);


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

