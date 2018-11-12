#include "stdafx.h"
#include "FrameWork.h"
#include "SceneManager.h"
#include "InputManager.h"

FrameWork::FrameWork()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(215);
	m_hdc = GetDC(g_hWnd);

	
}


FrameWork::~FrameWork()
{
	Destroy();
}

void FrameWork::Init()
{

	MYRENDERMANAGER->LoadCImage();				//�����Ŵ����� ���� �̹��� ���� �ε�

}

void FrameWork::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	m_hWnd = hMainWnd;
	m_hInstance = hInstance;

	//�Ŵ��� ����
	m_ClientInfo.IsScene = E_MENU;
	//m_ClientInfo.IsReady = FALSE; todo���� �̰Ŷ����� �ȳѾ� ����

	//TODO Ÿ�̸�, ����Ŵ���
	MYRENDERMANAGER->LoadCImage();				//�����Ŵ���
	SCENEMANAGER->SetScene(E_MENU);

	//this->Enter(E_MENU);
	this->MakeServer();
}


void FrameWork::OnDraw()
{


}

void FrameWork::PreRender(DWORD dwColor)
{
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hdc, hBrush);
	::Rectangle(m_hdc, 0, 0, m_nWndClientWidth, m_nWndClientHeight);
	::SelectObject(m_hdc, hOldBrush);
	::DeleteObject(hBrush);
}

void FrameWork::BeginRender()
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
	::SelectObject(m_hdc, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hdc, TRANSPARENT);
}



void FrameWork::Render()
{
	//MYRENDERMANAGER->Render(memDC,);
	//todo 
	//1. scene�� �ִٸ� �� ������ drawȣ��

	//�������� ���� �ƴϸ� �� ���� ������ �ִ� �̹����� �׷����Ѵ�. 
	//if (!m_states.empty())
	//{
	//	//m_states.back()->
	//}
	//CScene* state;
	//m_states.push_back(state);
	//if (!m_states.empty())
	//{
	//	m_states.back()->OnDraw(m_hdc);
	//}
	//// resume previous state
	//else if (!m_states.empty()) {
	//	states.back()->OnDraw(m_hdc);
	//}

	////1. ������۸� ó�� ���Ʒ���
	//this->BeginRender();
	SCENEMANAGER->Render(m_hdc);

	//this->EndRender();

}

void FrameWork::EndRender()
{
	HDC hDC = ::GetDC(m_hWnd);

	::BitBlt(hDC, 0, 0, m_nWndClientWidth, m_nWndClientHeight, m_hdc, 0, 0, SRCCOPY);
	::ReleaseDC(m_hWnd, hDC);

}

void FrameWork::Update()
{
	//��ġ �Է�
	INPUTMANAGER->SetPos();
	INPUTMANAGER->SetKeyState();

	//update����. �� ������Ʈ �ؼ� ���� �޾ƿ��� �׷�����. 

	SCENEMANAGER->Update();
}

void FrameWork::Destroy()
{
	//delete pSceneMgr;
	//pSceneMgr = nullptr;
}

void FrameWork::Enter(E_SCENE state)
{
	//m_states.push_back(state);
	//m_states = state;
//	m_states.back()->Enter();

	//�� �� ��������
	//���� ������� ������ ���� ��
	//���� ��.
	SCENEMANAGER->SetScene(E_MENU);

}

int FrameWork::MakeServer()
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	//if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(m_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	//if (retval == SOCKET_ERROR) err_quit("connect()");

	
	m_count = 0;
}

int FrameWork::recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
	
}

void FrameWork::err_display(const char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
