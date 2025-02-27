// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "winmm.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <atlimage.h>
#include <WinSock2.h>
#include <time.h>
#include <list>
#include <iostream>
#include <string>

#include "SingleTon.h"


//
#include "CRenderManager.h"
//#include "Framework.h"


using namespace std;
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.


#define FRAMEWORK		 FrameWork::GetInstance()
#define MYRENDERMANAGER	 CRenderManager::GetInstance()
#define SCENEMANAGER	 CSceneManager::GetInstance()
#define OBJECTMANAGER	 CObjectManager::GetInstance()
#define INPUTMANAGER	 CInputManager::GetInstance()
#define TIMEMANAGER		TimeManager::GetInstance()


#define FPS_PERSECOND 30
//OBJECT
#define MAXOBJECTNUM 10000
#define MAXITEMNUM 100
//SERVER
#define SERVERPORT 9000
#define BUFSIZE    1024

#define WndX 419
#define WndY 635



extern HWND g_hWnd;

enum E_SCENE
{
	E_TITLE,
	E_MENU,
	E_INGAME,
	E_GAMEOVER,
	E_RANK
};

enum E_OBJECT
{
	E_BACKGROUND,
	E_PLAYER,
	E_ENEMY1,
	E_ENEMY2,
	E_ENEMY3,
	E_BOSS1,
	E_BOSS2
};
enum E_ITEM
{
	E_ITEM,
	E_IPOWER,
	E_ISKILL,
	E_ISUB,
	E_ISHIELD,
	E_IBULLET
};

//키 상태

//메뉴
const DWORD KEY_READY = 0x00000120; 
//const DWORD KEY_ENTER = 0x00000222;
const DWORD KEY_END =	0x00000999;

//작업을 위한 보조키
const DWORD KEY_CHEATREADY = 0x00000298;


//인게임
const DWORD KEY_LEFT = 0x0001;
const DWORD KEY_RIGHT = 0x0002;
const DWORD KEY_UP = 0x0004;
const DWORD KEY_DOWN = 0x0008;
const DWORD KEY_SPACE = 0x0020;
const DWORD KEY_SKILL = 0x0040;

//마우스
const DWORD KEY_LBUTTON = 0x00000100;