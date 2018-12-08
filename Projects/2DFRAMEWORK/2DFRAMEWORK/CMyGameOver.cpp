#include "stdafx.h"

#include "CMyGameOver.h"
#include "CMybutton.h"
#include "InputManager.h"
#include "CPlayer.h"
#include "Framework.h"

using namespace std;
CMyGameOver::CMyGameOver()
{
	m_GameOverImageMap.insert(pair<std::string, std::vector<MyImage>>("GameOverBackGroundImage", *MYRENDERMANAGER->FindCImage("GameOverImage")));
	m_GameOverImageMap.insert(pair<std::string, std::vector<MyImage>>("GameOverExitButtonImage", *MYRENDERMANAGER->FindCImage("MenuExitButtonImage")));
	m_ListButton.push_back(new CMyButton("EXIT", 500.0f, 200.0f, 150.0f, 150.0f));
	m_PlayerScore = 10;
	//StrToLpcstr(ScoreStr, score);

	//strcpy(ScoreStr, "hi");
	//_itoa_s(m_PlayerScore, ScoreStr, sizeof(ScoreStr), 10);
	//Str = to_string(m_PlayerScore);
	//send(FRAMEWORK->GetSock(), (char*)&FRAMEWORK->NICKNAME, sizeof(FRAMEWORK->NICKNAME), 0);

	recv(FRAMEWORK->GetSock(), (char*)&MyScore, sizeof(MyScore), 0);
	recv(FRAMEWORK->GetSock(), (char*)&Snum, sizeof(Snum), 0);
	for (int i = 0; i < Snum; ++i)
	{
		recv(FRAMEWORK->GetSock(), (char*)&RecvRank.first, sizeof(RecvRank.first), 0);
		recv(FRAMEWORK->GetSock(), (char*)&RecvRank.second, sizeof(RecvRank.second), 0);
		Rank.emplace_back(RecvRank);
	}

}
CMyGameOver::~CMyGameOver()
{
}

void CMyGameOver::StrToLpcstr(const char* source, wchar_t* dest)
{
	int length = strlen(source);

	for (int i = 0; i < strlen(source); ++i)
	{
		dest[i] = source[i];
	}
}

void CMyGameOver::Render(HDC hdc)
{
	PAINTSTRUCT ps;
	BeginPaint(g_hWnd, &ps);
	{
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, m_nWndClientWidth, m_nWndClientHeight);
		SelectObject(memDC, memBit);
		//StretchBlt(memDC, 0, 0, 403, 599, m_GameOverImageMap["GameOverBackGroundImage"].begin()->GetCimage()->GetDC(), 0, 0, 360, 600, SRCCOPY);

		hFont = CreateFont(40, 0, 0, 0, 0, true, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼편지체"));
		oldFont = (HFONT)SelectObject(memDC, hFont);

		SetTextColor(memDC, RGB(255, 255, 255));
		SetBkMode(memDC, OPAQUE);
		SetBkColor(memDC, RGB(100, 100, 100));

		/*sprintf_s(str, "%s", "Return to Game");
		TextOut(memDC, 100, 350, str, strlen(str));*/

		sprintf_s(str, "%d MyScore !",MyScore);
		TextOut(memDC, 100, 0, str, strlen(str));

		//INT T0 STRING에러
		/*sprintf_s(ScoreStr, "%s");
		TextOut(memDC, 300, 0, ScoreStr, strlen(ScoreStr));*/
		memset(str, 0, sizeof(str));
		
		for (int i = 0; i < Rank.size(); ++i)
		{
			sprintf(str, "%d 등 %7s : %5d",i+1, Rank[i].second.c_str(), Rank[i].first);
			TextOut(memDC, 100, 50+(i*50), str, _tcslen(str));
			//MyTextOut(memDC, 100, 50 + (i * 50), Rank[i]);
		}
		sprintf_s(str, "%s", "Go to Main");
		TextOut(memDC, 130, 460, str, strlen(str));

		sprintf_s(str, "%s", "Exit Program");
		TextOut(memDC, 120, 500, str, strlen(str));

		SelectObject(memDC, oldFont);
		DeleteObject(hFont);

		//TransparentBlt(memDC, 240, 400, 100, 100, m_GameOverImageMap["GameOverExitButtonImage"].begin()->GetCimage()->GetDC(), 0, 0,
		//199,100, SRCCOPY);
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
		//끄는법,,?
		exit(0);
	}
}

void CMyGameOver::MyTextOut(HDC hdc, int x, int y, Score score)
{
	////char t[50];
	////sprintf(t, "%s  %d", score.second, score.first);
	//WCHAR sz[100];
	//wsprintf(sz, L"%s %d", score.second, score.first);
	//TextOut(hdc, x, y, sz, strlen(sz));
}