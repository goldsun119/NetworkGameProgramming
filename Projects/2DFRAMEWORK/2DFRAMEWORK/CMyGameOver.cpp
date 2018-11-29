#include "stdafx.h"
#include "CMyGameOver.h"
#include "CMybutton.h"
#include "InputManager.h"
#include "CPlayer.h"

CMyGameOver::CMyGameOver()
{
	m_GameOverImageMap.insert(pair<std::string, std::vector<MyImage>>("GameOverBackGroundImage", *MYRENDERMANAGER->FindCImage("GameOverImage")));
	m_GameOverImageMap.insert(pair<std::string, std::vector<MyImage>>("GameOverExitButtonImage", *MYRENDERMANAGER->FindCImage("MenuExitButtonImage")));
	m_ListButton.push_back(new CMyButton("EXIT", 500.0f, 200.0f, 150.0f, 150.0f));
}
CMyGameOver::~CMyGameOver()
{
}

void CMyGameOver::Render(HDC hdc)
{
	PAINTSTRUCT ps;
	BeginPaint(g_hWnd, &ps);
	{
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, m_nWndClientWidth, m_nWndClientHeight);
		SelectObject(memDC, memBit);
		StretchBlt(memDC, 0, 0, 403, 599, m_GameOverImageMap["GameOverBackGroundImage"].begin()->GetCimage()->GetDC(), 0, 0, 360, 600, SRCCOPY);

		TransparentBlt(memDC, 240, 400, 100, 100, m_GameOverImageMap["GameOverExitButtonImage"].begin()->GetCimage()->GetDC(), 0, 0,
		199,100, SRCCOPY);
		BitBlt(hdc, 0, 0, 800, 600, memDC, 0, 0, SRCCOPY);
		DeleteObject(memBit);
		DeleteDC(memDC);
	}
	EndPaint(g_hWnd, &ps);
}

void CMyGameOver::Update()
{
	CheckKey();

}

void CMyGameOver::Destroy()
{
}

void CMyGameOver::Enter()
{
}

void CMyGameOver::Exit()
{
}

void CMyGameOver::CheckKey()
{
	DWORD Key = INPUTMANAGER->GetKeyState();
	if (Key == KEY_END)
	{
		//ฒ๔ดยนý,,?
		exit(0);
	}
}
