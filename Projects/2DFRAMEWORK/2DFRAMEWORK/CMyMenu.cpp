#include "stdafx.h"
#include "Framework.h"
#include "CMyMenu.h"
#include "CRenderManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "CGameObject.h"
#include "CMybutton.h"
#include "MyPacket.h"
#include "CPlayer.h"
#include "TimerManager.h"

CMyMenu::CMyMenu()
{
	

	//m_MenuImageMap
	//m_MenuImageMap.insert(make_pair("background", MYRENDERMANAGER->FindCImage("StartBackground.png")));
	//std::map<std::string, std::vector<MyImage>> m_ImageMap;
	m_MenuImageMap.insert(pair<std::string, std::vector<MyImage>>("MenuBackGroundImage", *MYRENDERMANAGER->FindCImage("MenuImage")));
	m_MenuImageMap.insert(pair<std::string, std::vector<MyImage>>("MenuStartButtonImage", *MYRENDERMANAGER->FindCImage("MenuStartButtonImage")));
	m_MenuImageMap.insert(pair<std::string, std::vector<MyImage>>("MenuExitButtonImage", *MYRENDERMANAGER->FindCImage("MenuExitButtonImage")));
	m_MenuImageMap.insert(pair<std::string, std::vector<MyImage>>("MenuReadyButtonImage", *MYRENDERMANAGER->FindCImage("MenuReadyButtonImage")));

	m_ListButton.push_back(new CMyButton("START", 40.0f, 400.0f, 100.0f, 100.0f));

	m_ListButton.push_back(new CMyButton("READY",80.0f,300.0f, 100.0f, 100.0f));
	
	m_ListButton.push_back(new CMyButton("EXIT", 500.0f, 200.0f, 150.0f, 150.0f));


}


CMyMenu::~CMyMenu()
{

}

void CMyMenu::Render(HDC hdc)
{
	
	PAINTSTRUCT ps;
	BeginPaint(g_hWnd, &ps);
	{
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, m_nWndClientWidth, m_nWndClientHeight);
		SelectObject(memDC, memBit);
	
		TransparentBlt(memDC, 0, 0, 400, 600, m_MenuImageMap["MenuBackGroundImage"].begin()->GetCimage()->GetDC(), 0, 0,
			m_MenuImageMap["MenuBackGroundImage"].begin()->GetWidth(), m_MenuImageMap["MenuBackGroundImage"].begin()->GetHeight(), RGB(0,0,0));

		
		//START버튼
		TransparentBlt(memDC, 40, 400, 100, 100, m_MenuImageMap["MenuStartButtonImage"].begin()->GetCimage()->GetDC(), 0, 0,
			m_MenuImageMap["MenuStartButtonImage"].begin()->GetWidth() - 3, m_MenuImageMap["MenuStartButtonImage"].begin()->GetHeight() - 15, RGB(0, 0, 0));
		//EXIT
		TransparentBlt(memDC, 240, 400, 100, 100, m_MenuImageMap["MenuExitButtonImage"].begin()->GetCimage()->GetDC(), 0, 0,
			m_MenuImageMap["MenuStartButtonImage"].begin()->GetWidth() - 3, m_MenuImageMap["MenuExitButtonImage"].begin()->GetHeight() - 15, RGB(0, 0, 0));
		
		//READY. 레디상태가 아니면 알유레디 버튼이 그려짐
		if (m_pPlayer->GetIsReady() == FALSE)
		{

			TransparentBlt(memDC, 80, 300, 100, 100, m_MenuImageMap["MenuReadyButtonImage"].begin()->GetCimage()->GetDC(), 0, 0,
			m_MenuImageMap["MenuReadyButtonImage"].begin()->GetWidth() - 3, m_MenuImageMap["MenuReadyButtonImage"].begin()->GetHeight() - 15, RGB(255, 0, 0));

		}

		BitBlt(hdc, 0, 0, 800, 600, memDC, 0, 0, SRCCOPY);

		DeleteObject(memBit);
		DeleteDC(memDC);
	}
	EndPaint(g_hWnd, &ps);

}

void CMyMenu::EndRender()
{
	HDC hDC = ::GetDC(m_hWnd);

	BitBlt(hDC, 0, 0, m_nWndClientWidth, m_nWndClientHeight, m_hdc, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hDC);
}

void CMyMenu::Update()
{
	CheckKey();
	//FRAMEWORK->SetClientInfo(m_ClientInfo);
	if (m_pPlayer->m_IsReady)
	{
		send(FRAMEWORK->GetSock(), (char*)&m_pPlayer->m_IsReady, sizeof(m_pPlayer->m_IsReady), 0);
		//씬 정보받음 
		int retval = FRAMEWORK->recvn(FRAMEWORK->GetSock(), (char*)&m_ClientInfo.IsScene, sizeof(m_ClientInfo.IsScene), 0);

		if (m_ClientInfo.IsScene == E_INGAME)
		//if (m_ClientInfo.IsScene == E_GAMEOVER)
		{
			FRAMEWORK->recvn(FRAMEWORK->GetSock(), (char*)&m_ClientInfo.PlayNum, sizeof(m_ClientInfo.PlayNum), 0);
			FRAMEWORK->SetClientInfo(m_ClientInfo);
			//씬 넘김
			SCENEMANAGER->SetScene(E_INGAME);
			//SCENEMANAGER->SetScene(E_GAMEOVER);
			TIMEMANAGER->SetPrevElipsedTime();
			
		}
	}

	//클라 작업을 위한 인게임치트키 F8을 누르세여 응 버그
	/*if (Key == KEY_CHEATREADY)
	{
		SCENEMANAGER->SetScene(E_INGAME);
	}*/
}

void CMyMenu::Destroy()
{
}

void CMyMenu::Enter()
{
	//create
}

void CMyMenu::Exit()
{
}

void CMyMenu::CheckKey()
{
	DWORD Key = INPUTMANAGER->GetKeyState();
	if (Key == KEY_READY)
	{
		m_pPlayer->SetReady(TRUE);
	}

	

}

void CMyMenu::PreRender(DWORD dwColor)
{
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hdc, hBrush);
	Rectangle(m_hdc, 0, 0, m_nWndClientWidth, m_nWndClientHeight);
	SelectObject(m_hdc, hOldBrush);
	DeleteObject(hBrush);
}

void CMyMenu::BeginRender()
{
	HDC hDC = ::GetDC(m_hWnd);

	if (!m_hdc)
		m_hdc = ::CreateCompatibleDC(hDC);
	if (m_hBitmapFrameBuffer)
	{
		::SelectObject(m_hdc, NULL);
		::DeleteObject(m_hBitmapFrameBuffer);
		m_hBitmapFrameBuffer = NULL;
	}

	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_nWndClientWidth, m_nWndClientHeight);
	SelectObject(m_hdc, m_hBitmapFrameBuffer);

	ReleaseDC(m_hWnd, hDC);
	SetBkMode(m_hdc, TRANSPARENT);
}
