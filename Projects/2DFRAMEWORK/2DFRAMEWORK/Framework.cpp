#include "stdafx.h"
#include "FrameWork.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimerManager.h"

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

	MYRENDERMANAGER->LoadCImage();				//랜더매니저가 가진 이미지 전부 로드

}

void FrameWork::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	m_hWnd = hMainWnd;
	m_hInstance = hInstance;

	//매니저 생성
	m_ClientInfo.IsScene = E_MENU;
	//m_ClientInfo.IsReady = FALSE; todo소현 이거때문에 안넘어 갔음

	//TODO 타이머, 사운드매니저
	MYRENDERMANAGER->LoadCImage();				//랜더매니저
	this->MakeServer();
	
	SCENEMANAGER->SetScene(E_MENU);

	//this->Enter(E_MENU);
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
	//1. scene이 있다면 각 씬마다 draw호출

	//씬정보가 널이 아니면 그 씬이 가지고 있는 이미지를 그려야한다. 
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

	////1. 더블버퍼링 처리 위아래로
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
	//장치 입력
	INPUTMANAGER->SetPos();
	INPUTMANAGER->SetKeyState();

	//update해줌. 꼭 업데이트 해서 정보 받아오고 그려야함. 
	wsprintf(str, "FPS : %f", TIMEMANAGER->m_FPS, strlen(str));
	SetWindowTextA(FRAMEWORK->m_hWnd, str);

	
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

	//겟 씬 만들어야함
	//씬이 비어있지 않으면 씬에 들어감
	//씬에 들어감.
	SCENEMANAGER->SetScene(E_MENU);

}

int FrameWork::MakeServer()
{
	int retval;

	// 윈속 초기화
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

	int sockopt = TRUE;
	setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, (const char*)&sockopt, sizeof(sockopt));
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
