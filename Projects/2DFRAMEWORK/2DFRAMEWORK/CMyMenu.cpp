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

		
		//START��ư
		TransparentBlt(memDC, 40, 400, 100, 100, m_MenuImageMap["MenuStartButtonImage"].begin()->GetCimage()->GetDC(), 0, 0,
			m_MenuImageMap["MenuStartButtonImage"].begin()->GetWidth() - 3, m_MenuImageMap["MenuStartButtonImage"].begin()->GetHeight() - 15, RGB(0, 0, 0));
		//EXIT
		TransparentBlt(memDC, 240, 400, 100, 100, m_MenuImageMap["MenuExitButtonImage"].begin()->GetCimage()->GetDC(), 0, 0,
			m_MenuImageMap["MenuStartButtonImage"].begin()->GetWidth() - 3, m_MenuImageMap["MenuExitButtonImage"].begin()->GetHeight() - 15, RGB(0, 0, 0));
		
		//READY. ������°� �ƴϸ� �������� ��ư�� �׷���
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

	//���������� ��� �����ش�.
	if (m_pPlayer->GetIsReady())
	{
		send(FRAMEWORK->GetSock(), (char*)&m_pPlayer->m_IsReady, sizeof(m_pPlayer->m_IsReady), 0); //��ģ��
	}

	//todo ����
	if (m_pPlayer->GetIsReady()) //���� ������ ��
	{
		//�� �������� 
		int retval = FRAMEWORK->recvn(FRAMEWORK->GetSock(), (char*)&FRAMEWORK->m_ClientInfo.IsScene, sizeof(FRAMEWORK->m_ClientInfo.IsScene), 0);
		if (retval == SOCKET_ERROR) 
		{
			FRAMEWORK->err_display("recv() IsReady");
		}
		else
		{

		if (FRAMEWORK->GetClientInfo().IsReady) //���� ������ true��
		{
			//�� �ѱ�
			SCENEMANAGER->SetScene(E_INGAME);
		}
		}
	}
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

	//recv(FRAMEWORK->GetSock(), (char*)&FRAMEWORK->m_ClientInfo.IsReady, sizeof(FRAMEWORK->m_ClientInfo.IsReady), 0);
	//if (Key & KEY_ENTER) //�ΰ������� �ٲٶ�� ���ú긦 �ް� �� ����
	//{
	//	SCENEMANAGER->SetScene(E_INGAME);
	//}
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
