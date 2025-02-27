// 2DFRAMEWORK.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "2DFRAMEWORK.h"
#include "Framework.h"
#include "SceneManager.h"
#include "TimerManager.h"
#define MAX_LOADSTRING 100

// 전역 변수:
HWND g_hWnd,hDlg;
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
int cmd;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(215);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY2DFRAMEWORK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	hInst = hInstance;
	cmd = nCmdShow;


		hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
		HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, WndX, WndY, nullptr, nullptr, hInst, nullptr);

		g_hWnd = hWnd;
		if (!hWnd)
		{
			return FALSE;
		}
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DialogProc);

		FRAMEWORK->OnCreate(hInst, hWnd);
		ShowWindow(hWnd, cmd);
		UpdateWindow(hWnd);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2DFRAMEWORK));

    MSG msg;
	HDC memDc = GetDC(g_hWnd);


    // 기본 메시지 루프입니다.
	msg.message = WM_NULL;
	
	while(msg.message != WM_DESTROY)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //PeekMessage
		{
			if (msg.message == WM_QUIT) break;

			if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
		else
		{
			//if (dwTime + 30 < GetTickCount())
			//TIMEMANAGER->m_CurrentTime = 
			/*TIMEMANAGER->m_eTime = TIMEMANAGER->m_CurrentTime - TIMEMANAGER->m_PrevTime;
			TIMEMANAGER->m_eActine += TIMEMANAGER->m_eTime;
			if (TIMEMANAGER->m_eActine > 1 / FPS_PERSECOND)
			{*/
			//	//dwTime = GetTickCount();
			//	TIMEMANAGER->m_eTime = 0.0f;
			//	
				FRAMEWORK->Update();
				FRAMEWORK->Render();
			//}
			//1105todo. 렌더가 불리지 않는다. 여기서 이미지 렌더로 들어가야함. 
		}
	}
	//디스트로이.
	//릴리즈

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2DFRAMEWORK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//



//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
		ShowWindow(hDlg, SW_SHOW);

            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
				
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CHAR:
		
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

BOOL CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HWND hWnd;
	switch (uMsg) {
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_IPADDRESS1, "127.0.0.1");
		return TRUE;
	case WM_COMMAND:
		switch (wParam) {
		case IDC_CONNECT:
			GetDlgItemText(hDlg, IDC_IPADDRESS1, FRAMEWORK->SERVERIP, 20);
			GetDlgItemText(hDlg, IDC_NICKNAME, FRAMEWORK->NICKNAME, 4);

			DestroyWindow(hDlg);
			hDlg = NULL;
			return FALSE;
			//return TRUE;

		case IDCANCEL:
			DestroyWindow(hDlg);
			hDlg = NULL;
			return TRUE;

		}
	}
	return FALSE;
}