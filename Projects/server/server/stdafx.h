// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "Enemy.h"
#include "Player.h"

#define SERVERPORT 9000
#define BUFSIZE    1024

using namespace std;
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

enum Key
{
	E_LEFT,
	E_RIGHT,
	E_UP,
	E_DOWN,
	E_ATTACK,
	E_ULTIMATE
};